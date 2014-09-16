
#include "stdio.h"
#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h> 


typedef unsigned int matrix_ringbuf_handle;


/*封装成Client的代码*/
namespace android  
{  
    class RingBufClient  
    {  
    public:  

         RingBufClient *Instance() {
			return this;
        }
	
        unsigned int rpc_matrix_ringbuf_in(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size){
			Parcel  data ,reply;
			getZPService(); 
        	printf("client - binder->transact() \n");  
			data.writeInt32(handle);
			data.writeInt32(size);
			data.write(buf,size);
        	binder->transact(0, data, &reply);  
			return reply.readInt32();
		}

	  
	  unsigned int rpc_matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf)
	  {
	  	Parcel data, reply;
	  	getZPService();  
		data.writeInt32(handle);
		binder->transact(1, data, &reply); 
		*buf = (const unsigned char *)reply.readInt32();
		return reply.readInt32();
	  }

	  unsigned int rpc_matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size)
	  {
		Parcel data, reply;
		getZPService();  
		data.writeInt32(handle);
		data.writeInt32(size);
		binder->transact(2, data, &reply);  
		return reply.readInt32();
	  }
	  
    private:
         void getZPService(){
			 sp<IServiceManager> sm = defaultServiceManager();  
        	binder = sm->getService(String16("zp.svc"));  
        	printf("client - etService: %p\n", sm.get());  
        	if(binder == 0)  
        	{  
            	printf("ZPService not published, waiting...");  
            	return;  
        	}  
        }
		sp<IBinder> binder; 
		Parcel mem_t;
		Parcel::WritableBlob Blob;
    };  

 } 


unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle,const unsigned char *buf, unsigned int size)
{
	RingBufClient::Instance().rpc_matrix_ringbuf_in(handle,data,DATA_SIZE);
}

static unsigned char s_buff[128];
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf)
{
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
}



using namespace android; 

#define DATA_SIZE  1024

void write_buf(unsigned char *xxx)
{
	int i;
	for(i = 0 ;i < DATA_SIZE;i++)
		*(xxx + i) = i;
}

void dump_buf(unsigned char *xxx)
{
	int i ;
	printf("\nCliend :");
	for(i = 0 ;i < 500;i++){
		if(i%16 == 0)
			printf("\n");

		printf("%d   ",*(xxx + i));
	}
		printf("\n");
}


/*main function of server*/
int main(int arg, char** argv)  
{
	
    RingBufClient client();
	int len;
	printf("\n======================== testringbuf_client start ========================\n");
	matrix_ringbuf_handle handle = 0x12345678;

	//test 3.1
	unsigned char data[DATA_SIZE];
	memset(data,12,sizeof(data));
	client.rpc_matrix_ringbuf_in(handle,data,DATA_SIZE);

	//test 3.2
	const unsigned char *buf = NULL:
	int len = client.rpc_matrix_ringbuf_aquireOut( handle,&buf);
	memset(buf,34,len);
	client.rpc_matrix_ringbuf_confirmAquireOut(handle,DATA_SIZE,len);
	printf("\nCliend - len :%d\n",len);
	return 0;
}

