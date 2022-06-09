import java.util.HashMap;
import java.util.LinkedList;

class InstanceList {

    // 区分攻击者 跟 罗密欧(至于罗密欧是否盗版,不重要也无法判别)

    // 这个哈希表需要定时清理,不然里面的条目越来越多
    private HashMap<String, InstanceInfo> mMap = new HashMap<String, InstanceInfo>();

    // 不只是为了记住谁是最老的实例,这个列表里的实例都是secret成功验证过的,要控制这个列表的长度
    private LinkedList<String> mVerifiedInstanceList = new LinkedList<String>();

    boolean has(String instanceId) {
        return mMap.get(instanceId) != null;
    }

    InstanceInfo getInstanceInfo(String instanceId) {
        return mMap.get(instanceId);
    }

    int verifiedInstanceTotalNumber() {
        return mVerifiedInstanceList.size();
    }

    InstanceInfo add(String instanceId) {
        InstanceInfo instanceInfo = new InstanceInfo();
        mMap.put(instanceId, instanceInfo);
        //mVerifiedUserList.offer(instanceId);
        return instanceInfo;
    }

    void removeEldest() {
        String eldestInstanceId = mVerifiedInstanceList.getFirst();
        mVerifiedInstanceList.removeFirst();
        mMap.remove(eldestInstanceId);
    }

    String getHtmlDesc(String indent) {
        String desc = "";
        for (HashMap.Entry<String, InstanceInfo> instance : mMap.entrySet()) {
            String instanceId = instance.getKey();
            InstanceInfo instanceInfo = instance.getValue();
            String secret = instanceInfo.mSecret;

            desc += indent;
            if (instanceInfo.mIsSecretVerified)
                desc += "<b>";
            desc += "instance ID:" + instanceId;
            desc += "\tsecret: " + secret;
            if (instanceInfo.mIsSecretVerified)
                desc += "</b>";
            desc += "<br/>";
        }
        return desc;    }

    void promoteToVerifiedInstance(String instanceId) {
        mVerifiedInstanceList.add(instanceId);
    }
}
