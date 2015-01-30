#include <sbinder/ICallbackList.h>
#include <utils/Log.h>

using namespace android;

ICallbackList::ICallbackList()
    :_mutex("ICallbackList") {

}

ICallbackList::~ICallbackList() {
    _CBList.clear();
}


bool ICallbackList::addCallback(sp<ICallbackList::ICallback> callback) {
    if(callback == NULL) {
        ALOGW("%s callback null",__FUNCTION__);
        return false;
    }

    Mutex::Autolock _l(_mutex);
    _CBList.add(callback);
    return true;
}

bool ICallbackList::removeCallback(sp<ICallbackList::ICallback> callback) {
    if(callback == NULL) {
        ALOGW("%s callback null",__FUNCTION__);
        return false;
    }

    Mutex::Autolock _l(_mutex);
    int size = _CBList.size();
    for(int i=0;i<size;i++) {
        sp<ICallbackList::ICallback> cb = _CBList[i];
        if(cb == callback) {
            _CBList.removeAt(i);
            return true;
        }

    }
    
    ALOGW("%s not found",__FUNCTION__);
    return false;
}

sp<ICallbackList::ICallback> ICallbackList::findCallback(void* callback,void* cookie) {
    if(callback == NULL) {
        ALOGW("%s callback null",__FUNCTION__);
        return NULL;
    }

    Mutex::Autolock _l(_mutex);
    int size = _CBList.size();
    for(int i=0;i<size;i++) {
        sp<ICallbackList::ICallback> cb = _CBList[i];
        if(cb != NULL && cb->_callback == callback && cb->_cookie == cookie) {
            return cb;
        }

    }

    ALOGW("%s not found",__FUNCTION__);
    return NULL;
}
