#include "sample_module.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SAMPLE_PTR_1(in,pin,pout,pinout,len)   {\
    typeof(in) ret = in + *pin;\
    if(pinout!=NULL) ret += *pinout;\
    int i;\
    for(i=0;i<len;i++) {\
    if(pout!=NULL) *(pout+i) = ret;\
    if(pinout!=NULL) *(pinout+i) = ret;\
    }\
    return ret;}\
    
    

int sample_int_prt_1(int in,int* pin,int* pout,int* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
int sample_int_ptr_len(int in,int* pin,int* pout,int* pinout,int len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

int32_t sample_int32_t_prt_1(int32_t in,int32_t* pin,int32_t* pout,int32_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
int32_t sample_int32_t_prt_len(int32_t in,int32_t* pin,int32_t* pout,int32_t* pinout,int32_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

unsigned int sample_unsigned_int_prt_1(unsigned int in,unsigned int* pin,unsigned int* pout,unsigned int* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
unsigned int sample_unsigned_int_prt_len(unsigned int in,unsigned int* pin,unsigned int* pout,unsigned int* pinout,unsigned int len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

uint32_t sample_uint32_t_prt_1(uint32_t in,uint32_t* pin,uint32_t* pout,uint32_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
uint32_t sample_uint32_t_prt_len(uint32_t in,uint32_t* pin,uint32_t* pout,uint32_t* pinout,uint32_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

short sample_short_prt_1(short in,short* pin,short* pout,short* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
short sample_short_ptr_len(short in,short* pin,short* pout,short* pinout,short len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}
short int sample_shortint_prt_1(short int in,short int* pin,short int* pout,short int* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
short int sample_shortint_ptr_len(short int in,short int* pin,short int* pout,short int* pinout,short int len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

int16_t sample_int16_t_prt_1(int16_t in,int16_t* pin,int16_t* pout,int16_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
int16_t sample_int16_t_prt_len(int16_t in,int16_t* pin,int16_t* pout,int16_t* pinout,int16_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

unsigned short sample_unsigned_short_prt_1(unsigned short in,unsigned short* pin,unsigned short* pout,unsigned short* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
unsigned short sample_unsigned_short_prt_len(unsigned short in,unsigned short* pin,unsigned short* pout,unsigned short* pinout,unsigned short len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}
unsigned short int sample_unsigned_shortint_prt_1(unsigned short int in,unsigned short int* pin,unsigned short int* pout,unsigned short int* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
unsigned short int sample_unsigned_shortint_prt_len(unsigned short int in,unsigned short int* pin,unsigned short int* pout,unsigned short int* pinout,unsigned short len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

uint16_t sample_uint16_t_prt_1(uint16_t in,uint16_t* pin,uint16_t* pout,uint16_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
uint16_t sample_uint16_t_prt_len(uint16_t in,uint16_t* pin,uint16_t* pout,uint16_t* pinout,uint16_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

char sample_char_prt_1(char in,char* pin,char* pout,char* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
char sample_char_ptr_len(char in,char* pin,char* pout,char* pinout,char len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

int8_t sample_int8_t_prt_1(int8_t in,int8_t* pin,int8_t* pout,int8_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
int8_t sample_int8_t_prt_len(int8_t in,int8_t* pin,int8_t* pout,int8_t* pinout,int8_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

unsigned char sample_unsigned_char_prt_1(unsigned char in,unsigned char* pin,unsigned char* pout,unsigned char* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
unsigned char sample_unsigned_char_ptr_len(unsigned char in,unsigned char* pin,unsigned char* pout,unsigned char* pinout,unsigned char len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

uint8_t sample_uint8_t_prt_1(uint8_t in,uint8_t* pin,uint8_t* pout,uint8_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
uint8_t sample_uint8_t_prt_len(uint8_t in,uint8_t* pin,uint8_t* pout,uint8_t* pinout,uint8_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

long long sample_longlong_prt_1(long long in,long long* pin,long long* pout,long long* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
long long sample_longlong_ptr_len(long long in,long long* pin,long long* pout,long long* pinout,long long len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

int64_t sample_uint64_t_prt_1(int64_t in,int64_t* pin,int64_t* pout,int64_t* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
int64_t sample_uint64_t_prt_len(int64_t in,int64_t* pin,int64_t* pout,int64_t* pinout,int64_t len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}

unsigned long long sample_unsigned_longlong_prt_1(unsigned long long in,unsigned long long* pin,unsigned long long* pout,unsigned long long* pinout) {SAMPLE_PTR_1(in,pin,pout,pinout,1)}
unsigned long long sample_unsigned_longlong_ptr_len(unsigned long long in,unsigned long long* pin,unsigned long long* pout,unsigned long long* pinout,unsigned long long len) {SAMPLE_PTR_1(in,pin,pout,pinout,len)}


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
    const char* ret = '1';//sample_ptr_api(uin.buf,uout.buf,sizeof(uout.buf));
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