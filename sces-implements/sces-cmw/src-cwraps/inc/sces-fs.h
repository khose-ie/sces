#ifndef __SCES_CMW_SCES_FS_H__
#define __SCES_CMW_SCES_FS_H__

/// @file sces-fs.h
/// @brief SCES CMW File System (FS) module public API
/// @details This header file defines the public API for the SCES CMW File System (FS) module.
///     It includes type definitions, constants, and function prototypes for file system operations.
/// @author Khose-ie<khose-ie@outlook.com>
/// @date 2024-06-10

#include <sces.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief File system handle type
/// @details This type represents a handle to a mounted file system.
typedef void* scesFsHandle_t;

/// @brief File handle type
/// @details This type represents a handle to an open file in the file system.
typedef void* scesFileHandle_t;

/// @brief Directory handle type
/// @details This type represents a handle to an open directory in the file system.
typedef void* scesDirHandle_t;

/// @brief File open mode mask type
/// @details This type represents a bitmask for file open modes, allowing combination of multiple
///     modes using bitwise OR operations.
typedef uint32_t scesFileOpenModeMask_t;

/// @brief File system kind enumeration
/// @details This enumeration defines the kinds of file systems supported.
///     The SCES_FS_AUTO_DETECT option allows automatic detection of the file system type.
typedef enum
{
    SCES_FS_AUTO_DETECT = 0,
    SCES_FS_FAT12       = 1,
    SCES_FS_FAT16       = 2,
    SCES_FS_FAT32       = 3,
    SCES_FS_EXFAT       = 4
} scesFsKind_t;

/// @brief File item kind enumeration
/// @details This enumeration defines the kinds of file system items: files and directories.
typedef enum
{
    SCES_FILE_FILE = 0,
    SCES_FILE_DIR  = 1,
} scesFileItemKind_t;

/// @brief File open mode enumeration
/// @details This enumeration defines the various modes for opening files in the file system.
typedef enum
{
    SCES_FILE_READ   = 0x01,
    SCES_FILE_WRITE  = 0x02,
    SCES_FILE_APPEND = 0x04,
    SCES_FILE_TRUNC  = 0x08,
} scesFileOpenMode_t;

/// @brief File item state structure
/// @details This structure holds the state information of a file system item, including its kind,
///     name, and size.
typedef struct
{
    scesFileItemKind_t kind;
    struct
    {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    } time_stamp;
    uint8_t attributes;
    uint64_t size;
} scesFileItemState_t;

/// @brief File system information structure
/// @details This structure holds information about a file system, including its kind,
///     number of FATs, directory entries, and sectors per cluster.
typedef struct
{
    scesFsKind_t kind;
    uint32_t num_of_fats;
    uint32_t directory_entries;
    uint32_t sectors_per_cluster;
} scesFsInfo_t;

/// @brief File disk I/O driver structure
/// @details This structure defines the disk I/O driver functions for file system operations.
typedef struct
{
    /// @brief Read sectors from the disk
    /// @param sector    Starting sector number to read from
    /// @param count     Number of sectors to read
    /// @param buffer    Pointer to the buffer to store the read data
    /// @return SCES_RET_OK on success, error code otherwise
    scesRetVal_t (*read)(uint32_t sector, uint32_t count, uint8_t* buffer);

    /// @brief Write sectors to the disk
    /// @param sector    Starting sector number to write to
    /// @param count     Number of sectors to write
    /// @param buffer    Pointer to the buffer containing the data to write
    /// @return SCES_RET_OK on success, error code otherwise
    scesRetVal_t (*write)(uint32_t sector, uint32_t count, const uint8_t* buffer);

    /// @brief Flush any cached data to the disk
    /// @return SCES_RET_OK on success, error code otherwise
    scesRetVal_t (*flush)(void);

    /// @brief Trim (erase) sectors on the disk
    /// @param start_sector  Starting sector number to trim
    /// @param sector_count  Number of sectors to trim
    /// @return SCES_RET_OK on success, error code otherwise
    scesRetVal_t (*trim)(uint32_t start_sector, uint32_t sector_count);

    /// @brief Get the status of the disk
    /// @return SCES_RET_OK on success, error code otherwise
    scesRetVal_t (*status)(void);

    /// @brief Get the total number of sectors on the disk
    /// @return Total number of sectors
    uint32_t (*sector_count)(void);

    /// @brief Get the size of a sector in bytes
    /// @return Size of a sector in bytes
    uint32_t (*sector_size)(void);

    /// @brief Get the size of a block in sectors
    /// @return Size of a block in sectors
    uint32_t (*block_size)(void);
} scesFileDiskIO_t;

