import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.Date;

/**
 * Created by root on 2015-10-24.
 */
public class Juliet {
    public static void main(String[] args) throws IOException {

	    // 创建套接字（作为服务器，端口号必须是确定的，不然别人如何知道你在哪个端口）
        DatagramSocket s = new DatagramSocket(1314); 

	    while (true) {

	        byte[] inBuf = new byte[1000]; // 输入缓冲区

	        // 构造用于接收的数据包
	        DatagramPacket inPkt = new DatagramPacket(inBuf, inBuf.length); 

	        s.receive(inPkt); // 接收

	        System.out.println("client said: " + new String(inPkt.getData(), 0, inPkt.getLength()));

	        // ------------以上为从客户端接收数据，以下为向客户端发送数据-----------------

	        Date today = new Date(); // 准备向客户端发送的内容——今天的日期
	        byte[] outBuf = today.toString().getBytes();
	        DatagramPacket outPkt = new DatagramPacket( // 构造用于发送的数据包
	                outBuf, outBuf.length, // 输出缓冲区起始地址与大小
	                inPkt.getAddress(), inPkt.getPort() // 接收方的地址和端口号（谁给我发，我就发给谁）
	                //inPkt.getAddress(), 1413 // 接收方的地址和端口号（谁给我发，我就发给谁）
	        );

	        s.send(outPkt); // 发送
	    }
    }
}
