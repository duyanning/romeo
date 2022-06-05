#include <string>
#include <regex>

#include "base64.h"

#include "Enclave_t.h"

#include "sgx_trts.h"
#include "sgx_tcrypto.h"

#include "RsaPkcs15.h"

using namespace std;

struct ConfessionMsg {
	string user_id;
	string nonce; // һ���������
};

//struct ReassuranceMsg {
//	string user_id;
//	string nonce; // һ���������
//};

const int HEART_BREAK_LIMIT = 2;
int disappointment_count = 0;
bool is_heart_broken = false;

//bool last_confession_msg_reassured = false; // commented for debug
bool last_confession_msg_reassured = true;
ConfessionMsg confession_msg;


void confess()
{
	// �����һ�������Ϣ��û�õ�����,�Ͳ�Ҫ���µı��
	if (last_confession_msg_reassured == false)  return;

	confession_msg.user_id = "duyanning@gmail.com";
	int nonce;
	sgx_read_rand((unsigned char*)&nonce, sizeof nonce);
	confession_msg.nonce = std::to_string(nonce);

	//���÷ǿ��ź�������������ͱ����Ϣconfession_msg
	confess_through_untrusted(
		confession_msg.user_id.c_str(),
		confession_msg.nonce.c_str()
	);

	last_confession_msg_reassured = false;// commented for debug

}

// ����
// Open the envelope and read the letter.
// ����������ɵ��⸺����շ�������Ϣ���̵߳���
//void check_letter(ReassuranceMsg msg)
//{
//	��msg���н��� // ���ܱ����ڷɵ��н���,ֻ���������൱������Ҷ�԰�����Ϣ������ǩ��
//		if (�ǶԸղŷ��͵ı�׽��а�������Ϣ) {
//			disappointment_count = 0;
//			last_confession_msg_reassured = true;
//		}
//}




//https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
// usage: replace(rsaPrivateKeyPem, "-----END PRIVATE KEY-----", "");
//bool replace(std::string& str, const std::string& from, const std::string& to) {
//	size_t start_pos = str.find(from);
//	if (start_pos == std::string::npos)
//		return false;
//	str.replace(start_pos, from.length(), to);
//	return true;
//}

// usage: replaceAll(rsaPrivateKeyPem, "[\\r\\n]+", "");
//void replaceAll(std::string& str, const std::string& from, const std::string& to) {
//	if (from.empty())
//		return;
//	size_t start_pos = 0;
//	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
//		str.replace(start_pos, from.length(), to);
//		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
//	}
//}

// ECALL
//void reassure_in_enclave(const char* user_id, const unsigned char* nonce_encrypted, size_t len, const char* nonce)
void reassure_in_enclave(const char* user_id, const char* nonce_encrypted)
{
	//��msg���н��� // ���ܱ����ڷɵ��н���,ֻ���������൱������Ҷ�԰�����Ϣ������ǩ��

	std::vector<BYTE> encrypted_nonce_vec = base64_decode(nonce_encrypted);

	unsigned char decrypted[4098] = {};
	int decrypted_length;
	rsa_pkcs15_decrypt(&encrypted_nonce_vec[0], decrypted, &decrypted_length);

	string nonce((char*)&decrypted[0]);



	//if (confession_msg.user_id == user_id && confession_msg.nonce == newnonce) { // �ǶԸղŷ��͵ı�׽��а�������Ϣ
	if (confession_msg.nonce == nonce) { // �ǶԸղŷ��͵ı�׽��а�������Ϣ
	//if (true) {
		disappointment_count = 0;
		last_confession_msg_reassured = true;
	}
}

// ECALL
//void calculate_xpos_in_enclave(int* ok, int32_t seqNumber, int32_t* xpos)
void calculate_xpos_in_enclave(int* ok, int seqNumber, int* xpos)
{

	confess();

	// ----------------------------------------------------

	disappointment_count++;
	if (disappointment_count == HEART_BREAK_LIMIT)
		is_heart_broken = true;

	// ----------------------------------------------------

	if (is_heart_broken) {
		*ok = 0;
		return;
	}

	// ----------------------------------------------------


	// �������Ĺؼ�����
    *xpos = 80 + (100 * (seqNumber % 5));

	*ok = 1;
}