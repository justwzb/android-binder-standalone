#include <stdio.h>

#if defined(BINDER_SERVICE)

#include "remote_buffer_module.h"

int main(int arg, char** argv) {
    return remote_buffer_module_service_serv();
}

#elif defined(BINDER_CLIENT)
#include "matrix_ringbuf.h"

#define BUFFER_SIZE 64*1024  //must be 2^n, TODO: all size support will add in server

int main(int arg, char** argv) {
	matrix_ringbuf_handle handle = matrix_ringbuf_init((unsigned int)BUFFER_SIZE);
	printf("Main, ringbuf init, handle = %p\n",handle);

	unsigned char* inbuf = NULL;
	unsigned int canWriteSize = matrix_ringbuf_aquireIn(handle,&inbuf);
	printf("Main, matrix_ringbuf_aquireIn, canWriteSize = %d\n",canWriteSize);
	printf("Main, matrix_ringbuf_aquireIn,begin to copy,buf=%p\n",inbuf);

	char* s = "ddddddddd";
	memcpy(inbuf,s,strlen(s));
	printf("Main, matrix_ringbuf_aquireIn,copy end  ---------\n");

	unsigned int size  = matrix_ringbuf_confirmAquireIn(handle,(unsigned int)strlen(s));

	canWriteSize = matrix_ringbuf_aquireIn(handle,&inbuf);
	printf("Main, matrix_ringbuf_aquireIn, canWriteSize = %d\n",canWriteSize);
	printf("Main, matrix_ringbuf_aquireIn,begin to copy,buf=%p\n",inbuf);
	char* ts = "aaaaaaaaaaaaaadddddddddddddddddddddfffffffffffff";
	memcpy(inbuf,ts,strlen(ts));
	printf("Main, matrix_ringbuf_aquireIn,copy end  ---------\n");
	printf("Main, matrix_ringbuf_aquireIn,copy end,inbuf=%s\n",inbuf);

	size  = matrix_ringbuf_confirmAquireIn(handle,(unsigned int)strlen(ts));

	printf("Main, matrix_ringbuf_confirmAquireIn,size=%d\n",size);


	const unsigned char* outbuf;
	size = matrix_ringbuf_aquireOut(handle,&outbuf);

	printf("Main, matrix_ringbuf_aquireOut,size=%d\n",size);
	printf("Main, matrix_ringbuf_aquireOut,outbuf=%s\n",outbuf);

	int ret = matrix_ringbuf_exit(handle);
	printf("Main, matrix_ringbuf_exit,ret=%d\n",ret);
	return 0;
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
