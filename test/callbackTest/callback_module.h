///< a very sample module with callback

#ifndef __CALLBACK_MODULE_H__
#define __CALLBACK_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef int (*cb_callback)(int param);

int cb_add(cb_callback cb);

int cb_remove(cb_callback cb);

int cb_invoke(int p);

int cb_invoke2(int p);


#ifdef __cplusplus
}
#endif

#endif
