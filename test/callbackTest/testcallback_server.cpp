/*
头文件
*/

#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <grp.h>  
#include <binder/IPCThreadState.h>  
#include <binder/ProcessState.h>  
#include <binder/IServiceManager.h>  
#include <utils/Log.h> 
#include <pthread.h>



//result 随机出结果，0--未锁定	1--已锁定
typedef void (*tuner_callback)(int result);


tuner_callback sCB = NULL;
pthread_t m_threadIdTimer = NULL;

void add_cb(tuner_callback cb);
void tune(int freq);




/*封装成Service的代码*/
namespace android  
{   
	sp<IBinder> client_binder = NULL;
	
	class TbinderCbService  
    {  
    public:  
         TbinderCbService *Instance() {
			return this;
        }
	
        void rpc_cb_to_client(int cb,int arg){
			getZPService();  
        	Parcel data, reply;  
        	data.writeInt32(cb);
			data.writeInt32(arg);
			if(binder->isBinderAlive()){
        		printf("server - binder->transact() Callback:0x%x Arg:%d\n",cb,arg);  
        		binder->transact(0, data, &reply);
			}else{
				printf("server - binder Dead ! \n"); 
			}
		}

    private:
		
         void getZPService(){
			binder = client_binder;
			if(binder == 0)  
        	{  
            	printf("client_binder not published, waiting...");  
            	return;  
        	} 
        }
		sp<IBinder> binder;  
    }; 

	
    class ZPService : public BBinder  
    {  
    private:  
		    //static struct sigaction oldact;  
     pthread_key_t sigbuskey;  
        //mutable Mutex m_Lock;  
        //int32_t m_NextConnId;  
  
    public:  
        static int Instance() {
		LOGE("ZPService Instantiate\n");  
        int ret = defaultServiceManager()->addService(  
        	String16("CbSrv.svc"), new ZPService());  
        LOGE("ZPService ret = %d\n", ret);  
        return ret;  
        }
		
        ZPService(){
			        LOGV("ZPService create\n");  
        	//m_NextConnId = 1;  
        	pthread_key_create(&sigbuskey,NULL);  
        }
		
        virtual ~ZPService() {
			        pthread_key_delete(sigbuskey);  
        	LOGV("ZPService destory\n");  
        }

		virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
			printf("server - onTransact code:%d\n",code);
			   switch(code)  {
     
        case 0:   
            {  
                int in = data.readInt32(); 
				//TODO hardware lock
				tune(in);
				printf("\nserver - getint :%x \n",in);
                return NO_ERROR;  
            } break;  
		
		 case 1:   
            {  
                int in = data.readInt32(); 
				int out = 1;
				//TODO register callback
				client_binder = data.readStrongBinder();
				add_cb((tuner_callback) in);
                reply->writeInt32(out);  
				printf("\nserver - Register callback :0x%x \n",in);
                return NO_ERROR;  
            } break;  
        default:  
            return BBinder::onTransact(code, data, reply, flags);  
        
		}
    }
 }; 
}



 using namespace android; 
 
 void * tuner_task(void *)
 {
 	 TbinderCbService rpc;
	 	
	 printf("\nServer - Enter tuner_task\n");
	 while(1){
		 //get tuner status
		 printf("\nServer - get tuner status\n");
		 usleep(1000 * 1000 * 5);
		 printf("\nServer - locked !\n");
		 rpc.rpc_cb_to_client((int)sCB,1);
		 break;
	 }
	  printf("\nServer - Exit tuner_task\n");
	  pthread_exit(NULL);    
	  return NULL;
 }
 
 //添加回调函数
 void add_cb(tuner_callback cb){
	 sCB = cb;
 }
 
 
 //开始锁频，完成后（假设10完成）回调结果
 void tune(int freq) {
	 printf("\nServer - [Freq:%d]Tunner Locking ...\n",freq);
 
	 pthread_create(&m_threadIdTimer, NULL, tuner_task, (void*)NULL);
 }


/*main function of server*/
int main(int arg, char** argv)  
{  
	printf("\n========================= testringbuf_server start =========================\n");
    printf("server - ain() begin\n");  
    sp<ProcessState> proc(ProcessState::self());  
    sp<IServiceManager> sm = defaultServiceManager();  
    //LOGI("ServiceManager: %p\n", sm.get());  
    printf("server - erviceManager: %p\n", sm.get());  
    int ret = ZPService::Instance();  
    printf("server - ZPService::Instance return %d\n", ret);  
    ProcessState::self()->startThreadPool();  
	
	printf("server -> enter loop ...\n");
	IPCThreadState::self()->joinThreadPool();//主线程加入线程池
	printf("server -> return \n");
	return 0;
}




