import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.Date;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

class Msg {
    public String msg_type;
    public Msg(String type) {
        msg_type = type;
    }
}

class ConfessionMsg extends Msg {
    public String instance_id;
    public String nonce;
    ConfessionMsg(String instance_id, String nonce) {
        super("confession");
        instance_id = instance_id;
        nonce = nonce;
    }

    ConfessionMsg(String jsonString) {
        super("confession");
        JSONParser parser = new JSONParser();
        String msg_type = "";
        String instance_id = "";
        String nonce = "";
        try {
            JSONObject jsonMsg = (JSONObject)parser.parse(jsonString);
            msg_type = (String)jsonMsg.get("msg_type");
            System.out.println(msg_type);

            instance_id = (String) jsonMsg.get("instance_id");
            System.out.println(instance_id);

            //System.out.println((long)json.get("nonce"));
            nonce = (String) jsonMsg.get("nonce");
            System.out.println(nonce);

        }
        catch (ParseException e) {
            System.out.println(e);
        }
    }
}

class ReassuranceMsg extends Msg {
    public String instance_id;
    public String nonce;
    ReassuranceMsg(String instance_id, String nonce) {
        super("reassurance");
        instance_id = instance_id;
        nonce = nonce;
    }

    public String toJsonString() {
        JSONObject jsonReassuranceMsg = new JSONObject();
        jsonReassuranceMsg.put("msg_type", "reassurance");
        jsonReassuranceMsg.put("instance_id", instance_id);
        jsonReassuranceMsg.put("nonce", nonce);
        return jsonReassuranceMsg.toJSONString();
    }
}

public class Juliet {
    public static void main(String[] args) throws IOException {
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
            ReassuranceMsg reassuranceMsg = new ReassuranceMsg(confessionMsg.instance_id, confessionMsg.nonce);

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
