/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_sample_module.sidl
 */

#define LOG_TAG     "remote_sample_module"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "sample_module.h"


#define SERVICE_DESCRIPTOR                      "851ecc51-3fe5-11e4-83b8-7831c1c50d90"
#define SERVICE_NAME                            "remote_sample_module"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_sample_base_api FIRST_CALL_TRANSACTION + 1

using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_sample_module.h"

class remote_sample_module_service : public BBinder  
{  
private:
    static remote_sample_module_service* _instance;

    remote_sample_module_service(){
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~remote_sample_module_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_sample_module_service();
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

            case TRANSACTION_sample_base_api:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for sample_base_api here, will auoto generated but may change yourself if need --

                int in = data.readInt32();  //int as input paramter

                //TODO: use blob
                int _in1_len = data.readInt32(); //read length
                int* in1 = (int*)malloc(sizeof(int)*_in1_len);
                data.read(%(name)s,sizeof(%(typ)s)*_%(name)s_len)

                //TODO: use blob
                int _inout1_len = data.readInt32(); //read length
                int* inout1 = (int*)malloc(sizeof(int)*_inout1_len);
                data.read(%(name)s,sizeof(%(typ)s)*_%(name)s_len)

                //TODO: use blob
                int _out1_len = data.readInt32(); //read length
                int* out1 = (int*)malloc(sizeof(int)*_out1_len);
                memset(out1,0,sizeof(int)*_out1_len);

                //TODO: use blob
                int _inoutlen_len = data.readInt32(); //read length
                int* inoutlen = (int*)malloc(sizeof(int)*_inoutlen_len);
                data.read(%(name)s,sizeof(%(typ)s)*_%(name)s_len)

                int len = data.readInt32();  //int as input paramter

                int _result = sample_base_api_stub( in, in1, inout1, out1, inoutlen, len );

                reply->writeNoException(); //fixed check

                reply->writeInt32(_result); //int as return value

                free(in1);
                in1 = NULL;

                //TODO: use blob
                reply->writeInt32Array(_inout1_len,inout1);
                free(inout1);
                inout1 = NULL;

                //TODO: use blob
                reply->writeInt32Array(_out1_len,out1);
                free(out1);
                out1 = NULL;

                //TODO: use blob
                reply->writeInt32Array(_inoutlen_len,inoutlen);
                free(inoutlen);
                inoutlen = NULL;

                //-- end code for sample_base_api here --
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
    ALOGV("server - remote_sample_module__service::Instance return %d", ret);

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return");
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

    int sample_base_api( int in, int* in1, int* inout1, int* out1, int* inoutlen, int len ) {
        Parcel data, reply;

        /*-- add you code for sample_base_api here --*/
        int _result;
        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(in);  //int as input paramter

            data.writeInt32Array(1, in1);  //int* as input paramter

            data.writeInt32Array(1, inout1);  //int* as input paramter

            if ( out1 == NULL ) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(len);
            }

            data.writeInt32Array(len, inoutlen);  //int* as input paramter

            data.writeInt32(len);  //int as input paramter

            _binder->transact(TRANSACTION_sample_base_api,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = reply.readInt32();//int as return value

                reply.readInt32Array(1,inout1); //TODO need add this api

                reply.readInt32Array(len,out1); //TODO need add this api

                reply.readInt32Array(len,inoutlen); //TODO need add this api

            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client sample_base_api error");
        }

        return _result;
        /*-- add you code for sample_base_api here --*/
    }
};

int sample_base_api( int in, int* in1, int* inout1, int* out1, int* inoutlen, int len ) {
    return remote_sample_module_client*::Instance->sample_base_api(in, in1, inout1, out1, inoutlen, len);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
