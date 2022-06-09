import com.sun.net.httpserver.*;


import java.net.*;


public class Juliet {

//    ArrayList<String> mUserList;
//    ArrayList<String> mInstanceLis
    UserList mUserList = new UserList();
    DatagramSocket datagramSocket;
    DatagramPacket inPkt;

    //StateServer mStateServer = new StateServer();

    void go() throws Exception {
        System.out.println("Juliet started.");
        System.out.println("loading user list from file user-list.txt");
        mUserList.loadFromFile();

        System.out.println("waiting for messages from Romeo ...");

        //mStateServer.start();
        // 开启状态服务器,好让用户查询朱丽叶的状态
        HttpServer server = HttpServer.create(new InetSocketAddress(1314), 0);
        server.createContext("/", new StateQueryHandler(mUserList));
        server.setExecutor(null); // creates a default executor
        server.start();

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

                if (confessionMsg.mSecret == null) {
                    ignore();
                    continue;
                }

                InstanceInfo instanceInfo = userInfo.mInstanceList.getInstanceInfo(instanceId);
                if (!confessionMsg.mSecret.equals(instanceInfo.mSecret)) {
                    ignore();
                    continue;
                }

                // 能走到这,说明secret通过验证了
                if (!instanceInfo.mIsSecretVerified) {
                    instanceInfo.mIsSecretVerified = true;
                    userInfo.mInstanceList.promoteToVerifiedInstance(instanceId);
                }

                if (exceed_online_limit(userInfo))
                    userInfo.mInstanceList.removeEldest();
                send_reassurance_msg(confessionMsg, null);
            }
            else {
                if (confessionMsg.mSecret == null) {

                    InstanceInfo instanceInfo = userInfo.mInstanceList.add(instanceId);
                    send_reassurance_msg(confessionMsg, instanceInfo.mSecret);
                    continue;
                }

            }

        }

    }

    boolean exceed_online_limit(UserInfo userInfo) {
        // 获得该用户的实例列表
        InstanceList instanceList = userInfo.mInstanceList;
        int maxOnlineNum = userInfo.mMaxOnlineNum;

        if (instanceList.verifiedInstanceTotalNumber() > maxOnlineNum)
            return true;

        return false;
    }

    // 只有第一次发给罗密欧的安抚消息中含有secret,其他情况为secret==null
    void send_reassurance_msg(ConfessionMsg confessionMsg, String secret) throws Exception {
        // 针对表白消息构造安抚消息
        ReassuranceMsg reassuranceMsg = new ReassuranceMsg(confessionMsg, secret);

        System.out.println(reassuranceMsg.toJsonString());

        byte[] outBuf = reassuranceMsg.toJsonString().getBytes();
        DatagramPacket outPkt = new DatagramPacket( // 构造用于发送的数据包
                outBuf, outBuf.length, // 输出缓冲区起始地址与大小
                inPkt.getAddress(), inPkt.getPort() // 接收方的地址和端口号（谁给我发，我就发给谁）
        );

        datagramSocket.send(outPkt); // 发送

    }

    void ignore() {
        // do nothing
    }


    public static void main(String[] args) throws Exception {
        Juliet juliet = new Juliet();
        juliet.go();
    }
}
