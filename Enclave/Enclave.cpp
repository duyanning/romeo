#include <string>

#include "Enclave_t.h"

#include "sgx_trts.h"

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
	confession_msg.nonce = "123";

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

// ECALL
void reassure_in_enclave(const char* user_id, const char* nonce)
{
	//对msg进行解密 // 解密必须在飞地中进行,只有这样才相当于朱丽叶对安抚消息进行了签名
	if (true) { // 是对刚才发送的表白进行安抚的消息
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


	// 业务代码
    *xpos = 80 + (100 * (seqNumber % 5));

	*ok = 1;
}