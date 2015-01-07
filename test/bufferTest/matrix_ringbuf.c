#define LOG_TAG "matrix_ringbuf"
#include <string.h>

#include "mhal_defines.h"
#include "matrix_ringbuf.h"
#include <utils/Log.h>

typedef struct {
	unsigned int in;
	unsigned int out;
	unsigned int bufsize;
	unsigned char *buf;
	unsigned int allocFlag;
} _matrix_ringbuf;

 matrix_ringbuf_handle matrix_ringbuf_init(unsigned int bufsize) {
 	return matrix_ringbuf_initwithbuffer(NULL,bufsize);
}

matrix_ringbuf_handle matrix_ringbuf_initwithbuffer(void* ptr,unsigned int bufsize){
	ALOGI("ENTER %s\n", __FUNCTION__);
	if (bufsize & (bufsize - 1)) {
		ALOGE("%d bufsize should be 2^n", bufsize);
		return NULL;
	}

	_matrix_ringbuf *ringBuf = (_matrix_ringbuf*)malloc(sizeof(_matrix_ringbuf));
	memset(ringBuf, 0, sizeof(_matrix_ringbuf));
	if (ptr != NULL){
		ringBuf->buf =(char*)ptr;
		ringBuf->allocFlag = 0;
	}else{
		ringBuf->buf = (unsigned char*)malloc(bufsize);
		ringBuf->allocFlag = 1;
	}
	
	MHAL_ASSERT(ringBuf->buf != NULL, "matrix_ringbuf_init : malloc Failed!!!");
	memset(ringBuf->buf, 0, bufsize);	
	
	ringBuf->bufsize = bufsize;
	ALOGD("####EXIT %s bufsize =%d", __FUNCTION__, ringBuf->bufsize);
	return (void*)ringBuf;
}


unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size) {
	unsigned int len=0;

	//LOGV("ENTER %s", __FUNCTION__);	
	if(handle == NULL || buf == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}

	//LOGV("@1 %s size=%u", __FUNCTION__, size);
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;

	// size = min(size, freeSize) 
	size = MHAL_MIN(size, (ringBuf->bufsize - (ringBuf->in - ringBuf->out)));
	//LOGV("@2 %s, size=%u, bufsize=%u, in=%u, out=%u", __FUNCTION__, size, ringBuf->bufsize, ringBuf->in, ringBuf->out);

	/* first put the data starting from fifo->in to buffer end */   
    len = MHAL_MIN(size, ringBuf->bufsize - (ringBuf->in & (ringBuf->bufsize- 1)));   
	int offset = (ringBuf->in & (ringBuf->bufsize - 1));
	//LOGV("@2-2 offset = %u", offset); 
    memcpy(ringBuf->buf+offset , buf, len);   
	//LOGV("@3 %s, len=%u, size=%u, bufsize=%u, in=%u, out=%u", __FUNCTION__, len, size, ringBuf->bufsize, ringBuf->in, ringBuf->out);
  
    /* then put the rest (if any) at the beginning of the buffer */   
    memcpy(ringBuf->buf, buf + len, size - len);   
      
    ringBuf->in += size; 
	//LOGV("@4 %s in=%u", __FUNCTION__, size);

	//LOGV("EXIT %s write in size=%u", __FUNCTION__, size);
	return size;
}

unsigned int matrix_ringbuf_out(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size) {
	
	unsigned int len=0;

	//LOGV("ENTER %s", __FUNCTION__);	
	if(handle == NULL || buf == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
		
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;

	// size = min(size, dataSize) 
	size = MHAL_MIN(size, (ringBuf->in-ringBuf->out));

	/* first put the data starting from fifo->in to buffer end */   
    len = MHAL_MIN(size, ringBuf->bufsize - (ringBuf->out & (ringBuf->bufsize- 1)));   
    memcpy(buf, ringBuf->buf+ (ringBuf->out & (ringBuf->bufsize - 1)),  len);   
  
    /* then put the rest (if any) at the beginning of the buffer */   
    memcpy(buf + len, ringBuf->buf,  size - len);   
  
    ringBuf->out += size;  
	//LOGV("EXIT %s read out size=%d", __FUNCTION__, size);
	return size;
}

unsigned int matrix_ringbuf_skip(matrix_ringbuf_handle handle, unsigned int size){
	ALOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;
	
	if ((ringBuf->in - ringBuf->out) == 0) {
		ALOGW("%s, Here is no data in ring buffer", __FUNCTION__);
		return 0;
	}

	// size = min(size, dataSize) 
	size = MHAL_MIN(size, (ringBuf->in - ringBuf->out));

	//skip 
	ringBuf->out += size;

	MHAL_ASSERT(ringBuf->out <= ringBuf->in, "matrix_ringbuf_skip ERROR skip!");

	return size;
}

unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle, const unsigned char**buf) {

	unsigned int len = 0;
	
	//LOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL || buf == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;
	
	if ((ringBuf->in - ringBuf->out) == 0) {
		ALOGW("%s, Here is no data in ring buffer", __FUNCTION__);
		*buf = NULL;
		return 0;
	}

	// size =  dataSize 
	len = ringBuf->in - ringBuf->out;

	//len = min(size, dataSize(out -> end))
    len = MHAL_MIN(len, ringBuf->bufsize - (ringBuf->out & (ringBuf->bufsize- 1))); 
	*buf = ringBuf->buf+ (ringBuf->out & (ringBuf->bufsize - 1));
		
	return len;
}

unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size) {

	unsigned int len = 0;
	
	//LOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;	
	
	//min(size, dataSize)
	size = MHAL_MIN(size, (ringBuf->in - ringBuf->out));
	//min(size, out->end)
    len = MHAL_MIN(size, ringBuf->bufsize - (ringBuf->out & (ringBuf->bufsize- 1))); 

	if(ringBuf->out+len > ringBuf->in)
		ringBuf->out = ringBuf->in;
	else
		ringBuf->out += len;

	//LOGV("EXIT %s finished zero-copy read len = %u", __FUNCTION__, len);

	return len;
}





unsigned int matrix_ringbuf_aquireIn(matrix_ringbuf_handle handle, unsigned char**buf) {

	unsigned int len = 0;
	
	ALOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL || buf == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;
	
	if (ringBuf->bufsize - (ringBuf->in - ringBuf->out) == 0) {
		ALOGW("%s, Here is no free space in ring buffer", __FUNCTION__);
		*buf = NULL;
		return 0;
	}

	// len =  freeSpaceSize
	len = ringBuf->bufsize - (ringBuf->in - ringBuf->out);

	//len= min(size, dataSize(in -> end))
    len = MHAL_MIN(len, ringBuf->bufsize - (ringBuf->in & (ringBuf->bufsize- 1))); 
	
	*buf = ringBuf->buf+ (ringBuf->in & (ringBuf->bufsize - 1));
		
	return len;
}



unsigned int matrix_ringbuf_confirmAquireIn(matrix_ringbuf_handle handle, unsigned int size) {

	unsigned int len = 0;
	
	ALOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
		
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;	
	
	//min(size, freeSpaceSize)
	size = MHAL_MIN(size, (ringBuf->bufsize - (ringBuf->in - ringBuf->out)));

	//min(size, in->end)
    len = MHAL_MIN(size, ringBuf->bufsize - (ringBuf->in & (ringBuf->bufsize- 1)));
	
	ringBuf->in += len;

	ALOGI("EXIT %s finished zero-copy write len = %u", __FUNCTION__, len);

	return len;
}


unsigned int matrix_ringbuf_getDataSize(matrix_ringbuf_handle handle){

	unsigned int len = -1;
		
	//LOGV("ENTER %s handle(%p)", __FUNCTION__, (void*)handle);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;	

	len = ringBuf->in - ringBuf->out;	
	
	//LOGV("EXIT %s , in = %u, out = %u, validData = %u", __FUNCTION__, ringBuf->in, ringBuf->out, len);

	return len;
}


unsigned int matrix_ringbuf_getFreeSize(matrix_ringbuf_handle handle){

	unsigned int len = -1;
		
	//LOGV("ENTER %s handle(%p)", __FUNCTION__, (void*)handle);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;	

	len = ringBuf->bufsize - (ringBuf->in - ringBuf->out);	
	
	//LOGV("EXIT %s , in = %u, out = %u, freeSpaceSize = %u", __FUNCTION__, ringBuf->in, ringBuf->out, len);

	return len;

}




unsigned int matrix_ringbuf_rewind(matrix_ringbuf_handle handle, unsigned int size){

	unsigned int len = 0;
	
	ALOGV("ENTER %s", __FUNCTION__);

	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return 0;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle;	


	if(ringBuf->in <= ringBuf->bufsize  && ringBuf->out <= ringBuf->bufsize)
		len = ringBuf->out;
	else
		len = ringBuf->bufsize - (ringBuf->in - ringBuf->out);	 
	
	if(size != 0xFFFFFFFF)
		len = MHAL_MIN(size, len);

	ringBuf->out -= len;

	ALOGV("EXIT %s rewind len = %u", __FUNCTION__, len);

	return len;

}


int matrix_ringbuf_reset(matrix_ringbuf_handle handle) {
	
	ALOGV("ENTER %s", __FUNCTION__);
	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return MHAL_EINVAL;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle; 
	ringBuf->out = 0;
	ringBuf->in = 0;

	ALOGV("EXIT %s", __FUNCTION__);
	return MHAL_SUCCESS;
}

int matrix_ringbuf_exit(matrix_ringbuf_handle handle) {
	
	ALOGV("ENTER %s", __FUNCTION__);
	
	if(handle == NULL){
		ALOGE("%s, Invalid Input Params!", __FUNCTION__);
		return MHAL_EINVAL;
	}
			
	_matrix_ringbuf *ringBuf = (_matrix_ringbuf *)handle; 

	if (ringBuf->allocFlag ==  1 && ringBuf->buf != NULL){
		free(ringBuf->buf);
	}
	
	memset(ringBuf, 0, sizeof(_matrix_ringbuf));

	ALOGV("EXIT %s", __FUNCTION__);
	return MHAL_SUCCESS;
}



