import java.util.HashMap;
import java.util.LinkedList;

class InstanceList {
    HashMap<String, InstanceInfo> mMap = new HashMap<String, InstanceInfo>();
    LinkedList<String> mList = new LinkedList<String>(); // 为了记住谁是最老的实例

    boolean has(String instanceId) {
        return mMap.get(instanceId) != null;
    }

    InstanceInfo getInstanceInfo(String instanceId) {
        return mMap.get(instanceId);
    }

    int size() {
        return mMap.size();
    }

    InstanceInfo add(String instanceId) {
        InstanceInfo instanceInfo = new InstanceInfo();
        mMap.put(instanceId, instanceInfo);
        mList.offer(instanceId);
        return instanceInfo;
    }

    void removeEldest() {
        String eldestInstanceId = mList.getFirst();
        mList.removeFirst();
        mMap.remove(eldestInstanceId);
    }

}
