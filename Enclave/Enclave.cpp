#include <string>
#include <regex>

#include "base64.h"

#include "Enclave_t.h"

#include "sgx_trts.h"
#include "sgx_tcrypto.h"

using namespace std;

struct ConfessionMsg {
	string user_id;
	string nonce; // 一次性随机数
};

//struct ReassuranceMsg {
//	string user_id;
//	string nonce; // 一次性随机数
//};

const int HEART_BREAK_LIMIT = 2;
int disappointment_count = 0;
bool is_heart_broken = false;

//bool last_confession_msg_reassured = false; // commented for debug
bool last_confession_msg_reassured = true;
ConfessionMsg confession_msg;


void confess()
{
	// 如果上一条表白消息还没得到安抚,就不要发新的表白
	if (last_confession_msg_reassured == false)  return;

	confession_msg.user_id = "duyanning@gmail.com";
	int nonce;
	sgx_read_rand((unsigned char*)&nonce, sizeof nonce);
	confession_msg.nonce = std::to_string(nonce);

	//调用非可信函数向服务器发送表白消息confession_msg
	confess_through_untrusted(
		confession_msg.user_id.c_str(),
		confession_msg.nonce.c_str()
	);

	last_confession_msg_reassured = false;// commented for debug

}

// 拆信
// Open the envelope and read the letter.
// 这个函数被飞地外负责接收服务器消息的线程调用
//void check_letter(ReassuranceMsg msg)
//{
//	对msg进行解密 // 解密必须在飞地中进行,只有这样才相当于朱丽叶对安抚消息进行了签名
//		if (是对刚才发送的表白进行安抚的消息) {
//			disappointment_count = 0;
//			last_confession_msg_reassured = true;
//		}
//}

string rsaPrivateKeyPem = "-----BEGIN PRIVATE KEY-----\n"
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDwSZYlRn86zPi9\n"
"e1RTZL7QzgE/36zjbeCMyOhf6o/WIKeVxFwVbG2FAY3YJZIxnBH+9j1XS6f+ewjG\n"
"FlJY4f2IrOpS1kPiO3fmOo5N4nc8JKvjwmKtUM0t63uFFPfs69+7mKJ4w3tk2mSN\n"
"4gb8J9P9BCXtH6Q78SdOYvdCMspA1X8eERsdLb/jjHs8+gepKqQ6+XwZbSq0vf2B\n"
"MtaAB7zTX/Dk+ZxDfwIobShPaB0mYmojE2YAQeRq1gYdwwO1dEGk6E5J2toWPpKY\n"
"/IcSYsGKyFqrsmbw0880r1BwRDer4RFrkzp4zvY+kX3eDanlyMqDLPN+ghXT1lv8\n"
"snZpbaBDAgMBAAECggEBAIVxmHzjBc11/73bPB2EGaSEg5UhdzZm0wncmZCLB453\n"
"XBqEjk8nhDsVfdzIIMSEVEowHijYz1c4pMq9osXR26eHwCp47AI73H5zjowadPVl\n"
"uEAot/xgn1IdMN/boURmSj44qiI/DcwYrTdOi2qGA+jD4PwrUl4nsxiJRZ/x7PjL\n"
"hMzRbvDxQ4/Q4ThYXwoEGiIBBK/iB3Z5eR7lFa8E5yAaxM2QP9PENBr/OqkGXLWV\n"
"qA/YTxs3gAvkUjMhlScOi7PMwRX9HsrAeLKbLuC1KJv1p2THUtZbOHqrAF/uwHaj\n"
"ygUblFaa/BTckTN7PKSVIhp7OihbD04bSRrh+nOilcECgYEA/8atV5DmNxFrxF1P\n"
"ODDjdJPNb9pzNrDF03TiFBZWS4Q+2JazyLGjZzhg5Vv9RJ7VcIjPAbMy2Cy5BUff\n"
"EFE+8ryKVWfdpPxpPYOwHCJSw4Bqqdj0Pmp/xw928ebrnUoCzdkUqYYpRWx0T7YV\n"
"RoA9RiBfQiVHhuJBSDPYJPoP34kCgYEA8H9wLE5L8raUn4NYYRuUVMa+1k4Q1N3X\n"
"Bixm5cccc/Ja4LVvrnWqmFOmfFgpVd8BcTGaPSsqfA4j/oEQp7tmjZqggVFqiM2m\n"
"J2YEv18cY/5kiDUVYR7VWSkpqVOkgiX3lK3UkIngnVMGGFnoIBlfBFF9uo02rZpC\n"
"5o5zebaDImsCgYAE9d5wv0+nq7/STBj4NwKCRUeLrsnjOqRriG3GA/TifAsX+jw8\n"
"XS2VF+PRLuqHhSkQiKazGr2Wsa9Y6d7qmxjEbmGkbGJBC+AioEYvFX9TaU8oQhvi\n"
"hgA6ZRNid58EKuZJBbe/3ek4/nR3A0oAVwZZMNGIH972P7cSZmb/uJXMOQKBgQCs\n"
"FaQAL+4sN/TUxrkAkylqF+QJmEZ26l2nrzHZjMWROYNJcsn8/XkaEhD4vGSnazCu\n"
"/B0vU6nMppmezF9Mhc112YSrw8QFK5GOc3NGNBoueqMYy1MG8Xcbm1aSMKVv8xba\n"
"rh+BZQbxy6x61CpCfaT9hAoA6HaNdeoU6y05lBz1DQKBgAbYiIk56QZHeoZKiZxy\n"
"4eicQS0sVKKRb24ZUd+04cNSTfeIuuXZrYJ48Jbr0fzjIM3EfHvLgh9rAZ+aHe/L\n"
"84Ig17KiExe+qyYHjut/SC0wODDtzM/jtrpqyYa5JoEpPIaUSgPuTH/WhO3cDsx6\n"
"3PIW4/CddNs8mCSBOqTnoaxh\n"
"-----END PRIVATE KEY-----";


//https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

// ECALL
void reassure_in_enclave(const char* user_id, const unsigned char* nonce_encrypted, size_t len, const char* nonce)
{
	//对msg进行解密 // 解密必须在飞地中进行,只有这样才相当于朱丽叶对安抚消息进行了签名

	//replace(rsaPrivateKeyPem, "-----BEGIN PRIVATE KEY-----", "");
	//replace(rsaPrivateKeyPem, "-----END PRIVATE KEY-----", "");
	//replaceAll(rsaPrivateKeyPem, "[\\r\\n]+", "");

	//std::vector<unsigned char> rsaPrivateKeyPemEncoded = base64_decode(rsaPrivateKeyPem);

	//unsigned char out_buf[2000];
	//size_t out_len = 0;
	//sgx_rsa_priv_decrypt_sha256(&rsaPrivateKeyPemEncoded[0], out_buf, &out_len,
	//	nonce_encrypted, len);

	//out_buf[out_len] = 0;
	//char* newnonce = (char*)out_buf;



	//if (confession_msg.user_id == user_id && confession_msg.nonce == newnonce) { // 是对刚才发送的表白进行安抚的消息
	if (true) {
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


	// 被保护的关键代码
    *xpos = 80 + (100 * (seqNumber % 5));

	*ok = 1;
}