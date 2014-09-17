/*py
import os
py*/

/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: %=filename%
 */
#define LOG_TAG     "%=basename%"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "%=filename%"

#define SERVICE_NAME                            "%=basename%"

#define FIRST_CALL_TRANSACTION                  (1)
/*py
idx = 0
for func in functionslist:
    idx += 1
    print("#define TRANSACTION_%s FIRST_CALL_TRANSACTION + %d\r\n" % (func["name"],idx))
py*/

using namespace android;

#if defined(BINDER_SERVICE)

#include "remote_%=basename%.h"

class remote_%=basename%_service : public BBinder  
{  
private:
    static remote_%=basename%_service* _instance;

    remote_%=basename%_service(){
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~remote_%=basename%_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_%=basename%_service();
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
/*py

for func in functionslist:
    print("""
            case TRANSACTION_%(funcname)s:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- add you code for %(funcname)s here --

                

                //-- add you code for %(funcname)s here --

                return NO_ERROR;
            } break;
            """ % {"funcname":func["name"]})
py*/
                
#if 0
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
#endif
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int remote_%=basename%_service_serv()
{
    sp<ProcessState> proc(ProcessState::self());

    int ret = remote_%=basename%_service::Instance();
    ALOGV("server - remote_%=basename%_service::Instance return %d\n", ret);

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...\n");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return \n");
    return 0;
}

int remote_%=basename%_service_add() {
    remote_%=basename%_service::Instance();
}

#elif defined(BINDER_CLIENT)

class remote_%=basename%_client  
{  
private:
    static remote_%=basename%_client* _instance;
    sp<IBinder> _binder;

    remote_%=basename%_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_%=basename%_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

public:  
    static remote_%=basename%_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new remote_%=basename%_client();
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
    return remote_%=basename%_client::Instance()->sample_base_api(in,out);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
