/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_buffer_module.sidl
 */
 

#define LOG_TAG     "remote_buffer_module"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "matrix_ringbuf.h"
#include "mhal_defines.h"


#define SERVICE_DESCRIPTOR                      "6baaef61-84d7-11e4-a55b-7831c1c50d90"
#define SERVICE_NAME                            "remote_buffer_module"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_matrix_ringbuf_init FIRST_CALL_TRANSACTION + 1
#define TRANSACTION_matrix_ringbuf_in FIRST_CALL_TRANSACTION + 2
#define TRANSACTION_matrix_ringbuf_out FIRST_CALL_TRANSACTION + 3
#define TRANSACTION_matrix_ringbuf_aquireIn FIRST_CALL_TRANSACTION + 4
#define TRANSACTION_matrix_ringbuf_aquireOut FIRST_CALL_TRANSACTION + 5
#define TRANSACTION_matrix_ringbuf_confirmAquireIn FIRST_CALL_TRANSACTION + 6
#define TRANSACTION_matrix_ringbuf_confirmAquireOut FIRST_CALL_TRANSACTION + 7
#define TRANSACTION_matrix_ringbuf_skip FIRST_CALL_TRANSACTION + 8
#define TRANSACTION_matrix_ringbuf_getDataSize FIRST_CALL_TRANSACTION + 9
#define TRANSACTION_matrix_ringbuf_getFreeSize FIRST_CALL_TRANSACTION + 10
#define TRANSACTION_matrix_ringbuf_rewind FIRST_CALL_TRANSACTION + 11
#define TRANSACTION_matrix_ringbuf_reset FIRST_CALL_TRANSACTION + 12
#define TRANSACTION_matrix_ringbuf_exit FIRST_CALL_TRANSACTION + 13

using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_buffer_module.h"

class remote_buffer_module_service : public BBinder  
{  
private:
    static remote_buffer_module_service* _instance;

    remote_buffer_module_service(){
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~remote_buffer_module_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

	class serverData {
	private:
		void* magic;
	public:
		matrix_ringbuf_handle realHandle;
		Parcel::WritableBlob blob;

		serverData() {
			magic = this;
		}

		bool check() {
			return magic == this;
		}
	};

	
public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new remote_buffer_module_service();
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

            case TRANSACTION_matrix_ringbuf_init:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_init here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                unsigned int bufsize = (unsigned int)data.readInt32();  //unsigned int as input paramter

                serverData* sd = new serverData();
                reply->writePointer((intptr_t)sd);
                if(sd != NULL) {
                    reply->writeRBBlob(bufsize,&(sd->blob));
                
                    sd->realHandle = matrix_ringbuf_initwithbuffer(sd->blob.data(),bufsize);

                    if(sd->realHandle == NULL) {
                        reply->setDataPosition(0);
                        reply->writeNoException();
                        reply->writePointer((intptr_t)NULL);
                        delete sd;
                    }
                }
                //-- end code for matrix_ringbuf_init here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_aquireIn:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_aquireIn here, will auoto generated but may change yourself if need --

                //begin paramters list
                serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
	            	matrix_ringbuf_handle handle = sd->realHandle;

	                unsigned char* buf = NULL;
						
	                unsigned int _result = matrix_ringbuf_aquireIn( handle, &buf );

					if(buf >= (unsigned char*)sd->blob.data() && buf < (unsigned char*)sd->blob.data() + sd->blob.size()) {
						reply->writeNoException();
		            	reply->writeInt32(_result);

                        //write offset since the start addr in server & client may not same.
						reply->writeInt32((int32_t)(buf-(unsigned char*)sd->blob.data()));
					}
					else {
						reply->writeInt32(-2);//error buffer
					}
				}
				else {
					reply->writeInt32(-1);//error handle
				}

                //-- end code for matrix_ringbuf_aquireIn here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_aquireOut:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_aquireOut here, will auoto generated but may change yourself if need --

                //begin paramters list
                serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
	            	matrix_ringbuf_handle handle = sd->realHandle;

               		const unsigned char* buf = NULL;
                    unsigned int _result = matrix_ringbuf_aquireOut( handle, &buf );
					