//===============================
//  File system (media)
//===============================

/// @brief Initialize file system subsystem
/// @details This function initializes the global file system subsystem.
///     It must be called once before any sces_fs_mount() operation. For some file systems (e.g.
///     FileX), this function performs underlying system-level initialization.
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_initialize(void);

/// @brief Set disk I/O driver function
/// @details This function sets the disk I/O driver function for the specified disk number.
/// @param disk_num Disk number for which to set the disk I/O driver function
/// @param diskio Pointer to the disk I/O driver structure
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_set_diskio(uint32_t disk_num, const scesFileDiskIO_t* diskio);

/// @brief Format a file system
/// @details This function formats a file system with the specified parameters.
/// @param name   Name of the file system
/// @param disk_num Disk number to format
/// @param info   Information about the file system to format
/// @return SCES_RET_OK on success, error code otherwise
/// @attention This operation will erase all data on the specified disk.
/// @attention The disk I/O driver for the specified disk number must be set
///     using sces_fs_set_diskio() before calling this function.
/// @attention This function will not initialize the disk; it must be done prior to calling this
///     function.
scesRetVal_t sces_fs_format(const char* name, uint32_t disk_num, const scesFsInfo_t* info);

/// @brief Mount a file system
/// @details This function mounts a file system with the specified parameters.
/// @param name          Name of the file system
/// @return Handle to the mounted file system, or NULL on failure
/// @attention The disk I/O driver for the specified disk number must be set
///     using sces_fs_set_diskio() before calling this function.
/// @attention This function will not initialize the disk; it must be done prior to calling this
///     function.
scesFsHandle_t sces_fs_mount(const char* name, uint32_t disk_num);

/// @brief Unmount a file system
/// @details This function unmounts the specified file system.
/// @param fs Handle to the file system to unmount
void sces_fs_unmount(scesFsHandle_t fs);

/// @brief Get the name of the file system
/// @details This function retrieves the name of the specified file system.
/// @param fs Handle to the file system
/// @return Pointer to the file system's name string
const char* sces_fs_name(scesFsHandle_t fs);

/// @brief Synchronize the file system
/// @details This function synchronizes the specified file system, ensuring that all pending
///     changes are written to the underlying storage.
/// @param fs Handle to the file system
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_sync(scesFsHandle_t fs);

/// @brief Create an empty file
/// @details Creates an empty file at the specified path.
///     If the file already exists, an error is returned.
/// @param fs Handle to the file system
/// @param path Path of the file to create
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_create_file(scesFsHandle_t fs, const char* path);

/// @brief Remove a file
/// @details Removes the file at the specified path.
/// @param fs Handle to the file system
/// @param path Path of the file to remove
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_remove_file(scesFsHandle_t fs, const char* path);

/// @brief Create a directory
/// @details Creates a directory at the specified path.
///     If the directory already exists, an error is returned.
/// @param fs   Handle to the file system
/// @param path Path of the directory to create
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_create_dir(scesFsHandle_t fs, const char* path);

/// @brief Remove a directory
/// @details Removes the directory at the specified path.
///     The directory must be empty to be removed successfully.
/// @param fs   Handle to the file system
/// @param path Path of the directory to remove
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_remove_dir(scesFsHandle_t fs, const char* path);

/// @brief  Move or rename a file or directory
/// @details This function moves or renames a file or directory from old_path to new_path.
///     It do the same operation for both files and directories, and like the "rename" function
///     in standard C library. It can't move files or directories across different mounted file
///     systems.
/// @param fs        Handle to the file system
/// @param old_path  Current path of the file or directory
/// @param new_path  New path of the file or directory
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_move(scesFsHandle_t fs, const char* old_path, const char* new_path);

