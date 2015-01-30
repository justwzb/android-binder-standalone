/**
Class helps to save and map c callbacks and BBinders
added in binder-standalone
*/

#ifndef ANDROID_ICALLBACKLIDT_H
#define ANDROID_ICALLBACKLIDT_H

#include <binder/Binder.h>
#include <utils/StrongPointer.h>
#include <utils/Mutex.h>
#include <utils/Vector.h>

namespace android {

class ICallbackList {

public:
    class ICallback : public BBinder {
    friend class ICallbackList;
    public:
        ICallback(void* callback,void* cookie)
            :_callback(callback)
            ,_cookie(cookie) {
            ALOGV("%s client %p-%p create\n",__FUNCTION__,_callback,_cookie);
        }

        ~ICallback() {
            ALOGV("%s client %p-%p destory\n",(char*)_descriptor.string(),_callback,_cookie);
        }

        virtual const String16& getInterfaceDescriptor() const {
            return _descriptor;
        }

    protected:
        void* _callback;
        void* _cookie;
        String16 _descriptor;
    };

    ICallbackList();
    virtual ~ICallbackList();

    bool addCallback(sp<ICallbackList::ICallback> callback);
    bool removeCallback(sp<ICallbackList::ICallback> callback);
    sp<ICallbackList::ICallback> findCallback(void* callback,void* cookie);

private:
    Mutex _mutex;
    Vector< sp<ICallbackList::ICallback> > _CBList;
};

}   // namespace

#endif // ANDROID_ICALLBACKLIDT_H
