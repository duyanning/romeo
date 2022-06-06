import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Scanner;

class UserList {
    HashMap<String, UserInfo> mMap = new HashMap<String, UserInfo>();

    void loadFromFile() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("user-list.txt"));
        String line = br.readLine();
        while (line != null) {
            Scanner scanner = new Scanner(line);
            String userId = scanner.next();
            int maxOnlineNum = scanner.nextInt();

            mMap.put(userId, new UserInfo(maxOnlineNum));

            line = br.readLine();
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