					if(buf >= (unsigned char*)sd->blob.data() && buf < (unsigned char*)sd->blob.data() + sd->blob.size()) {
						reply->writeNoException();
		            	reply->writeInt32(_result);

                        //write offset since the start addr in server & client may not same.
						reply->writeInt32((int32_t)(buf-(unsigned char*)sd->blob.data()));
					}
					else {
						reply->writeInt32(-2);//error buffer
					}
				}
				else {
					reply->writeInt32(-1);//error handle
				}
                //-- end code for matrix_ringbuf_aquireOut here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_confirmAquireIn:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_confirmAquireIn here, will auoto generated but may change yourself if need --

                //begin paramters list
                serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
	            	matrix_ringbuf_handle handle = sd->realHandle;	
					unsigned int size = (unsigned int)data.readInt32();
					unsigned int _result = matrix_ringbuf_confirmAquireIn( handle, size );
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}
                //-- end code for matrix_ringbuf_confirmAquireIn here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_confirmAquireOut:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_confirmAquireOut here, will auoto generated but may change yourself if need --

                //begin paramters list
                serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
	            	matrix_ringbuf_handle handle = sd->realHandle;		
					unsigned int size = (unsigned int)data.readInt32();				
					unsigned int _result = matrix_ringbuf_confirmAquireOut( handle, size );
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}
                //-- end code for matrix_ringbuf_confirmAquireOut here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_skip:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_skip here, will auoto generated but may change yourself if need --

				//begin paramters list
			   serverData* sd = (serverData*)data.readPointer();
			   if(sd != NULL && sd->check()) {
				   reply->writeNoException();
				   matrix_ringbuf_handle handle = sd->realHandle;			   
				   unsigned int size = (unsigned int)data.readInt32();
				   unsigned int _result = matrix_ringbuf_skip( handle, size );
				   reply->writeInt32(_result);
			   }
			   else {
				   reply->writeInt32(-1);//error handle
			   }
                //-- end code for matrix_ringbuf_skip here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_getDataSize:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_getDataSize here, will auoto generated but may change yourself if need --

				 //begin paramters list
				serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
					matrix_ringbuf_handle handle = sd->realHandle;				
					unsigned int _result = matrix_ringbuf_getDataSize( handle);
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}
				//-- end code for matrix_ringbuf_getDataSize here --

                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_getFreeSize:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_getFreeSize here, will auoto generated but may change yourself if need --

				 //begin paramters list
				serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
					matrix_ringbuf_handle handle = sd->realHandle;				
					unsigned int _result = matrix_ringbuf_getFreeSize( handle);
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}

                //-- end code for matrix_ringbuf_getFreeSize here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_rewind:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_rewind here, will auoto generated but may change yourself if need --

				 //begin paramters list
				serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
					matrix_ringbuf_handle handle = sd->realHandle;
					unsigned int size = (unsigned int)data.readInt32();					
					unsigned int _result =matrix_ringbuf_rewind( handle, size );
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}

                //-- end code for matrix_ringbuf_rewind here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_reset:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_reset here, will auoto generated but may change yourself if need --

				 //begin paramters list
				serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
					matrix_ringbuf_handle handle = sd->realHandle;
					unsigned int _result =matrix_ringbuf_reset( handle );
					reply->writeInt32(_result);
				}
				else {
					reply->writeInt32(-1);//error handle
				}

                //-- end code for matrix_ringbuf_reset here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_matrix_ringbuf_exit:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for matrix_ringbuf_exit here, will auoto generated but may change yourself if need --

				 //begin paramters list
				serverData* sd = (serverData*)data.readPointer();
				if(sd != NULL && sd->check()) {
					reply->writeNoException();
					matrix_ringbuf_handle handle = sd->realHandle;
					unsigned int _result =matrix_ringbuf_exit( handle );
					reply->writeInt32(_result);
					delete sd;
				}
				else {
					reply->writeInt32(-1);//error handle
				}

                //-- end code for matrix_ringbuf_exit here --
                return NO_ERROR;
            } break;
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int remote_buffer_module_service_add() {
    remote_buffer_module_service::Instance();
}

remote_buffer_module_service* remote_buffer_module_service::_instance = NULL;

#elif defined(BINDER_CLIENT)

class remote_buffer_module_client  
{  
private:
    static remote_buffer_module_client* _instance;
    sp<IBinder> _binder;

    remote_buffer_module_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~remote_buffer_module_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

	class clientData {
	private:
		void* magic;
		
	public:
		intptr_t remoteHandle;
		Parcel::WritableBlob blob;

		clientData() {
			magic = this;
		}

