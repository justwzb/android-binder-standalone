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





typedef unsigned int matrix_ringbuf_handle;

unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle, const unsigned char *buf, unsigned int size);
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf);
unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size);


/*封装成Service的代码*/
namespace android  
{  
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
        	String16("zp.svc"), new ZPService());  
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
                matrix_ringbuf_handle handle = (matrix_ringbuf_handle)data.readInt32();
				unsigned int size = (unsigned int )data.readInt32();
				int out = 0;
				//TODO 
				unsigned char *outData = malloc(size);
				if(outData){
			    	data.read(outData,size);
					out = matrix_ringbuf_in(handle,outData,size);
				}else{
					out = 0;
					printf("\nserver - malloc failed !\n");
				}
                reply->writeInt32(out);  
				printf("\nserver - arg:%x %x %d return:%d\n",in0,in1,in2,out);
                free(outData);
				return NO_ERROR;  
            } break;  
		case 1:   
            {  
                matrix_ringbuf_handle handle = (matrix_ringbuf_handle)data.readInt32(); 
				int out; 
				unsigned char *buf_ptr = NULL;
				
				out = matrix_ringbuf_aquireOut(handle,(const unsigned char * *) &buf_ptr);
				reply->writeInt32((int32_t)buf_ptr);
                reply->writeInt32(out);  
				printf("\nserver - arg:%x %x return:%d\n",in0,in1,out);
                return NO_ERROR;  
            } break;  
		case 2:   
            {  
                int in0 = data.readInt32(); 
				int in1 = data.readInt32(); 
				int out;
				//TODO hardware lock
				out = matrix_ringbuf_confirmAquireOut((matrix_ringbuf_handle) in0,in1);
                reply->writeInt32(out);  
				printf("\nserver - arg:%x %x return:%d\n",in0,in1,out);
                return NO_ERROR;  
            } break;  
		
        default:  
            return BBinder::onTransact(code, data, reply, flags);  
        
		}
    }
 }; 
}



 using namespace android; 

void dump_buf(unsigned char *buf,int len)
{
	int i ;
	printf("\nServer :");
	for(i = 0; i < len;i++){
		if(i%16 == 0)
			printf("\n");

		printf("%d   ",*(buf + i));
	}
	printf("\n");
}

/**
 @brief 写入数据

 @param[in] handle 缓冲区句柄。
 @param[in] buf 待写入的数据的缓冲区指针。
 @param[in] size 待写入数据的长度。
 @return 返回成功写入的数据字节数，如果未写入任何数据，则该值为0。
 @note 
 */
unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle,const unsigned char *buf, unsigned int size)
{
	
    printf("\nServer - matrix_ringbuf_in handle:0x%x size:%d\n",handle,size);
	dump_buf(buf,size);
	
	
	return size;
}

static unsigned char s_buff[128];
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf)
{
	printf("\nServer - matrix_ringbuf_aquireOut\n");
	if(buf != NULL) {
		*buf = s_buff;
	}

	return sizeof(s_buff);
}

/**
 @brief  确认处理完size个字节的数据，直接向前移动读指针size 个字节。

必须与matrix_ringbuf_aquireOut() 配合使用，使用matrix_ringbuf_aquireOut 获取了数据指针，并对其数据
进行处理以后，若不调用该函数，则读指针不会发生移动，如同没有对数据进行处理。

 @param[in] handle 缓冲区句柄。
 @param[in] size 完成处理的数据的长度。
 @return 返回确认处理过的数据长度。即读指针向前移动的字节数目。
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size)
{
	printf("\nServer - matrix_ringbuf_confirmAquireOut\n");
	dump_buf((unsigned char *)s_buff,size);
	return size;
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

