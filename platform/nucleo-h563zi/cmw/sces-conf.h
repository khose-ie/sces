/// @file sces-conf.example.h
/// @brief SCES Configuration Header Example
/// @details This is an example configuration header file for the SCES OS abstraction layer.
///          It defines constants and macros that can be modified to customize the behavior
///          of the OS abstraction layer according to the specific requirements of the target
///          application and underlying operating system.
/// @note This file should be copied and renamed to sces-conf.h and modified as needed.
/// @author Khose-ie<khose-ie@outlook.com>
/// @date 2024-06-10

#ifndef __SCES_CONF_H__
#define __SCES_CONF_H__

//============================================================================================
/// @brief OS Stack Configuration
/// @details These constants and macros define the configuration for the OS stack byte pool.
//============================================================================================

#define SCES_OS_STACK_SIZE (1024 * 60)
// #define SCES_OS_STACK_EX_MEM (os_stack_mem)

//============================================================================================
/// @brief OS Memory Pool Configuration
/// @details These constants define the block sizes and counts for the OS memory pool.
///          Modify these values according to your application's memory allocation patterns.
//============================================================================================

#define SCES_OS_MEM_POOL_BKSZ_1 (256)
#define SCES_OS_MEM_POOL_BKSZ_2 (512)
#define SCES_OS_MEM_POOL_BKSZ_3 (1024)
#define SCES_OS_MEM_POOL_BKSZ_4 (2048)
#define SCES_OS_MEM_POOL_BKCT_1 (32)
#define SCES_OS_MEM_POOL_BKCT_2 (16)
#define SCES_OS_MEM_POOL_BKCT_3 (8)
#define SCES_OS_MEM_POOL_BKCT_4 (4)

///============================================================================================
/// @brief File System Configuration
/// @details These constants and macros define the configuration for the file system abstraction layer.
///          Modify these values according to your application's file system requirements.
///============================================================================================

#define SCES_FS_MEDIA_COUNT (1)
#define SCES_FS_WORK_STACK_SIZE (4096)
#define SCES_FS_MAX_OPEN_COUNT (8)

#endif // __SCES_CONF_H__