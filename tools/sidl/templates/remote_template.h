/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: %=sidl_filename%
 */

#ifndef __%=sidl_basename%_h__
#define __%=sidl_basename%_h__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BINDER_SERVICE)

 /*py
for ctx in sidl_context:
    if isinstance(ctx,Include):
        output(ctx.output()+"\n")
py*/

///< call this api to only add this service
int %=sidl_basename%_service_add();

#elif defined(BINDER_CLIENT)
 #error This file is only used on server
#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif


#ifdef __cplusplus
}
#endif

#endif