#ifndef __MATRIX_RINGBUF_H__
#define __MATRIX_RINGBUF_H__

#include <stdio.h>
#include <stdlib.h>

/*
 * 环形缓冲区
 * 限制：只允许一个读线程，一个写线程对环形缓冲区进行并发操作。
 * 特点：免锁机制，KFIFO提取版本。提供1次拷贝和0次拷贝。
 * 使用：请参考unitTest 中的ringbuf测试用例。
 */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 @brief 环形缓冲区操作的句柄
 */
typedef void* matrix_ringbuf_handle;


/**
 @brief 初始化一个环形缓冲区

 @param[in] bufsize 	缓冲区大小，必须是2的n次幂。
 @return 				成功返回 缓冲区句柄；失败返回小于0  的值。
 @note 
 */
matrix_ringbuf_handle matrix_ringbuf_init(unsigned int bufsize);



/**
 @brief 初始化一个环形缓冲区，允许由上层分配buffer的版本。
 */
matrix_ringbuf_handle matrix_ringbuf_initwithbuffer(void* ptr,unsigned int bufsize);


/**
 @brief 写入数据

 @param[in] handle 	缓冲区句柄。
 @param[in] buf		待写入的数据的缓冲区指针。
 @param[in] size		待写入数据的长度。
 @return 				返回成功写入的数据字节数，如果未写入任何数据，则该值为0。
 */
unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size);


/**
 @brief 读取数据

 @param[in] handle 	缓冲区句柄。
 @param[out] buf		外部提供一个存储数据的缓冲区
 @param[in] size		欲读取数据的长度。
 @return 				返回成功读取的数据字节数，如果未读出任何数据，则该值为0。
 @note 发生一次拷贝，由环形缓冲区拷贝到用户提供的buf  中。
 */
unsigned int matrix_ringbuf_out(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size);


/**
 @brief 抛弃一段有效数据

 @param[in] handle 	缓冲区句柄。
 @param[in] size		欲忽略的数据的字节长度。即直接移动读指针，抛弃这段数据，不对其进行处理。
 @return 				返回成功抛弃的数据字节数。
 @note  如果环形缓冲区中的有效数据长度小于size  ，则整个缓冲区被清空。
 */
unsigned int matrix_ringbuf_skip(matrix_ringbuf_handle handle, unsigned int size);



/**
 @brief 从环形缓冲区中取得指向一段数据的指针。

获取数据的指针后，可以 通过该指针直接处理这段数据，
因此省去了将数据从缓冲区内拷贝出来的步骤。该函数返回可供
处理的数据字节长度。必须与matrix_ringbuf_confirmAquireOut() 一同使用。

 @param[in] handle 	缓冲区句柄。
 @param[out] buf		外部提供的一个二级指针，用于获得目标数据的缓冲区指针。
 @return 				返回该指针处，可供处理的数据字节数。
 @note   
 */
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf);



/**
 @brief  确认处理完size个字节的数据，直接向前移动读指针size 个字节。

必须与matrix_ringbuf_aquireOut() 配合使用，使用matrix_ringbuf_aquireOut 获取了数据指针，并对其数据
进行处理以后，若不调用该函数，则读指针不会发生移动，如同没有对数据进行处理。

 @param[in] handle 	缓冲区句柄。
 @param[in] size		完成处理的数据的长度。
 @return 				返回确认处理过的数据长度。即读指针向前移动的字节数目。
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size);






/**
 @brief 从环形缓冲区内获取一段空闲空间

直接获取了指向环形缓冲区内部的指针，因此可以直接将数据写入环形缓冲区内。
避免了数据写入时从用户buffer 中复制到环形缓冲区的一次拷贝，
必须与matrix_ringbuf_confirmAquireIn() 一同使用。

 @param[in] handle 	缓冲区句柄。
 @param[out] buf		外部提供的一个二级指针，用于获得一个指向缓冲区空闲部分的指针。
 @return 				返回该指针处，可供使用的空闲空间的字节数目。
 @note    
 */
unsigned int matrix_ringbuf_aquireIn(matrix_ringbuf_handle handle, unsigned char**buf);



/**
 @brief  确认写入size个字节的数据，直接向前移动写指针size 个字节。

 必须与matrix_ringbuf_aquireIn() 配合使用，使用matrix_ringbuf_aquireIn 获取了空闲空间的指针，
在对其写入数据以后，若不调用该函数，则写指针不会发生移动，如同没有写入数据。

 @param[in] handle 	缓冲区句柄。
 @param[in] size		写入的数据字节数目。
 @return 				返回确认的数据长度。即写指针向前移动的字节数目。
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireIn(matrix_ringbuf_handle handle, unsigned int size);



/**
 @brief 获取缓冲区中有效数据长度。

 @param[in] handle 	缓冲区句柄。
 @return 				返回有效数据字节长度。
 @note  
 */
unsigned int matrix_ringbuf_getDataSize(matrix_ringbuf_handle handle);



/**
 @brief 获取缓冲区中空闲空间的长度。

 @param[in] handle 	缓冲区句柄。
 @return 				返回缓冲区中空闲空间的字节长度。
 @note  请注意，如果写指针大于读指针，且读指针位于0边界之后时，
 @note  空闲空间长度为sizeof(out-->end)  + sizeof(start--> in)
 */
unsigned int matrix_ringbuf_getFreeSize(matrix_ringbuf_handle handle);




/**
 @brief 直接向后移动读指针size 个字节。

 这size个字节的数据是刚刚被读过、处理过的，
 如果传入的size 值为0xFFFFFFFF ，则读指针直接回移到被处理过的数据的最前端，
 这部分数据即将被写指针所覆盖，但尚未覆盖，重新取回它们。

 @note 这个函数是非线程安全的，即当一个线程读另一个线程同时写入时，该函数可能出现数据错误。
 @note 使用者须自行保证线程安全。

 @param[in] handle 	缓冲区句柄。
 @param[in] size		读指针直接向反方向移动的字节长度，以重新读取未被覆盖的旧数据。
 @return 				返回成功取回的旧数据长度，这部分数据尚未被覆盖。
 */
unsigned int matrix_ringbuf_rewind(matrix_ringbuf_handle handle, unsigned int size);





/**
 @brief 重置一个环形缓冲区，使其回归初始化状态。该接口不是线程安全的。

 @param[in] handle 	缓冲区句柄。
 @return 				成功返回 MHAL_SUCCESS；失败返回小于0  的值。
 @note 
 */
int matrix_ringbuf_reset(matrix_ringbuf_handle handle);




/**
 @brief 注销一个环形缓冲区，并释放其空间。

 @param[in] handle 	缓冲区句柄。
 @return 				成功返回 MHAL_SUCCESS；失败返回小于0  的值。
 @note 
 */
int matrix_ringbuf_exit(matrix_ringbuf_handle handle) ;


#ifdef __cplusplus
}
#endif

#endif /* __MATRIX_RINGBUF_H__ */
