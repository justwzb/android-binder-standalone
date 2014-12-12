/**@defgroup define sample api those need be RPC used to demo
@{

不支持的情况
- 返回struct指针
- 返回struct
- 非平面struct(不能直接拷贝的),一个或者多个

@version 1.0.0 2014/09/15 first draft
*/

#ifndef __STRUCT_MODULE_H__
#define __STRUCT_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int i;
    char j;
    char buf[16];
}STRUCT_S;

typedef enum {
    EM_1,
    EM_2,
    EM_MAX
}ENUM_EM;

typedef struct {
    int i;
    int j;
    int len;
    char* buf;
}STRUCT_UNFLAT_S;

typedef struct _HANDLE_T HANDLE_T;

int struct_api_1(STRUCT_S* pin,STRUCT_S* pout);

int struct_api_l(STRUCT_S* pin,STRUCT_S* pout,int len);

ENUM_EM enum_api_1(ENUM_EM in,ENUM_EM* pin,ENUM_EM* pout);

ENUM_EM enum_api_l(ENUM_EM in,ENUM_EM* pin,ENUM_EM* pout,int len);

int unflag_struct_api(STRUCT_UNFLAT_S* pin,STRUCT_UNFLAT_S* pout);


#ifdef __cplusplus
}
#endif
/** @} */
#endif
