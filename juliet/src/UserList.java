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

    String getHtmlDesc() {
        String desc = "";
        for (HashMap.Entry<String, UserInfo> user : mMap.entrySet()) {
            desc += user.getKey();
            UserInfo userInfo = user.getValue();
            InstanceList instanceList = userInfo.mInstanceList;
            desc += " " + instanceList.verifiedInstanceTotalNumber();
            desc += " of " + userInfo.mMaxOnlineNum;
            desc += "<br/>";
            desc += instanceList.getHtmlDesc("&nbsp; &nbsp; &nbsp; &nbsp; ");
        }
        return desc;
    }

}
