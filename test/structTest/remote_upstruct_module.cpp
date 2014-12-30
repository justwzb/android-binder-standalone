/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_upstruct_module.sidl
 */
 

#define LOG_TAG     "remote_upstruct_module"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "struct_module.h"


#define SERVICE_DESCRIPTOR                      "4ab7254a-81a9-11e4-8660-7831c1c50d90"
#define SERVICE_NAME                            "remote_upstruct_module"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_unflag_struct_api FIRST_CALL_TRANSACTION + 1

using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_upstruct_module.h"

class remote_upstruct_module_service : public BBinder  
{  
private:
    static remote_upstruct_module_service* _instance;

    remote_upstruct_module_service(){
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~remote_upstruct_module_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_upstruct_module_service();
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

            case TRANSACTION_unflag_struct_api:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for unflag_struct_api here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int _pin_count = data.readInt32(); //read count
                STRUCT_UNFLAT_S _pin_S;
                memset(&_pin_S,0,sizeof(_pin_S));

                STRUCT_UNFLAT_S* pin = NULL;
                if(_pin_count > 0) {
                    pin = &_pin_S;

                    pin->i = data.readInt32();
                    pin->j = data.readInt32();
                    pin->len = data.readInt32();

                    Parcel::ReadableBlob _pin_rblob;
                    data.readBlob(pin->len,&_pin_rblob);
                    pin->buf = (char*)_pin_rblob.data();
                }

                //pout
                int _pout_len = data.readInt32(); //read count
                STRUCT_UNFLAT_S _pout_S;
                memset(&_pout_S,0,sizeof(_pout_S));

                STRUCT_UNFLAT_S* pout = NULL;
                if(_pin_count > 0) {
                    pout = &_pout_S;
                }

                int _result = unflag_struct_api( pin, pout );

                reply->writeInt32(_result); //int as return value

                //pout
                if(_pin_count > 0) {
                    reply->writeInt32(pout->i);
                    reply->writeInt32(pout->j);
                    reply->writeInt32(pout->len);

                    Parcel::WritableBlob _pout_wblob;
                    reply->writeBlob(pout->len,&_pout_wblob);
                    memcpy(_pout_wblob.data(),pout->buf,pout->len);
                }

                //-- end code for unflag_struct_api here --
                return NO_ERROR;
            } break;
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int remote_upstruct_module_service_add() {
    remote_upstruct_module_service::Instance();
}

remote_upstruct_module_service* remote_upstruct_module_service::_instance = NULL;

#elif defined(BINDER_CLIENT)

class remote_upstruct_module_client  
{  
private:
    static remote_upstruct_module_client* _instance;
    sp<IBinder> _binder;

    remote_upstruct_module_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_upstruct_module_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

public:  
    static remote_upstruct_module_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new remote_upstruct_module_client();
        }

        return _instance;
    }

    int unflag_struct_api( STRUCT_UNFLAT_S* pin, STRUCT_UNFLAT_S* pout ) {
        Parcel data, reply;

        /*-- add you code for unflag_struct_api here --*/
        int _result;
        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            //pin
            if (pin == NULL) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(1);//write count

                data.writeInt32(pin->i);
                data.writeInt32(pin->j);
                data.writeInt32(pin->len);

                Parcel::WritableBlob _pin_wblob;
                data.writeBlob(pin->len,&_pin_wblob);
                memcpy(_pin_wblob.data(),pin->buf,pin->len);
            }

            //pout, only write count
            if (pout == NULL) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(1);
            }

            _binder->transact(TRANSACTION_unflag_struct_api,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();

                if (pout != NULL) {

                    pout->i = reply.readInt32();
                    pout->j = reply.readInt32();
                    pout->len = reply.readInt32();

                    Parcel::ReadableBlob _pout_rblob;
                    reply.readBlob(pout->len,&_pout_rblob);

                    pout->buf = (char*)_pout_rblob.data();//not work, _pin_wblob.data() will be release on return, only demo here

                    pout->buf = NULL;
                }
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client sample_base_api error");
        }

        return _result;
        /*-- add you code for sample_base_api here --*/
    }
};

remote_upstruct_module_client* remote_upstruct_module_client::_instance = NULL;

int unflag_struct_api( STRUCT_UNFLAT_S* pin, STRUCT_UNFLAT_S* pout ) {
    return remote_upstruct_module_client::Instance()->unflag_struct_api(pin, pout);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
