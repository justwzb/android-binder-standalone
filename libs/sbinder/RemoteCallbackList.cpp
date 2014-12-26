#include <sbinder/RemoteCallbackList.h>
#include <utils/Log.h>

namespace android {



class RemoteCallback : public IBinder::DeathRecipient,public virtual RefBase {

public:
    RemoteCallback(RemoteCallbackList* parent,sp<IBinder> binder,void* cookie) {
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

    RemoteCallbackList* _parent;
    sp<IBinder> _binder;
    void* _cookie;
};

RemoteCallbackList::RemoteCallbackList()
    :_mutex("RemoteCallbackList")
    ,_killed(false)
    ,_callbacks(NULL)
    ,_activeCBsList(NULL){
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

    if(_callbacks.add(binder,cb) >= 0) {
        return true;
    }

    ALOGW("%s register failed",__FUNCTION__);
    return false;
}


bool RemoteCallbackList::unregisterCallback(sp<IBinder> binder) {
    if(binder == NULL) {
        ALOGW("%s binder null",__FUNCTION__);
        return false;
    }

    Mutex::Autolock _l(_mutex);
    ssize_t idx = _callbacks.indexOfKey(binder);
    if(idx >= 0) {
        _callbacks[idx]->_binder->unlinkToDeath(_callbacks[idx]);
        _callbacks.removeItem(binder);
        return true;
    }

    ALOGW("%s binder not found",__FUNCTION__);
    return false;
}

void RemoteCallbackList::kill() {
    Mutex::Autolock _l(_mutex);

    int size = _callbacks.size();
    for(int i=0;i<size;i++) {
        sp<RemoteCallback> rc = _callbacks.valueAt(i);
        rc->_binder->unlinkToDeath(rc);
    }
    _callbacks.clear();
    _killed = true;
}

int RemoteCallbackList::beginBroadcast() {
    Mutex::Autolock _l(_mutex);
	
	DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> >* pActiveCBs = _activeCBsList.valueFor(pthread_self());
	if(pActiveCBs != NULL) {
        ALOGW("%s called while already in a broadcast\n",__FUNCTION__);
        return -1;
	}

	pActiveCBs = new DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> >;
	if(pActiveCBs == NULL) {
		ALOGW("[%s]out of memory\n",__FUNCTION__);
		return -2;
	}
	
    int size = _callbacks.size();
    for(int i=0;i<size;i++) {
        pActiveCBs->add(_callbacks.keyAt(i),_callbacks[i]);
    }
	_activeCBsList.add(pthread_self(),pActiveCBs);
    return size;
}

void RemoteCallbackList::finishBroadcast() {
    Mutex::Autolock _l(_mutex);

	DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> >* pActiveCBs =_activeCBsList.valueFor(pthread_self());
	if(pActiveCBs == NULL) {
        ALOGW("%s called outside of a broadcast",__FUNCTION__);
        return;
	}

	pActiveCBs->clear();
	_activeCBsList.removeItem(pthread_self());

	delete pActiveCBs;
	pActiveCBs = NULL;
}

sp<IBinder> RemoteCallbackList::getBroadcastItem(int index) {
    Mutex::Autolock _l(_mutex);

	DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> >* pActiveCBs =_activeCBsList.valueFor(pthread_self());

	if (pActiveCBs == NULL || pActiveCBs->size() <= 0){
		ALOGE("%s activeCBs null\n",__FUNCTION__);
		return NULL;
	}

    int size = pActiveCBs->size();
    if(index >= 0 && index < size && pActiveCBs->valueAt(index)!= NULL) {
        return pActiveCBs->valueAt(index)->_binder;
    }

    ALOGW("%s out of border",__FUNCTION__);
    return NULL;
}

void* RemoteCallbackList::getBroadcastCookie(int index) {
    Mutex::Autolock _l(_mutex);
	
	DefaultKeyedVector< wp<IBinder>, sp<RemoteCallback> >* pActiveCBs =_activeCBsList.valueFor(pthread_self());

	if (pActiveCBs == NULL || pActiveCBs->size() <= 0){
		ALOGE("%s activeCBs null\n",__FUNCTION__);
		return NULL;
	}

    int size = pActiveCBs->size();
    if(index >= 0 && index < size && pActiveCBs->valueAt(index)!= NULL) {
        return pActiveCBs->valueAt(index)->_cookie;
    }

    ALOGW("%s out of border",__FUNCTION__);
    return NULL;
}

int RemoteCallbackList::getRegisteredCallbackCount() {
    Mutex::Autolock _l(_mutex);

    return _callbacks.size();
}

}