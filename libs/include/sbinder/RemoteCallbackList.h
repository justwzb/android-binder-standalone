/**
C++ version of RemoteCallbackList.
added in binder-standalone
*/

#ifndef ANDROID_REMOTECALLBACKLIDT_H
#define ANDROID_REMOTECALLBACKLIDT_H


#include <binder/IBinder.h>
#include <utils/StrongPointer.h>
#include <utils/Mutex.h>

namespace android {

class RemoteCallback;

class RemoteCallbackList : public virtual RefBase {

public:
    RemoteCallbackList();
    virtual ~RemoteCallbackList();

    bool registerCallback(sp<IBinder> binder,void* cookie);
    bool unregisterCallback(sp<IBinder> binder);
    void kill();

    int beginBroadcast();
    void finishBroadcast();

    sp<IBinder> getBroadcastItem(int index);
    void* getBroadcastCookie(int index);

    int getRegisteredCallbackCount();

    virtual void onCallbackDied(sp<IBinder> binder,void* cookie) {}


private:
    Mutex _mutex;
    bool _killed;
    sp<RemoteCallback> _callbacks[16]; //TODO: use list or hash table
    sp<RemoteCallback> _activeCBs[16]; //TODO: use list or hash table


};

}   // namespace

#endif // ANDROID_REMOTECALLBACKLIDT_H