#ifndef __SCES_CMW_SCES_H__
#define __SCES_CMW_SCES_H__

/// @file sces.h
/// @brief SCES Common Definitions
/// @details This header file defines common types and return values used across the SCES
///          middleware and its components.
/// @author Khose-ie<khose-ie@outlook.com>
/// @date   2024-06-27

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Standard return value enumeration
/// @details Represents standard return values for SCES functions
typedef enum
{
    //===============================
    // General logic errors 0-31
    //===============================
    SCES_RET_OK             = 0, ///< Success
    SCES_RET_PARAM_ERR      = 1, ///< Invalid parameter
    SCES_RET_BUSY           = 2, ///< Resource busy
    SCES_RET_TIMEOUT        = 3, ///< Timeout occurred
    SCES_RET_STACK_OVERFLOW = 4, ///< Stack overflow
    SCES_RET_PERMISSION     = 5, ///< Permission denied
    SCES_RET_NULL_REF       = 6, ///< Null pointer reference

    SCES_RET_NOT_SUPPORT   = 8, ///< Operation not supported
    SCES_RET_NOT_AVAILABLE = 9, ///< Resource not available

    //===============================
    //  Basic operation errors 32-47
    //===============================
    SCES_RET_MEM_ALLOC_FAILURE = 32, ///< Memory allocation failure
    SCES_RET_FORMAT_FAILURE    = 33, ///< Format failure
    SCES_RET_LOW_LEVEL_FAILURE = 34, ///< Low-level API failure

    //===============================
    //  Instance management errors 48-63
    //===============================
    SCES_RET_INSTANCE_CREATE_FAILURE = 48, ///< Failed to create instance
    SCES_RET_INSTANCE_NOT_FOUND      = 49, ///< Instance not found
    SCES_RET_INSTANCE_DUPLICATE      = 50, ///< Instance already exists
    SCES_RET_INSTANCE_IN_USE         = 51, ///< Instance is in use
    SCES_RET_INSTANCE_UNAVAILABLE    = 52, ///< Instance unavailable

    //===============================
    //  MCU specific errors 64-79
    //===============================
    SCES_RET_MCU_HW_FAILURE    = 64, ///< MCU hardware failure
    SCES_RET_MCU_CLOCK_FAILURE = 65, ///< MCU clock or timing error
    SCES_RET_MCU_RESET         = 66, ///< Unexpected MCU reset

    //===============================
    //  OS specific errors 80-95
    //===============================
    SCES_RET_OS_KERNEL_ERR    = 80, ///< OS kernel operation failed
    SCES_RET_OS_EVENT_ERR     = 81, ///< Task deletion failed
    SCES_RET_OS_MEM_POOL_ERR  = 82, ///< Memory pool operation failed
    SCES_RET_OS_MQ_ERR        = 83, ///< Message queue operation failed
    SCES_RET_OS_MUTEX_ERR     = 84, ///< Mutex operation failed
    SCES_RET_OS_SEMAPHORE_ERR = 85, ///< Semaphore operation failed
    SCES_RET_OS_TASK_ERR      = 86, ///< Task deletion failed
    SCES_RET_OS_TIMER_ERR     = 87, ///< Timer creation failed

    //===============================
    //  File system errors 96-111
    //===============================
    SCES_RET_FS_MOUNT_FAILURE     = 96,  ///< File system mount failure
    SCES_RET_FS_FORMAT_FAILURE    = 97,  ///< File system format failure
    SCES_RET_FS_NOT_VALID_FS      = 98,  ///< No valid file system found
    SCES_RET_FS_NOT_FILE          = 99,  ///< Not a file
    SCES_RET_FS_NOT_DIR           = 100, ///< Not a directory
    SCES_RET_FS_DIR_NOT_EMPTY     = 101, ///< File system unmount error
    SCES_RET_FS_DISK_NOT_READY    = 102, ///< Disk not ready
    SCES_RET_DISK_WRITE_PROTECTED = 103, ///< Disk write protected
    SCES_RET_DISK_IO_ERR          = 104, ///< Low-level disk I/O error

    //===============================
    //  Network errors 112-127
    //===============================

    //===============================
    //  Peripheral extension errors 128-254
    //===============================

    //===============================
    //  Unknown error 255
    //===============================
    SCES_RET_UNKNOWN = 255 ///< Unknown error
} scesRetVal_t;

/// @brief Type used for memory alignment
/// @details This type is used to ensure proper memory alignment for dynamic allocations.
#define sces_aligned_sizeof(type, aligned_type)                                                    \
    (((sizeof(type) + (sizeof(aligned_type))) - ((aligned_type)1)) / sizeof(aligned_type))

#endif // __SCES_CMW_SCES_H__
