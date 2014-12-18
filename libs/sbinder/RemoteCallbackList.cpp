#include <sbinder/RemoteCallbackList.h>
#include <utils/Log.h>

namespace android {



class RemoteCallback : public IBinder::DeathRecipient,public virtual RefBase {

public:
    RemoteCallback(sp<RemoteCallbackList> parent,sp<IBinder> binder,void* cookie) {
        _parent = parent;
        _binder = binder;
        _cookie = cookie;
    }

    ~RemoteCallback() {
        _parent = NULL;
        _binder = NULL;
        _cookie = NULL;
    }

    void binderDied(const wp<IBinder>& who) {
        _parent->unregisterCallback(_binder);
        _parent->onCallbackDied(_binder,_cookie);
    }

    sp<RemoteCallbackList> _parent;
    sp<IBinder> _binder;
    void* _cookie;
};

RemoteCallbackList::RemoteCallbackList()
    :_mutex("RemoteCallbackList"),_killed(false) {
    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    for(int i=0;i<size;i++) {
        _callbacks[i] = NULL;
    }
}

RemoteCallbackList::~RemoteCallbackList() {
    kill();
}


bool RemoteCallbackList::registerCallback(sp<IBinder> binder,void* cookie) {
    if(binder == NULL) {
        ALOGW("%s binder null",__FUNCTION__);
        return false;
    }

    Mutex::Autolock _l(_mutex);
    if(_killed) {
        return false;
    }

    sp<RemoteCallback> cb = new RemoteCallback(this,binder,cookie);
    binder->linkToDeath(cb);

    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    int i;
    for(i=0;i<size;i++) {
        if(_callbacks[i] == NULL) {
            _callbacks[i] = cb;
            break;
        }
    }
    if(i >= size) {
        ALOGW("%s no space left",__FUNCTION__);
        return false;
    }

    return true;
}


bool RemoteCallbackList::unregisterCallback(sp<IBinder> binder) {
    if(binder == NULL) {
        ALOGW("%s binder null",__FUNCTION__);
        return false;
    }

    Mutex::Autolock _l(_mutex);
    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    for(int i=0;i<size;i++) {
        if(_callbacks[i] != NULL && _callbacks[i]->_binder == binder) {
            _callbacks[i]->_binder->unlinkToDeath(_callbacks[i]);
            _callbacks[i] = NULL;
            return true;
        }
    }

    ALOGW("%s binder not found",__FUNCTION__);
    return false;
}

void RemoteCallbackList::kill() {
    Mutex::Autolock _l(_mutex);

    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    for(int i=0;i<size;i++) {
        if(_callbacks[i] != NULL) {
            _callbacks[i]->_binder->unlinkToDeath(_callbacks[i]);
            _callbacks[i] = NULL;
        }
    }
    _killed = true;

}

int RemoteCallbackList::beginBroadcast() {
    Mutex::Autolock _l(_mutex);

    if(_activeCBs[0] != NULL) {
        ALOGW("%s called while already in a broadcast",__FUNCTION__);
        return -1;
    }

    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    int j=0;
    for(int i=0;i<size;i++) {
        if(_callbacks[i] != NULL) {
            _activeCBs[j++] = _callbacks[i];
        }
    }

    return j;
}

void RemoteCallbackList::finishBroadcast() {
    Mutex::Autolock _l(_mutex);
    if(_activeCBs[0] == NULL) {
        ALOGW("%s called outside of a broadcast",__FUNCTION__);
        return;
    }
    int size = sizeof(_activeCBs)/sizeof(_activeCBs[0]);
    for(int i=0;i<size;i++) {
        _activeCBs[i] = NULL;
    }
}

sp<IBinder> RemoteCallbackList::getBroadcastItem(int index) {
    Mutex::Autolock _l(_mutex);

    int size = sizeof(_activeCBs)/sizeof(_activeCBs[0]);
    if(index >= 0 && index < size && _activeCBs[index] != NULL) {
        return _activeCBs[index]->_binder;
    }

    return NULL;
}

void* RemoteCallbackList::getBroadcastCookie(int index) {
    Mutex::Autolock _l(_mutex);

    int size = sizeof(_activeCBs)/sizeof(_activeCBs[0]);
    if(index >= 0 && index < size && _activeCBs[index] != NULL) {
        return _activeCBs[index]->_cookie;
    }

    return NULL;
}

int RemoteCallbackList::getRegisteredCallbackCount() {
    Mutex::Autolock _l(_mutex);

    int size = sizeof(_callbacks)/sizeof(_callbacks[0]);
    int count=0;
    for(int i=0;i<size;i++) {
        if(_callbacks[i] != NULL) {
            count++;
        }
    }

    return count;
}


}