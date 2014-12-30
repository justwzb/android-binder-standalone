/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_upstruct_module.sidl
 */

#ifndef __remote_upstruct_module_h__
#define __remote_upstruct_module_h__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BINDER_SERVICE)

 #include "struct_module.h"

///< call this api to only add this service
int remote_upstruct_module_service_add();

#elif defined(BINDER_CLIENT)
 #error This file is only used on server
#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif


#ifdef __cplusplus
}
#endif

#endif