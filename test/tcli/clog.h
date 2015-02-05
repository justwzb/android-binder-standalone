#ifndef __CLOG_H__
#define __CLOG_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLOGV(...)   //printf(__VA_ARGS__)
#define CLOGD(...)   //printf(__VA_ARGS__)
#define CLOGI(...)   //printf(__VA_ARGS__)
#define CLOGW(...)   printf(__VA_ARGS__)
#define CLOGE(...)   printf(__VA_ARGS__)
#define CLOGF(...)   printf(__VA_ARGS__)
#define CLOGCLI(...) //printf(__VA_ARGS__)

/**
@brief 带错误代码的WARN信息打印函数,建议所有函数返回错误前都调用本系列接口输出错误代码,以方便终端管理对这些错误进行监控和预警.
*/
#define CLOGW_WITHCODE(errCode,fmt,...)  (printf("[E%d]"#fmt"\n",(errCode),##__VA_ARGS__))  

/**
@brief 带错误代码的ERROR信息打印函数,建议所有函数返回错误前都调用本系列接口输出错误代码,以方便终端管理对这些错误进行监控和预警.
*/
#define CLOGE_WITHCODE(errCode,fmt,...)  (printf("[E%d]"#fmt"\n",(errCode),##__VA_ARGS__))  

/**
@brief 带错误代码的FATAL信息打印函数,建议所有函数返回错误前都调用本系列接口输出错误代码,以方便终端管理对这些错误进行监控和预警.
*/
#define CLOGF_WITHCODE(errCode,fmt,...)  (printf("[E%d]"#fmt"\n",(errCode),##__VA_ARGS__))  

#define CLOG_ASSERT(expr, fmt,...)  \
    if (!(expr)) { \
        printf("[E%d]FATAL: Assertion FAILED in '%s', line %d, func %s ('%s'): "#fmt"\n", \
               -2, __FILE__, __LINE__,__FUNCTION__,#expr,##__VA_ARGS__);  \
    }do{}while(0)



#define SITA_ERROR_COMMON   0       ///< 通用模块错误段
#define SITA_ERROR_CEC      100       ///< CEC模块通用段

#define SITA_SUCCESS        (0)     ///< 成功
#define SITA_FAILED         (-(SITA_ERROR_COMMON)-1)    ///< 通用错误或者其它错误
#define SITA_ASSERT         (-(SITA_ERROR_COMMON)-2)    ///< 代码错误,产生了断言
#define SITA_ENOMEM         (-(SITA_ERROR_COMMON)-3)    ///< 内存不足错误
#define SITA_ETIMEDOUT      (-(SITA_ERROR_COMMON)-4)    ///< 超时错误
#define SITA_EINVAL         (-(SITA_ERROR_COMMON)-5)    ///< 参数错误
#define SITA_EAGAIN         (-(SITA_ERROR_COMMON)-6)    ///< 请稍后重试错误
#define SITA_ESTATUS        (-(SITA_ERROR_COMMON)-7)    ///< 状态错误


#define SITA_CEC_EFRAME     (-(SITA_ERROR_CEC)-1)       ///< CEC模块帧错误



#define SITA_MIN(a,b) (((a)<(b))?(a):(b)) ///< Get the min
#define SITA_MAX(a,b) (((a)>(b))?(a):(b)) ///< Get the max


#ifdef __cplusplus
}
#endif
/** @} */
#endif