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

//#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SAMPLE_HANDLE_T SAMPLE_HANDLE_T;

typedef int int32_t;

typedef struct {
    int i;
    char buf[16];
}SAMPLE_ST;

int32_t sample_base_api1(int32_t,int32_t*);

/**
@brief api to demo int as input/output paramter and return value

@param[in] in any input int
@param[out] out output int, will be in+1, NULL is allowed.
@return return in+2
*/
int sample_base_api(int in,int * out);

/**
@brief api to demo char* as input/output paramter and return value

@param[in] in any input char*
@param[out] out output char*, will be in+"o", NULL is allowed.
@param[in] outlen length of out buffer
@return return "o"+in+o", api will malloc the memory and no need to be free by caller
*/
const char* sample_ptr_api(char* in,char* out,int outlen);

/**
@brief api to demo struct pointer as input/output paramter and return value

@param[in] in any input struct*
@param[out] out output struct* with same value as sample_base_api and sample_ptr_api
@return return same value as sample_base_api and sample_ptr_api
*/
SAMPLE_ST* sample_st_api(SAMPLE_ST* in, SAMPLE_ST* out);

/**
@brief api to demo handle* as input/output paramter and return value

Same as sample_st_api but no defines of SAMPLE_HANDLE_T will be export
*/
SAMPLE_HANDLE_T* sample_handle_api(SAMPLE_HANDLE_T* in,SAMPLE_HANDLE_T* out);

/**
@brief api to demo no output paramter and no return value

Used to be called asynchronization

@param[in] in any input int, will sleep in ms and then print it
*/
void sample_void_api(int in);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
