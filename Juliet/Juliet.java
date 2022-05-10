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

	    // �����׽��֣���Ϊ���������˿ںű�����ȷ���ģ���Ȼ�������֪�������ĸ��˿ڣ�
        DatagramSocket s = new DatagramSocket(1314); 

	    while (true) {

	        byte[] inBuf = new byte[1000]; // ���뻺����

	        // �������ڽ��յ����ݰ�
	        DatagramPacket inPkt = new DatagramPacket(inBuf, inBuf.length); 

	        s.receive(inPkt); // ����

	        System.out.println("client said: " + new String(inPkt.getData(), 0, inPkt.getLength()));

	        // ------------����Ϊ�ӿͻ��˽������ݣ�����Ϊ��ͻ��˷�������-----------------

	        Date today = new Date(); // ׼����ͻ��˷��͵����ݡ������������
	        byte[] outBuf = today.toString().getBytes();
	        DatagramPacket outPkt = new DatagramPacket( // �������ڷ��͵����ݰ�
	                outBuf, outBuf.length, // �����������ʼ��ַ���С
	                inPkt.getAddress(), inPkt.getPort() // ���շ��ĵ�ַ�Ͷ˿ںţ�˭���ҷ����Ҿͷ���˭��
	                //inPkt.getAddress(), 1413 // ���շ��ĵ�ַ�Ͷ˿ںţ�˭���ҷ����Ҿͷ���˭��
	        );

	        s.send(outPkt); // ����
	    }
    }
}
