/**@defgroup MHAL_defines [MHAL defines] Defines basic environment and error codes.

@version 0.1 2012/02/27 Created
@{
*/

#ifndef _MHAL_DEFINES_H_
#define _MHAL_DEFINES_H_

#include <android/log.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define MHAL_SUCCESS (0) ///< success
#define MHAL_FAILED (-999) ///< general error

#define MHAL_ENOMEM 	(-12) ///< Out of memory
#define MHAL_ETIMEDOUT 	(-110) ///< timeout
#define MHAL_EINVAL 	(-22) ///< Invalid argument
#define MHAL_EAGAIN 	(-11) ///< Try again
#define MHAL_NOTNEED	(-998) ///< No need to so

#define MHAL_MIN(a,b) (((a)<(b))?(a):(b)) ///< Get the min
#define MHAL_MAX(a,b) (((a)>(b))?(a):(b)) ///< Get the max

#define ONTRANSACT_ringbuf_init 0
#define ONTRANSACT_ringbuf_in 1
#define ONTRANSACT_ringbuf_quireOut 2
#define ONTRANSACT_ringbuf_confirmAquireOut 3



#define MHAL_ASSERT(expr, fmt,...)  \
    if (!(expr)) { \
        ALOGE("FATAL: Assertion FAILED in '%s', line %d, func %s ('%s'): "#fmt"\n", \
			   __FILE__, __LINE__,__FUNCTION__, #expr, ##__VA_ARGS__);	\
	}do{}while(0)

#ifdef __cplusplus
}
#endif
/** @} */
#endif


