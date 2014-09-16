
#include "stdio.h"
#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h> 




//result 随机出结果，0--未锁定	1--已锁定
typedef void (*tuner_callback)(int result);
//添加回调函数
void add_cb(tuner_callback cb);

//开始锁频，完成后（假设10完成）回调结果
void tune(int freq);

void tune_cb(int res);


void tune_cb(int res)
{
	printf("\n==================================================\n");
	printf("                Tuner Lock Result :%d",res);
	printf("\n==================================================\n");
}



/*封装成Client的代码*/
namespace android  
{  

	static sp<IBinder> native_binder; 
	
	//Client端服务，用于Server端远程调用本地的Callback
    //回调函数地址和参数由Server端远程传来
	class TbinderCbSrvOnClient : public BBinder  
    {  
    private: 
     pthread_key_t sigbuskey;  
	  
    public:  
  	    
        static int Instance(const sp<IBinder>& binder) {
		native_binder = binder;
		LOGE("TbinderCbSrvOnClient Instantiate\n");  
        int ret = defaultServiceManager()->addService(  
        	String16("CbClient.svc"), native_binder);  
        LOGE("TbinderCbSrvOnClient ret = %d\n", ret);  
        return ret;  
        }
		
        TbinderCbSrvOnClient(){
			 LOGV("TbinderCbSrvOnClient create\n");  
        	pthread_key_create(&sigbuskey,NULL);  
        }
		
        virtual ~TbinderCbSrvOnClient() {
			        pthread_key_delete(sigbuskey);  
        	LOGV("TbinderCbSrvOnClient destory\n");  
        }

		virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
			printf("CbClient:server - onTransact code:%d\n",code);
			   switch(code)  {
     
        case 0:   
            {  
                tuner_callback cb  = (tuner_callback)data.readInt32();
				int arg = data.readInt32();
				//TODO get callback from the srv and exec it
				if(cb){
					cb(arg);
				}
				printf("\nCbClient:server - Callback :0x%x arg:%d \n",cb,arg);
                return NO_ERROR;  
            } break;  
		
        default:  
            return BBinder::onTransact(code, data, reply, flags);  
        
		}
    }
 }; 
	
	//Client端向Server端的远程调用，用于向Server端注册回调、锁频远程调用
    class TbinderCbClient  
    {  
    public:  
         TbinderCbClient *Instance() {
			return this;
        }
		void add_cb(tuner_callback cb){
			getZPService(); 
        	Parcel data, reply; 
        	data.writeInt32((int32_t)cb);
			data.writeStrongBinder(native_binder);
			printf("client - binder->transact() Callback:0x%x\n",cb);
        	binder->transact(1, data, &reply);
		}
        void tune(int freq){
			int status;
			getZPService();  
        	Parcel data, reply;  
        	data.writeInt32(freq);
        	printf("client - binder->transact() freq:%d\n",freq);  
        	binder->transact(0, data, &reply);  
        	status = reply.readInt32();  
			
		}
        void TbinderCbclient(){
			native_binder = new TbinderCbSrvOnClient;
        }

		sp<IBinder>& getNativeBinder(){
			return native_binder;
		}
		 
		//sp<IBinder> native_binder;  


    private:  
         void getZPService(){
			 sp<IServiceManager> sm = defaultServiceManager();  
        	binder = sm->getService(String16("CbSrv.svc"));  
        	printf("client - etService: %p\n", sm.get());  
        	if(binder == 0)  
        	{  
            	printf("ZPService not published, waiting...");  
            	return;  
        	}  
        }
		sp<IBinder> binder; 
    }; 

    

 } 


using namespace android; 

/*
Server端的接口在客户端的代理，一般会封装成库。
这里为了演示方便，与使用者放到了一起。
*/
int _test_cb(void) {
    TbinderCbClient Client ;
	int f;
	
    //初始化Client本地服务，用于接收Server端Callback触发
	sp<ProcessState> proc(ProcessState::self());  
	sp<IServiceManager> sm = defaultServiceManager();  
	printf("CbClient:server - erviceManager: %p\n", sm.get());  
	
	int ret = TbinderCbSrvOnClient::Instance(Client.getNativeBinder());  
	
	printf("CbClient:server - ZPService::Instance return %d\n", ret);  
	ProcessState::self()->startThreadPool();  

	//向Server端注册Callback
	Client.Instance()->add_cb(tune_cb);
	f = 576000;
	Client.Instance()->tune(f);
	
	printf("CbClient:server -> enter loop ...\n");
	IPCThreadState::self()->joinThreadPool();
	printf("CbClient:server -> return \n");

	
	return 0;
}
	


 

/*main function of server*/
int main(int arg, char** argv)  
{
	
    TbinderCbClient tuner_ctrl;
	printf("\n======================== testcallback_client start ========================\n");
	 
    _test_cb();
	return 0;
}



