#define LOG_TAG     "remote_sample_module"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "sample_module.h"

#define SERVICE_NAME                            "remote_sample_module"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_remote_sample_base_api      FIRST_CALL_TRANSACTION + 1
#define TRANSACTION_remote_sample_ptr_api       FIRST_CALL_TRANSACTION + 2
#define TRANSACTION_remote_sample_st_api        FIRST_CALL_TRANSACTION + 3
#define TRANSACTION_remote_sample_handle_api    FIRST_CALL_TRANSACTION + 4
#define TRANSACTION_remote_sample_void_api      FIRST_CALL_TRANSACTION + 5

using namespace android;

#if defined(BINDER_SERVICE)

#include "remote_sample_module.h"

class remote_sample_module_service : public BBinder  
{  
private:
    static remote_sample_module_service* _instance;

    remote_sample_module_service(){
        ALOGV(SERVICE_NAME"_service create\n");
    }
    
    virtual ~remote_sample_module_service() {
        ALOGV(SERVICE_NAME"_service destory\n");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_sample_module_service();
            int ret = defaultServiceManager()->addService(  
                String16(SERVICE_NAME), _instance );  
            ALOGV(SERVICE_NAME"_service ret = %d\n", ret);  
            return ret;  
        }

        return -1;
    }
    
    virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
        ALOGV(SERVICE_NAME"_service - onTransact code=%d",code);

        switch(code)  {
            case TRANSACTION_remote_sample_base_api:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                /*-- add you code for sample_base_api here --*/
                int in = data.readInt32();  //int as input paramter

                //int as output paramter ( with a length header )
                int* pout;
                int out;
                int out_length = data.readInt32();
                if(out_length >= 0) {
                    pout = &out;
                    out = data.readInt32();
                }
                else {
                    pout = NULL;
                }

                int _result = sample_base_api(in,pout);

                reply->writeNoException(); //fixed check

                reply->writeInt32(_result); //int as return value

                //int as output paramter
                if(out_length >= 0) {
                    reply->writeInt32(out); 
                }
                /*-- add you code for sample_base_api here --*/

                return NO_ERROR;
            } break;

            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int remote_sample_module_service_serv()
{
    sp<ProcessState> proc(ProcessState::self());

    int ret = remote_sample_module_service::Instance();
    ALOGV("server - remote_sample_module_service::Instance return %d\n", ret);

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...\n");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return \n");
    return 0;
}

int remote_sample_module_service_add() {
    remote_sample_module_service::Instance();
}

#elif defined(BINDER_CLIENT)

class remote_sample_module_client  
{  
private:
    static remote_sample_module_client* _instance;
    sp<IBinder> _binder;

    remote_sample_module_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_sample_module_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

public:  
    static remote_sample_module_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new remote_sample_module_client();
        }

        return _instance;
    }

    int sample_base_api(int in,int* out) {
        Parcel data, reply;

        /*-- add you code for sample_base_api here --*/
        int _result = -1; //default error value
        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(in);//int as input paramter

            //int as output paramter ( with a length header )
            if(out != NULL) {
                data.writeInt32(sizeof(int));
                data.writeInt32(*out);
            }
            else {
                data.writeInt32(-1);
            }

            _binder->transact(TRANSACTION_remote_sample_base_api,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
                _result = reply.readInt32();//int as return value

                //int as output paramter(always write)
                if(out != NULL) {
                    *out = reply.readInt32();
                }
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client sample_base_api error");
        }

        return _result;
        /*-- add you code for sample_base_api here --*/
    }
};

int sample_base_api(int in,int* out) {
    return remote_sample_module_client::Instance()->sample_base_api(in,out);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