/// @brief Get the state of a file or directory
/// @details This function retrieves the state information of a file or directory at the specified
///     path.
/// @param fs    Handle to the file system
/// @param path  Path of the file or directory
/// @param state Pointer to a scesFileItemState_t structure to receive the state information
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_fs_item_state(scesFsHandle_t fs, const char* path, scesFileItemState_t* state);

//===============================
//  File operations
//===============================

/// @brief Open a file
/// @details This function opens a file at the specified path with the given mode.
/// @param fs    Handle to the file system
/// @param path  Path of the file to open
/// @param mode  File open mode mask
/// @return Handle to the opened file, or NULL on failure
scesFileHandle_t sces_file_open(scesFsHandle_t fs, const char* path, scesFileOpenModeMask_t mode);

/// @brief Close a file
/// @details This function closes the specified file and releases its resources.
/// @param file Handle to the file to be closed
void sces_file_close(scesFileHandle_t file);

/// @brief Read data from a file
/// @details This function reads data from the specified file into the provided buffer.
/// @param file   Handle to the file to read from
/// @param buffer Pointer to the buffer to receive the data
/// @param size   Number of bytes to read
/// @param read_size Pointer to a variable to receive the number of bytes actually read
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_read(scesFileHandle_t file, void* buffer, uint32_t size,
                            uint32_t* read_size);

/// @brief Write data to a file
/// @details This function writes data to the specified file from the provided buffer.
/// @param file   Handle to the file to write to
/// @param buffer Pointer to the buffer containing the data to write
/// @param size   Number of bytes to write
/// @param written_size Pointer to a variable to receive the number of bytes actually written
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_write(scesFileHandle_t file, const void* buffer, uint32_t size,
                             uint32_t* written_size);

/// @brief Seek to a position in a file
/// @details This function sets the file position indicator for the specified file.
/// @param file   Handle to the file
/// @param offset Offset in bytes to seek
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_seek(scesFileHandle_t file, uint64_t offset);

/// @brief Seek to a position in a file from the current position
/// @details This function sets the file position indicator for the specified file,
///     relative to the current position.
/// @param file   Handle to the file
/// @param offset Offset in bytes to seek from the current position
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_seek_from_current(scesFileHandle_t file, uint64_t offset);

/// @brief Get the current position in a file
/// @details This function retrieves the current file position indicator for the specified file.
/// @param file Handle to the file
/// @return Current position in bytes from the beginning of the file
uint32_t sces_file_tell(scesFileHandle_t file);

/// @brief Get the size of a file
/// @details This function retrieves the size of the specified file in bytes.
/// @param file Handle to the file
/// @return Size of the file in bytes
uint32_t sces_file_size(scesFileHandle_t file);

/// @brief Truncate a file to the current position
/// @details This function truncates the specified file to the current file position.
/// @param file Handle to the file
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_truncate(scesFileHandle_t file);

/// @brief Synchronize a file
/// @details This function synchronizes the specified file, ensuring that all pending changes
///     are written to the underlying storage.
/// @param file Handle to the file
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_file_sync(scesFileHandle_t file);

//===============================
//  Directory operations
//===============================

/// @brief Open a directory
/// @details This function opens a directory at the specified path.
/// @param fs   Handle to the file system
/// @param path Path of the directory to open
/// @return Handle to the opened directory, or NULL on failure
scesDirHandle_t sces_dir_open(scesFsHandle_t fs, const char* path);

/// @brief Close a directory
/// @details This function closes the specified directory and releases its resources.
/// @param dir Handle to the directory to be closed
void sces_dir_close(scesDirHandle_t dir);

/// @brief Get the next item in a directory
/// @details This function retrieves the next item in the specified directory.
/// @param dir   Handle to the directory
/// @param state Pointer to a scesFileItemState_t structure to receive the item information
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_dir_next_item_state(scesDirHandle_t dir, scesFileItemState_t* state);

/// @brief Rewind a directory
/// @details This function rewinds the specified directory to the beginning.
/// @param dir Handle to the directory
/// @return SCES_RET_OK on success, error code otherwise
scesRetVal_t sces_dir_rewind(scesDirHandle_t dir);

#ifdef __cplusplus
}
#endif

#endif // __SCES_CMW_SCES_FS_H__