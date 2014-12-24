/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_callback_module.sidl
 */
 

#define LOG_TAG     "remote_callback_module"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/Mutex.h>

#include "callback_module.h"


#define SERVICE_DESCRIPTOR                      "f09d65ae-8687-11e4-ac97-7831c1c50d90"
#define SERVICE_NAME                            "remote_callback_module"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_cb_add FIRST_CALL_TRANSACTION + 1
#define TRANSACTION_cb_remove FIRST_CALL_TRANSACTION + 2
#define TRANSACTION_cb_invoke FIRST_CALL_TRANSACTION + 3


#define FIRST_CALLBACK_TRANSACTION                  (1)
#define TRANSACTION_CALLBACK_callback FIRST_CALLBACK_TRANSACTION + 1

using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_callback_module.h"
#include <sbinder/RemoteCallbackList.h>
#include <utils/KeyedVector.h>

class remote_callback_module_service : public BBinder  
{  
private:
    static remote_callback_module_service* _instance;

    RemoteCallbackList _cbList;
    bool _first;

    remote_callback_module_service()
        :_first(true) {
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~remote_callback_module_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

    static int module_callback(int param) {
        RemoteCallbackList* rcbl = &(_instance->_cbList);
        int _result = 0;
        int size = rcbl->beginBroadcast();
        for(int i=0;i<size;i++) {

            sp<IBinder> binder = rcbl->getBroadcastItem(i);

            if(binder != NULL) {
                Parcel data, reply;
                data.writeInterfaceToken(String16(SERVICE_NAME"_callback"));
                data.writeInt32(param);
                binder->transact(TRANSACTION_CALLBACK_callback, data, &reply, 0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result += reply.readInt32();//int as return value
                }
            }
        }
        rcbl->finishBroadcast();

        return _result;
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_callback_module_service();
            int ret = defaultServiceManager()->addService(  
                String16(SERVICE_NAME), _instance );  
            ALOGV(SERVICE_NAME"_service ret = %d", ret);  
            return ret;  
        }

        return -1;
    }
    
    virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
        ALOGV(SERVICE_NAME"_service - onTransact code=%d",code);

