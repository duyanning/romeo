import java.io.BufferedReader;
import java.io.FileReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.nio.charset.StandardCharsets;
import java.security.*;
import java.util.HashMap;
import java.util.LinkedList;

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
        PrivateKey privateKeyLoad = RsaEncryptionPkcs15.getPrivateKeyFromString(RsaEncryptionPkcs15.loadRsaPrivateKeyPem());
        mNonceEncrypted = RsaEncryptionPkcs15.base64Encoding(RsaEncryptionPkcs15.rsaEncryptionPkcs1b(privateKeyLoad, dataToEncrypt));

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

class InstanceInfo {
};

class InstanceList {
    HashMap<String, InstanceInfo> mMap = new HashMap<String, InstanceInfo>();
    LinkedList<String> mList = new LinkedList<String>(); // 为了记住谁是最老的实例
    boolean has(String instanceId) {
        return mMap.get(instanceId) != null;
    }

    InstanceInfo getInstance(String instanceId) {
        return mMap.get(instanceId);
    }

    int size() {
        return mMap.size();
    }

    void add(String instanceId) {
        mMap.put(instanceId, new InstanceInfo());
        mList.offer(instanceId);
    }

    void removeEldest() {
        String eldestInstanceId = mList.getFirst();
        mList.removeFirst();
        mMap.remove(eldestInstanceId);
    }

}

class UserInfo {
    int mMaxOnlineNum;
    InstanceList mInstanceList = new InstanceList();
}

class UserList {
    HashMap<String, UserInfo> mMap = new HashMap<String, UserInfo>();

    void loadFromFile() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("user-list.txt"));
        String userId = br.readLine();
        while (userId != null) {
            mMap.put(userId, new UserInfo());
            userId = br.readLine();
        }
        br.close();
    }

    boolean has(String userId) {
        return mMap.get(userId) != null;
    }

    UserInfo getUserInfo(String userId) {
        return mMap.get(userId);
    }
}

public class Juliet {

//    ArrayList<String> mUserList;
//    ArrayList<String> mInstanceLis
    UserList mUserList = new UserList();
    DatagramSocket datagramSocket;
    DatagramPacket inPkt;

    void go() throws Exception {
        System.out.println("Juliet started.");
        System.out.println("loading user list from file user-list.txt");
        mUserList.loadFromFile();

        System.out.println("waiting for messages from Romeo ...");

        // 创建套接字（作为服务器，端口号必须是确定的，不然别人如何知道你在哪个端口）
        datagramSocket = new DatagramSocket(1314);

        while (true) {

            byte[] inBuf = new byte[1000]; // 输入缓冲区

            // 构造用于接收的数据包
            inPkt = new DatagramPacket(inBuf, inBuf.length);

            datagramSocket.receive(inPkt); // 接收

            // 从收到的udp数据报中得到一个字符串
            String msgString = new String(inPkt.getData(), 0, inPkt.getLength());

            // 该字符串其实是个json对象的文本形式
            ConfessionMsg confessionMsg = new ConfessionMsg(msgString);

            // 如果用户id就不在用户列表中,直接忽略该消息
            if (!mUserList.has(confessionMsg.mUserId))
                continue;

            // 是udp数据报中提取ip地址与port号,形成实例id
            String ip = inPkt.getAddress().getHostAddress();
            String port = String.valueOf(inPkt.getPort());
            String instanceId = ip + ":" + port;

            UserInfo userInfo = mUserList.getUserInfo(confessionMsg.mUserId);

            // 判断是否在该用户的实例列表中
            if (userInfo.mInstanceList.has(instanceId)) {

                if (exceed_online_limit(userInfo))
                    userInfo.mInstanceList.removeEldest();
                send_reassurance_msg(confessionMsg);
            }
            else {

            }

        }

    }

    boolean exceed_online_limit(UserInfo userInfo) {
        // 获得该用户的实例列表
        InstanceList instanceList = userInfo.mInstanceList;
        int maxOnlineNum = userInfo.mMaxOnlineNum;

        if (instanceList.size() > maxOnlineNum)
            return true;

        return false;
    }

    void send_reassurance_msg(ConfessionMsg confessionMsg) throws Exception {
        // 针对表白消息构造安抚消息
        ReassuranceMsg reassuranceMsg = new ReassuranceMsg(confessionMsg.mUserId, confessionMsg.mNonce);

        System.out.println(reassuranceMsg.toJsonString());

        byte[] outBuf = reassuranceMsg.toJsonString().getBytes();
        DatagramPacket outPkt = new DatagramPacket( // 构造用于发送的数据包
                outBuf, outBuf.length, // 输出缓冲区起始地址与大小
                inPkt.getAddress(), inPkt.getPort() // 接收方的地址和端口号（谁给我发，我就发给谁）
        );

        datagramSocket.send(outPkt); // 发送

    }

    public static void main(String[] args) throws Exception {
        Juliet juliet = new Juliet();
        juliet.go();
    }
}
