#include <string>

#include "Enclave_t.h"

#include "sgx_trts.h"

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
	confession_msg.nonce = "123";

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

// ECALL
void reassure_in_enclave(const char* user_id, const char* nonce)
{
	//��msg���н��� // ���ܱ����ڷɵ��н���,ֻ���������൱������Ҷ�԰�����Ϣ������ǩ��
	if (true) { // �ǶԸղŷ��͵ı�׽��а�������Ϣ
		disappointment_count = 0;
		last_confession_msg_reassured = true;
	}
}

// ECALL
void calculate_xpos_in_enclave(int* ok, int32_t seqNumber, int32_t* xpos)
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


	// ҵ�����
    *xpos = 80 + (100 * (seqNumber % 5));

	*ok = 1;
}