#include "sample_module.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int sample_base_api(int in,int* out) {
    if(out != NULL) {
        *out = in+1;
    }

    int ret = in+2;

    printf("%s in=%d out=%d return=%d\n",__FUNCTION__,in,*out,ret);

    return ret;
}

const char* sample_ptr_api(char* in,char* out,int outlen) {
    if(out != NULL) {
        if(in != NULL) {
            snprintf(out,outlen,"%so",in);
        }
        else {
            strncpy(out,"o",outlen);
        }
    }

    static char s_ret[1024];//It`s bad api, fft we have to consider it
    if(in != NULL) {
        snprintf(s_ret,sizeof(s_ret),"o%so",in);
    }
    else {
        strncpy(s_ret,"oo",sizeof(s_ret));
    }

    printf("%s in=%s out=%s return=%s\n",__FUNCTION__,in,out,s_ret);

    return s_ret;
}

/**
@brief api to demo struct pointer as input/output paramter and return value

@param[in] in any input struct*
@param[out] out output struct* with same value as sample_base_api and sample_ptr_api
@return return same value as sample_base_api and sample_ptr_api
*/
SAMPLE_ST* sample_st_api(SAMPLE_ST* in, SAMPLE_ST* out) {
    SAMPLE_ST uin;
    if(in != NULL) {
        uin.i = in->i;
        memcpy(uin.buf,in->buf,sizeof(uin.buf));
    }
    else {
        uin.i = 0;
        memset(uin.buf,0,sizeof(uin.buf));
    }

    SAMPLE_ST uout;
    static SAMPLE_ST s_ret;//It`s bad api, but we have to consider it
    s_ret.i = sample_base_api(uin.i,&uout.i);
    const char* ret = sample_ptr_api(uin.buf,uout.buf,sizeof(uout.buf));
    if(ret != NULL) {
        strncpy(s_ret.buf,ret,sizeof(s_ret.buf));
    }
    else {
        memset(s_ret.buf,0,sizeof(s_ret.buf));
    }

    if(out != NULL) {
        memcpy(out,&uout,sizeof(out));
    }

    printf("%s in=%p-%d-%s out=%p-%d-%s return=%d-%s\n",__FUNCTION__
        ,in,uin.i,uin.buf
        ,out,uout.i,uout.buf
        ,s_ret.i,s_ret.buf);

    return &s_ret;
}


struct _SAMPLE_HANDLE_T {
    int i;
    char buf[16];
};

SAMPLE_HANDLE_T* sample_handle_api(SAMPLE_HANDLE_T* in,SAMPLE_HANDLE_T* out) {
    return (SAMPLE_HANDLE_T*)sample_st_api((SAMPLE_ST*)in,(SAMPLE_ST*)out);
}

void sample_void_api(int in) {

    usleep(in * 1000);

    printf("%s in=%d\n",__FUNCTION__,in);
}