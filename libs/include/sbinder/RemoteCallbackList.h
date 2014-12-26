/**
C++ version of RemoteCallbackList.
added in binder-standalone
*/

#ifndef ANDROID_REMOTECALLBACKLIDT_H
#define ANDROID_REMOTECALLBACKLIDT_H


#include <binder/IBinder.h>
#include <utils/StrongPointer.h>
#include <utils/Mutex.h>
#include <utils/KeyedVector.h>
#include <pthread.h>

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
    DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> > _callbacks;
    DefaultKeyedVector<pthread_t,DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback > >* > _activeCBsList;

};

}   // namespace

#endif // ANDROID_REMOTECALLBACKLIDT_H