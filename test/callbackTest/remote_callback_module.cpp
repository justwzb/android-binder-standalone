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
#define TRANSACTION_cb_invoke2 FIRST_CALL_TRANSACTION + 4 


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

        ALOGV(SERVICE_NAME"_service module_callback end");
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
                            _first = false;
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
            } break;

            case TRANSACTION_cb_invoke2:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                reply->writeNoException();

                int p = (int)data.readInt32();  //int as input paramter

                int _result = cb_invoke2( p );

                reply->writeInt32(_result); //int as return value

            } break;			
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
        return NO_ERROR;
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

#include <sbinder/ICallbackList.h>

class remote_callback_module_client  
{  
private:
    static remote_callback_module_client* _instance;
    sp<IBinder> _binder;
    ICallbackList _CBList;

    remote_callback_module_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_callback_module_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

    class Callback : public ICallbackList::ICallback {
    public:
        Callback(void* cb,void* cookie)
            :ICallback(cb,cookie) {
            _descriptor = String16(SERVICE_NAME"_callback");
        }

        ~Callback() {
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

                    int _result = ((cb_callback)_callback)(param);

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

        if(_CBList.findCallback((void*)cb,NULL) != NULL) {
            ALOGE(SERVICE_NAME"_client cb arleady added");
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            sp<Callback> ccb = new Callback((void*)cb,NULL);
            data.writeStrongBinder(ccb);

            _binder->transact(TRANSACTION_cb_add,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
                _result = (typeof(_result))reply.readInt32();//int as return value

                if(_result == 0) { //success
                    _CBList.addCallback(ccb);
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

        sp<ICallbackList::ICallback> ccb = _CBList.findCallback((void*)cb,NULL);
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
                    _CBList.removeCallback(ccb);
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

	int cb_invoke2( int p ) {
		
		Parcel data, reply;

		int _result = -1;
		if(_binder == NULL) {
			return _result;
		}

		try {
			data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

			data.writeInt32(p);  //int as input paramter

			_binder->transact(TRANSACTION_cb_invoke2,data, &reply,0);

			if(reply.readExceptionCode() == 0) {//fix check

				_result = (typeof(_result))reply.readInt32();//int as return value

			}
		}catch(...) {
			ALOGE(SERVICE_NAME"_client cb_invoke error");
		}

		return _result;
		/*-- add you code for cb_invoke here --*/
	}


	
};

remote_callback_module_client* remote_callback_module_client::_instance = NULL;

int cb_add( cb_callback cb ) {
    return remote_callback_module_client::Instance()->cb_add(cb);
}
int cb_remove( cb_callback cb ) {
    return remote_callback_module_client::Instance()->cb_remove(cb);
}
int cb_invoke( int p ) {
    return remote_callback_module_client::Instance()->cb_invoke(p);
}

int cb_invoke2( int p ) {
    return remote_callback_module_client::Instance()->cb_invoke2(p);
}


#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
