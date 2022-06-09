class InstanceInfo {
    String mSecret = "123";
    boolean mIsSecretVerified = false;
    InstanceInfo() {
        mSecret = String.valueOf(Math.random());
    }
}
