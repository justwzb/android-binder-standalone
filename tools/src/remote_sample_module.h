/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_sample_module.sidl
 */

#ifndef __remote_sample_module_h__
#define __remote_sample_module_h__

#if defined(BINDER_SERVICE)

///< call this api loop for ever and star service
int remote_sample_module_service_serv();

///< call this api to only add this service
int remote_sample_module_service_add();

//--------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


///<implent this api to call real function on service
int sample_base_api_stub( int in, int* in1, int* inout1, int* out1, int* inoutlen, int len );


#ifdef __cplusplus
}
#endif

#elif defined(BINDER_CLIENT)
 #error This file is only used on server
#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif

#endif