import org.json.simple.JSONObject;

import java.nio.charset.StandardCharsets;
import java.security.GeneralSecurityException;
import java.security.PrivateKey;

class ReassuranceMsg extends Msg {
    public String mUserId;
    public String mNonce;
    public String mNonceEncrypted;

    public String mSecret;

    //ReassuranceMsg(String userId, String nonce) throws GeneralSecurityException {
    ReassuranceMsg(ConfessionMsg confessionMsg, String secret) throws GeneralSecurityException {
        super("reassurance");
        mUserId = confessionMsg.mUserId;
        mNonce = confessionMsg.mNonce;
        mSecret = secret;

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
        if (mSecret != null)
            jsonReassuranceMsg.put("secret", mSecret);
        return jsonReassuranceMsg.toJSONString();
    }
}
