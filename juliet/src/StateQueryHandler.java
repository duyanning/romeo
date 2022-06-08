import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import java.io.IOException;
import java.io.OutputStream;

class StateQueryHandler implements HttpHandler {
    UserList mUserList;

    StateQueryHandler(UserList userList) {
        mUserList = userList;
    }

    @Override
    public void handle(HttpExchange t) throws IOException {
        String prologue = ""
                + "<!DOCTYPE html>"
                + "<html><head><title>Juliet state server</title>"
                + "</head>"
                + "<body>";


        String epilogue = "</body></html>\r\n";

        String response = prologue;
        //response += "duyanning";
        response += mUserList.getHtmlDesc();
        response += epilogue;
        t.sendResponseHeaders(200, response.length());
        OutputStream os = t.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}

//class StateServer extends Thread {
//    public void run() {
//
////                + "<style>body { background-color: #111 }"
////                + "h1 { font-size:4cm; text-align: center; color: black;"
////                + " text-shadow: 0 0 2mm red}</style>"
//        String prologue = "HTTP/1.1 200 OK\r\n"
//                + "Content-Type: text/html; charset=UTF-8\r\n\r\n"
//                + "<!DOCTYPE html>"
//                + "<html><head><title>Juliet state server</title>"
//                + "</head>"
//                + "<body>";
//        String epilogue = "</body></html>\r\n";
//
//        System.out.println("State server is waiting for a connection from client...");
//        ServerSocket server = null; // 在这个端口上监听
//        try {
//            server = new ServerSocket(1314);
//            while (true) {
//                Socket s = server.accept(); // 等待客户端发来连接请求
//                System.out.println("connection established");
//                DataOutputStream out = new DataOutputStream(s.getOutputStream()); // 从套接字上获得输出流
//                //out.writeUTF("hello, bye.");
//                String response = "";
//                response += prologue;
//
//                response += "duyanning";
//
//                response += epilogue;
//                out.writeUTF(response);
//                out.close();
//                s.close();
//            }
//        } catch (IOException e) {
//            System.out.println(e);;
//        }
//    }
//}
