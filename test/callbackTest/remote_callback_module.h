/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_callback_module.sidl
 */

#ifndef __remote_callback_module_h__
#define __remote_callback_module_h__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BINDER_SERVICE)

 #include "callback_module.h"


///< call this api loop for ever and star service
int remote_callback_module_service_serv();

///< call this api to only add this service
int remote_callback_module_service_add();

#elif defined(BINDER_CLIENT)
 #error This file is only used on server
#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif


#ifdef __cplusplus
}
#endif

#endif