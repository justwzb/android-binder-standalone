/**@defgroup define sample api those need be RPC used to demo
@{

Sample api means all parameters and return value should be base types.
Including:
 - base type (e.g. int) as input paramter
 - base type (e.g. int) as int as output paramter
 - base type (e.g. int) as int as return value
 - struct pointer as input paramter
 - struct pointer as output paramter
 - struct pointer as return value
 - handle pointer as input paramter
 - handle pointer as output paramter
 - handle pointer as return value
 - no output paramter and no return value ( onway RPC )

Not includeing:
 - callback function pointer as input paramter
 - big buffer as input paramter
 - big buffer as output paramter
 - big buffer as return value

@version 1.0.0 2014/09/15 first draft
*/

#ifndef __SAMPLE_MODULE_H__
#define __SAMPLE_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct _SAMPLE_HANDLE_T SAMPLE_HANDLE_T;

typedef int int32_t;

typedef struct {
    int i;
    char buf[16];
}SAMPLE_ST;

int sample_int_prt_1(int in,int* pin,int* pout,int* pinout);
int sample_int_ptr_len(int in,int* pin,int* pout,int* pinout,int len);

int32_t sample_int32_t_prt_1(int32_t in,int32_t* pin,int32_t* pout,int32_t* pinout);
int32_t sample_int32_t_prt_len(int32_t in,int32_t* pin,int32_t* pout,int32_t* pinout,int32_t len);

unsigned int sample_unsigned_int_prt_1(unsigned int in,unsigned int* pin,unsigned int* pout,unsigned int* pinout);
unsigned int sample_unsigned_int_prt_len(unsigned int in,unsigned int* pin,unsigned int* pout,unsigned int* pinout,unsigned int len);

uint32_t sample_uint32_t_prt_1(uint32_t in,uint32_t* pin,uint32_t* pout,uint32_t* pinout);
uint32_t sample_uint32_t_prt_len(uint32_t in,uint32_t* pin,uint32_t* pout,uint32_t* pinout,uint32_t len);

short sample_short_prt_1(short in,short* pin,short* pout,short* pinout);
short sample_short_ptr_len(short in,short* pin,short* pout,short* pinout,short len);
short int sample_shortint_prt_1(short int in,short int* pin,short int* pout,short int* pinout);
short int sample_shortint_ptr_len(short int in,short int* pin,short int* pout,short int* pinout,short int len);

int16_t sample_int16_t_prt_1(int16_t in,int16_t* pin,int16_t* pout,int16_t* pinout);
int16_t sample_int16_t_prt_len(int16_t in,int16_t* pin,int16_t* pout,int16_t* pinout,int16_t len);

unsigned short sample_unsigned_short_prt_1(unsigned short in,unsigned short* pin,unsigned short* pout,unsigned short* pinout);
unsigned short sample_unsigned_short_prt_len(unsigned short in,unsigned short* pin,unsigned short* pout,unsigned short* pinout,unsigned short len);
unsigned short int sample_unsigned_shortint_prt_1(unsigned short int in,unsigned short int* pin,unsigned short int* pout,unsigned short int* pinout);
unsigned short int sample_unsigned_shortint_prt_len(unsigned short int in,unsigned short int* pin,unsigned short int* pout,unsigned short int* pinout,unsigned short len);

uint16_t sample_uint16_t_prt_1(uint16_t in,uint16_t* pin,uint16_t* pout,uint16_t* pinout);
uint16_t sample_uint16_t_prt_len(uint16_t in,uint16_t* pin,uint16_t* pout,uint16_t* pinout,uint16_t len);

char sample_char_prt_1(char in,char* pin,char* pout,char* pinout);
char sample_char_ptr_len(char in,char* pin,char* pout,char* pinout,char len);

int8_t sample_int8_t_prt_1(int8_t in,int8_t* pin,int8_t* pout,int8_t* pinout);
int8_t sample_int8_t_prt_len(int8_t in,int8_t* pin,int8_t* pout,int8_t* pinout,int8_t len);

unsigned char sample_unsigned_char_prt_1(unsigned char in,unsigned char* pin,unsigned char* pout,unsigned char* pinout);
unsigned char sample_unsigned_char_ptr_len(unsigned char in,unsigned char* pin,unsigned char* pout,unsigned char* pinout,unsigned char len);

uint8_t sample_uint8_t_prt_1(uint8_t in,uint8_t* pin,uint8_t* pout,uint8_t* pinout);
uint8_t sample_uint8_t_prt_len(uint8_t in,uint8_t* pin,uint8_t* pout,uint8_t* pinout,uint8_t len);

long long sample_longlong_prt_1(long long in,long long* pin,long long* pout,long long* pinout);
long long sample_longlong_ptr_len(long long in,long long* pin,long long* pout,long long* pinout,long long len);

int64_t sample_uint64_t_prt_1(int64_t in,int64_t* pin,int64_t* pout,int64_t* pinout);
int64_t sample_uint64_t_prt_len(int64_t in,int64_t* pin,int64_t* pout,int64_t* pinout,int64_t len);

unsigned long long sample_unsigned_longlong_prt_1(unsigned long long in,unsigned long long* pin,unsigned long long* pout,unsigned long long* pinout);
unsigned long long sample_unsigned_longlong_ptr_len(unsigned long long in,unsigned long long* pin,unsigned long long* pout,unsigned long long* pinout,unsigned long long len);

SAMPLE_ST* sample_st_api(SAMPLE_ST* pin, SAMPLE_ST* pout);

SAMPLE_HANDLE_T* sample_handle_api(SAMPLE_HANDLE_T* pin,SAMPLE_HANDLE_T* pout);

void sample_oneway_api(int in);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