        switch(code)  {

            case TRANSACTION_cb_add:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for cb_add here, will auoto generated but may change yourself if need --
                sp<IBinder> binder = data.readStrongBinder();

                if(binder != NULL) {

                    int _result = 0;
                        
                    if(_first) {
                        _result = cb_add(remote_callback_module_service::module_callback);
                        if(_result == 0) {
                            _first = true;
                        }
                    }

                    if(_result == 0) {
                        if(_cbList.registerCallback(binder,NULL)) {
                            reply->writeNoException();
                            reply->writeInt32(_result); //int as return value
                        }
                        else {
                            reply->writeInt32(-3);//Exception
                        }
                    }
                    else {
                        reply->writeInt32(-2);//Exception
                    }
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                //-- end code for cb_add here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_cb_remove:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for cb_remove here, will auoto generated but may change yourself if need --
                sp<IBinder> binder = data.readStrongBinder();

                if(_cbList.unregisterCallback(binder)) {
                    reply->writeNoException();
                    reply->writeInt32(0);//result
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                //-- end code for cb_remove here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_cb_invoke:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for cb_invoke here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int p = (int)data.readInt32();  //int as input paramter

                int _result = cb_invoke( p );

                reply->writeInt32(_result); //int as return value

                //-- end code for cb_invoke here --
                return NO_ERROR;
            } break;
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int remote_callback_module_service_serv()
{
    sp<ProcessState> proc(ProcessState::self());

    int ret = remote_callback_module_service::Instance();
    ALOGV("server - remote_callback_module__service::Instance return %d", ret);

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return");
    return 0;
}

int remote_callback_module_service_add() {
    remote_callback_module_service::Instance();
}

remote_callback_module_service* remote_callback_module_service::_instance = NULL;

#elif defined(BINDER_CLIENT)

class remote_callback_module_client  
{  
private:
    static remote_callback_module_client* _instance;
    sp<IBinder> _binder;

    remote_callback_module_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_callback_module_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

    class Callback : public BBinder {
    public:
        Callback(cb_callback cb) {
            ALOGV(SERVICE_NAME"_client callback %p-%p create\n",this,cb);
            _descriptor = String16(SERVICE_NAME"_callback");
            _callback = cb;
            _userdata = NULL;
        }

        ~Callback() {
            ALOGV(SERVICE_NAME"_client callback %p-%p destory\n",this,_callback);
            Callback::removeCb(this);//for safe
            _callback = NULL;
            _userdata = NULL;
        }

        virtual status_t onTransact( uint32_t code,
                const Parcel& data,Parcel* reply,uint32_t flags = 0) {
            ALOGV(SERVICE_NAME"_client onTransact code=%d\n",code);

            switch (code){
            case TRANSACTION_CALLBACK_callback:
            {
                if (!data.checkInterface(this)) {
                    ALOGW(SERVICE_NAME"_client onTransact Interface error\n");
                    return -1;
                }

                if(_callback != NULL) {
                    int param = (int)data.readInt32();  //int as input paramter

                    int _result = _callback(param);

                    reply->writeNoException();
                    reply->writeInt32(_result);
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                break;
            }

            default:
                return BBinder::onTransact(code, data, reply, flags);
            }

            return NO_ERROR;
        }

        virtual const String16& getInterfaceDescriptor() const{
            return _descriptor;
        }

        static sp<Callback> findCb(cb_callback cb) {
            Mutex::Autolock _l(_mutex);

            return _CBList.valueFor(cb);
        }

        static void addCb(sp<Callback> cb) {
            Mutex::Autolock _l(_mutex);

            _CBList.add(cb->_callback,cb);
        }

        static void removeCb(sp<Callback> cb) {
            Mutex::Autolock _l(_mutex);

            _CBList.removeItem(cb->_callback);
        }

    private:
        cb_callback _callback;
        void* _userdata;
        String16 _descriptor;

        static Mutex _mutex;
        static KeyedVector< cb_callback, sp<Callback> > _CBList;
    };

public:  
    static remote_callback_module_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new remote_callback_module_client();
        }

        return _instance;
    }

    int cb_add( cb_callback cb ) {
        Parcel data, reply;

        /*-- add you code for cb_add here --*/
        int _result = -1;
        if(_binder == NULL || cb == NULL) {
            ALOGE(SERVICE_NAME"_client _binder or cb null");
            return _result;
        }

        if(Callback::findCb(cb) != NULL) {
            ALOGE(SERVICE_NAME"_client cb arleady added");
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            sp<Callback> ccb = new Callback(cb);
            data.writeStrongBinder(ccb);

            _binder->transact(TRANSACTION_cb_add,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
                _result = (typeof(_result))reply.readInt32();//int as return value

                if(_result == 0) { //success
                    Callback::addCb(ccb);
                }
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client cb_add error");
        }

        return _result;
        /*-- add you code for cb_add here --*/
    }

    int cb_remove( cb_callback cb ) {
        Parcel data, reply;

        /*-- add you code for cb_remove here --*/
        int _result = -1;
        if(_binder == NULL || cb == NULL) {
            ALOGE(SERVICE_NAME"_client _binder or cb null");
            return _result;
        }

        sp<Callback> ccb = Callback::findCb(cb);
        if( ccb == NULL) {
            ALOGE(SERVICE_NAME"_client cb not added");
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeStrongBinder(ccb);

            _binder->transact(TRANSACTION_cb_remove,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

                if(_result == 0) { //success
                    Callback::removeCb(ccb);
                }
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client cb_remove error");
        }

        return _result;
        /*-- add you code for cb_remove here --*/
    }

    int cb_invoke( int p ) {
        Parcel data, reply;

        /*-- add you code for cb_invoke here --*/
        int _result = -1;
        if(_binder == NULL) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(p);  //int as input paramter

            _binder->transact(TRANSACTION_cb_invoke,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client cb_invoke error");
        }

        return _result;
        /*-- add you code for cb_invoke here --*/
    }
};

remote_callback_module_client* remote_callback_module_client::_instance = NULL;
Mutex remote_callback_module_client::Callback::_mutex("Callback");
KeyedVector< cb_callback, sp<remote_callback_module_client::Callback> > remote_callback_module_client::Callback::_CBList;

int cb_add( cb_callback cb ) {
    return remote_callback_module_client::Instance()->cb_add(cb);
}
int cb_remove( cb_callback cb ) {
    return remote_callback_module_client::Instance()->cb_remove(cb);
}
int cb_invoke( int p ) {
    return remote_callback_module_client::Instance()->cb_invoke(p);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