		bool check() {
			return magic == this;
		}
	};

public:  
    static remote_buffer_module_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new remote_buffer_module_client();
        }

        return _instance;
    }

    matrix_ringbuf_handle matrix_ringbuf_init( unsigned int bufsize ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_init here --*/
        matrix_ringbuf_handle _result = NULL;
        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(bufsize);  //unsigned int as input paramter

            _binder->transact(TRANSACTION_matrix_ringbuf_init,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
                intptr_t remoteHandle = reply.readPointer();
                if(remoteHandle != (intptr_t)NULL) {
                    clientData* cd = new clientData();
                    
                    reply.readRBBlob((size_t)bufsize,&(cd->blob));
                    
                    cd->remoteHandle = remoteHandle;
                    _result = (matrix_ringbuf_handle)cd;
                }
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_init error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_init here --*/
    }

    unsigned int matrix_ringbuf_in( matrix_ringbuf_handle handle, unsigned char* buf, unsigned int size ) {
		unsigned int _result =0;

		if(handle != NULL && buf != NULL && size > 0) {
	  		unsigned char* ptr = NULL;
			unsigned int has = matrix_ringbuf_aquireIn(handle,&ptr);
			if (ptr !=NULL){
				size = MHAL_MIN(has,size);
				memcpy(ptr,buf,size);
				_result = matrix_ringbuf_confirmAquireIn(handle,size);
			}
		}
		return _result;
    }

    unsigned int matrix_ringbuf_out( matrix_ringbuf_handle handle, unsigned char* buf, unsigned int size ) {
        unsigned int _result = 0;
        
		if(handle != NULL && buf != NULL && size > 0) {
			const unsigned char *ringbuf = NULL;
			unsigned int pos = matrix_ringbuf_aquireOut(handle,&ringbuf);
			size = MHAL_MIN(pos,size);
			memcpy(buf,ringbuf,size);
			_result = matrix_ringbuf_confirmAquireOut(handle,size);
		}	
        return _result;
    }

    unsigned int matrix_ringbuf_aquireIn( matrix_ringbuf_handle handle, unsigned char** buf ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_aquireIn here --*/
        unsigned int _result = 0;
        try {
			clientData* cd = (clientData*)handle;
			if(cd != NULL && cd->check() && buf != NULL) {
            	data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            	data.writePointer(cd->remoteHandle); 

            	_binder->transact(TRANSACTION_matrix_ringbuf_aquireIn,data, &reply,0);

	            if(reply.readExceptionCode() == 0) {//fix check

	                _result = reply.readInt32();

					int offset = reply.readInt32();
					if(offset >= 0 && offset < cd->blob.size()){
						*buf = (unsigned char*)cd->blob.data() + offset;
					}
					else {
						ALOGW(SERVICE_NAME"_client sample_base_api error offset=%d size=%d\n",offset,cd->blob.size());
					}
	            }
			}
			else {
				ALOGW(SERVICE_NAME"_client sample_base_api error 1");
			}
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_aquireIn error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_aquireIn here --*/
    }

    unsigned int matrix_ringbuf_aquireOut( matrix_ringbuf_handle handle, const unsigned char** buf ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_aquireOut here --*/
        unsigned int _result = 0;
        try {
			clientData* cd = (clientData*)handle;
			if(cd != NULL && cd->check() && buf != NULL) {
            	data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

	            data.writePointer(cd->remoteHandle);

	            _binder->transact(TRANSACTION_matrix_ringbuf_aquireOut,data, &reply,0);

	            if(reply.readExceptionCode() == 0) {//fix check
	                _result = reply.readInt32();
	                
					int offset = reply.readInt32();
					if(offset >= 0 && offset < cd->blob.size()){
						*buf = (unsigned char*)cd->blob.data() + offset;
					}
					else {
						ALOGW(SERVICE_NAME"_client matrix_ringbuf_aquireOut error offset=%d size=%d\n",offset,cd->blob.size());
					}
	            }
			}
			else {
            	ALOGW(SERVICE_NAME"_client matrix_ringbuf_aquireOut error 1");
			}
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_aquireOut error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_aquireOut here --*/
    }

    unsigned int matrix_ringbuf_confirmAquireIn( matrix_ringbuf_handle handle, unsigned int size ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_confirmAquireIn here --*/
        unsigned int _result = 0;
        try {
			clientData* cd = (clientData*)handle;
			if(cd != NULL && cd->check()) {
            	data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

	            data.writePointer(cd->remoteHandle);
				
				data.writeInt32(size);

	            _binder->transact(TRANSACTION_matrix_ringbuf_confirmAquireIn,data, &reply,0);

	            if(reply.readExceptionCode() == 0) {//fix check
	                _result = reply.readInt32();
	            }
			}
			else {
            	ALOGW(SERVICE_NAME"_client matrix_ringbuf_confirmAquireIn error 1");
			}
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_confirmAquireIn error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_confirmAquireIn here --*/
    }

    unsigned int matrix_ringbuf_confirmAquireOut( matrix_ringbuf_handle handle, unsigned int size ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_confirmAquireOut here --*/
        unsigned int _result = 0;
        try {
			clientData* cd = (clientData*)handle;
			if(cd != NULL && cd->check()) {
            	data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

	            data.writePointer(cd->remoteHandle);
				
				data.writeInt32(size);

	            _binder->transact(TRANSACTION_matrix_ringbuf_confirmAquireOut,data, &reply,0);

	            if(reply.readExceptionCode() == 0) {//fix check
	                _result = reply.readInt32();
	            }
			}
			else {
            	ALOGW(SERVICE_NAME"_client matrix_ringbuf_confirmAquireOut error 1");
			}
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_confirmAquireOut error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_confirmAquireOut here --*/
    }

    unsigned int matrix_ringbuf_skip( matrix_ringbuf_handle handle, unsigned int size ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_skip here --*/
        unsigned int _result = 0;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);
                
                data.writeInt32(size);

                _binder->transact(TRANSACTION_matrix_ringbuf_skip,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client matrix_ringbuf_skip error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_skip error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_skip here --*/
    }

    unsigned int matrix_ringbuf_getDataSize( matrix_ringbuf_handle handle ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_getDataSize here --*/
        unsigned int _result = 0;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);

                _binder->transact(TRANSACTION_matrix_ringbuf_getDataSize,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client matrix_ringbuf_getDataSize error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_getDataSize error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_getDataSize here --*/
    }

    unsigned int matrix_ringbuf_getFreeSize( matrix_ringbuf_handle handle ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_getFreeSize here --*/
        unsigned int _result = 0;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);

                _binder->transact(TRANSACTION_matrix_ringbuf_getFreeSize,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client matrix_ringbuf_getFreeSize error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_getFreeSize error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_getFreeSize here --*/
    }

    unsigned int matrix_ringbuf_rewind( matrix_ringbuf_handle handle, unsigned int size ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_rewind here --*/
        unsigned int _result = 0;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);
                
                data.writeInt32(size);

                _binder->transact(TRANSACTION_matrix_ringbuf_rewind,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client matrix_ringbuf_skip error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_rewind error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_rewind here --*/
    }

    int matrix_ringbuf_reset( matrix_ringbuf_handle handle ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_reset here --*/
        int _result = -1;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);

                _binder->transact(TRANSACTION_matrix_ringbuf_reset,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client matrix_ringbuf_reset error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_reset error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_reset here --*/
    }

    int matrix_ringbuf_exit( matrix_ringbuf_handle handle ) {
        Parcel data, reply;

        /*-- add you code for matrix_ringbuf_exit here --*/
        int _result = -1;
        try {
            clientData* cd = (clientData*)handle;
            if(cd != NULL && cd->check()) {
                data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

                data.writePointer(cd->remoteHandle);

                _binder->transact(TRANSACTION_matrix_ringbuf_exit,data, &reply,0);

                if(reply.readExceptionCode() == 0) {//fix check
                    _result = reply.readInt32();

                    delete cd;
                }
            }
            else {
                ALOGW(SERVICE_NAME"_client TRANSACTION_matrix_ringbuf_exit error 1");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client matrix_ringbuf_exit error");
        }

        return _result;
        /*-- add you code for matrix_ringbuf_exit here --*/
    }
};

remote_buffer_module_client* remote_buffer_module_client::_instance = NULL;

matrix_ringbuf_handle matrix_ringbuf_init( unsigned int bufsize ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_init(bufsize);
}
unsigned int matrix_ringbuf_in( matrix_ringbuf_handle handle, unsigned char* buf, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_in(handle, buf, size);
}
unsigned int matrix_ringbuf_out( matrix_ringbuf_handle handle, unsigned char* buf, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_out(handle, buf, size);
}
unsigned int matrix_ringbuf_aquireIn( matrix_ringbuf_handle handle, unsigned char** buf ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_aquireIn(handle, buf);
}
unsigned int matrix_ringbuf_aquireOut( matrix_ringbuf_handle handle, const unsigned char** buf ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_aquireOut(handle, buf);
}
unsigned int matrix_ringbuf_confirmAquireIn( matrix_ringbuf_handle handle, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_confirmAquireIn(handle, size);
}
unsigned int matrix_ringbuf_confirmAquireOut( matrix_ringbuf_handle handle, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_confirmAquireOut(handle, size);
}
unsigned int matrix_ringbuf_skip( matrix_ringbuf_handle handle, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_skip(handle, size);
}
unsigned int matrix_ringbuf_getDataSize( matrix_ringbuf_handle handle ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_getDataSize(handle);
}
unsigned int matrix_ringbuf_getFreeSize( matrix_ringbuf_handle handle ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_getFreeSize(handle);
}
unsigned int matrix_ringbuf_rewind( matrix_ringbuf_handle handle, unsigned int size ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_rewind(handle, size);
}
int matrix_ringbuf_reset( matrix_ringbuf_handle handle ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_reset(handle);
}
int matrix_ringbuf_exit( matrix_ringbuf_handle handle ) {
    return remote_buffer_module_client::Instance()->matrix_ringbuf_exit(handle);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
