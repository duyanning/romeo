import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

class ConfessionMsg extends Msg {
    String mUserId;
    String mNonce;
    String mSecret;

    ConfessionMsg(String userId, String nonce) {
        super("confession");
        mUserId = userId;
        mNonce = nonce;
    }

    ConfessionMsg(String jsonString) {
        super("confession");
        JSONParser parser = new JSONParser();
        try {
            JSONObject jsonMsg = (JSONObject) parser.parse(jsonString);
            mMsgType = (String) jsonMsg.get("msg_type");
            System.out.println(mMsgType);

            mUserId = (String) jsonMsg.get("user_id");
            System.out.println(mUserId);

            //System.out.println((long)json.get("nonce"));
            mNonce = (String) jsonMsg.get("nonce");
            System.out.println(mNonce);

            mSecret = (String) jsonMsg.get("secret");
            System.out.println(mSecret);

        } catch (ParseException e) {
            System.out.println(e);
        }
    }
}
