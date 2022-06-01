import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.nio.charset.StandardCharsets;
import java.security.*;

class Msg {
    public String mMsgType;
    public Msg(String type) {
        mMsgType = type;
    }
}

class ConfessionMsg extends Msg {
    public String mUserId;
    public String mNonce;
    ConfessionMsg(String userId, String nonce) {
        super("confession");
        mUserId = userId;
        mNonce = nonce;
    }

    ConfessionMsg(String jsonString) {
        super("confession");
        JSONParser parser = new JSONParser();
        try {
            JSONObject jsonMsg = (JSONObject)parser.parse(jsonString);
            mMsgType = (String)jsonMsg.get("msg_type");
            System.out.println(mMsgType);

            mUserId = (String) jsonMsg.get("user_id");
            System.out.println(mUserId);

            //System.out.println((long)json.get("nonce"));
            mNonce = (String) jsonMsg.get("nonce");
            System.out.println(mNonce);

        }
        catch (ParseException e) {
            System.out.println(e);
        }
    }
}

class ReassuranceMsg extends Msg {
    public String mUserId;
    public String mNonce;
    public String mNonceEncrypted;
    ReassuranceMsg(String userId, String nonce) throws GeneralSecurityException {
        super("reassurance");
        mUserId = userId;
        mNonce = nonce;

        byte[] dataToEncrypt = mNonce.getBytes(StandardCharsets.UTF_8);
        PublicKey publicKeyLoad = RsaEncryptionOaepSha256.getPublicKeyFromString(RsaEncryptionOaepSha256.loadRsaPublicKeyPem());
        mNonceEncrypted = RsaEncryptionOaepSha256.base64Encoding(RsaEncryptionOaepSha256.rsaEncryptionOaepSha256(publicKeyLoad, dataToEncrypt));

    }

    public String toJsonString() {
        JSONObject jsonReassuranceMsg = new JSONObject();
        jsonReassuranceMsg.put("msg_type", "reassurance");
        jsonReassuranceMsg.put("user_id", mUserId);
        jsonReassuranceMsg.put("nonce", mNonce);
        jsonReassuranceMsg.put("nonce_encrypted", mNonceEncrypted);
        return jsonReassuranceMsg.toJSONString();
    }
}

public class Juliet {
    public static void main(String[] args) throws Exception {
        System.out.println("Juliet started.");
        System.out.println("waiting for messages from Romeo ...");

        // 创建套接字（作为服务器，端口号必须是确定的，不然别人如何知道你在哪个端口）
        DatagramSocket s = new DatagramSocket(1314);

        while (true) {

            byte[] inBuf = new byte[1000]; // 输入缓冲区

            // 构造用于接收的数据包
            DatagramPacket inPkt = new DatagramPacket(inBuf, inBuf.length);

            s.receive(inPkt); // 接收

            // 从收到的udp数据报中得到一个字符串
            String msgString = new String(inPkt.getData(), 0, inPkt.getLength());

            // 该字符串其实是个json对象的文本形式
            ConfessionMsg confessionMsg = new ConfessionMsg(msgString);

            // 针对表白消息构造安抚消息
            ReassuranceMsg reassuranceMsg = new ReassuranceMsg(confessionMsg.mUserId, confessionMsg.mNonce);

            System.out.println(reassuranceMsg.toJsonString());

            // ------------以上为从客户端接收数据，以下为向客户端发送数据-----------------

            byte[] outBuf = reassuranceMsg.toJsonString().getBytes();
            DatagramPacket outPkt = new DatagramPacket( // 构造用于发送的数据包
                    outBuf, outBuf.length, // 输出缓冲区起始地址与大小
                    inPkt.getAddress(), inPkt.getPort() // 接收方的地址和端口号（谁给我发，我就发给谁）
            );

            s.send(outPkt); // 发送
        }
    }
}
