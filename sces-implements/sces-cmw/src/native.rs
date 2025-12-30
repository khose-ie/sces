use sces::value::{ErrValue, RetValue};

/// SCES return value enumeration
///
/// Represents standard return values for SCES C functions
/// Aligned with scesRetVal_t in sces.h
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ScesRetVal
{
    //===============================
    // General logic errors 0-31
    //===============================
    /// Operation completed successfully.
    Ok = 0,
    /// Invalid parameter.
    ParamErr = 1,
    /// Resource busy.
    Busy = 2,
    /// Timeout occurred.
    Timeout = 3,
    /// Stack overflow.
    StackOverflow = 4,
    /// Permission denied.
    Permission = 5,
    /// Null pointer reference.
    NullRef = 6,
    /// Operation not supported.
    NotSupport = 8,
    /// Resource not available.
    NotAvailable = 9,

    //===============================
    // Basic operation errors 32-47
    //===============================
    /// Memory allocation failure.
    MemAllocFailure = 32,
    /// Format failure.
    FormatFailure = 33,
    /// Low-level API failure.
    LowLevelFailure = 34,

    //===============================
    // Instance management errors 48-63
    //===============================
    /// Failed to create instance.
    InstanceCreateFailure = 48,
    /// Instance not found.
    InstanceNotFound = 49,
    /// Instance already exists.
    InstanceDuplicate = 50,
    /// Instance is in use.
    InstanceInUse = 51,
    /// Instance unavailable.
    InstanceUnavailable = 52,

    //===============================
    // MCU specific errors 64-79
    //===============================
    /// MCU hardware failure.
    McuHwFailure = 64,
    /// MCU clock or timing error.
    McuClockFailure = 65,
    /// Unexpected MCU reset.
    McuReset = 66,

    //===============================
    // OS specific errors 80-95
    //===============================
    /// OS kernel operation failed.
    OsKernelErr = 80,
    /// OS event operation failed.
    OsEventErr = 81,
    /// OS memory pool operation failed.
    OsMemPoolErr = 82,
    /// OS message queue operation failed.
    OsMqErr = 83,
    /// OS mutex operation failed.
    OsMutexErr = 84,
    /// OS semaphore operation failed.
    OsSemaphoreErr = 85,
    /// OS task operation failed.
    OsTaskErr = 86,
    /// OS timer operation failed.
    OsTimerErr = 87,

    //===============================
    // File system errors 96-111
    //===============================
    /// File system mount failure.
    FsMountFailure = 96,
    /// File system format failure.
    FsFormatFailure = 97,
    /// No valid file system found.
    FsNotValidFs = 98,
    /// Not a file.
    FsNotFile = 99,
    /// Not a directory.
    FsNotDir = 100,
    /// Directory is not empty.
    FsDirNotEmpty = 101,
    /// Disk not ready.
    FsDiskNotReady = 102,
    /// Disk write protected.
    FsDiskWriteProtected = 103,
    /// Low-level disk I/O error.
    FsDiskIoErr = 104,

    //===============================
    // Unknown error 255
    //===============================
    /// Unknown error.
    Unknown = 255,
}

impl From<ScesRetVal> for ErrValue
{
    fn from(ret: ScesRetVal) -> Self
    {
        match ret
        {
            ScesRetVal::Ok => ErrValue::None,
            ScesRetVal::ParamErr => ErrValue::Param,
            ScesRetVal::Busy => ErrValue::Busy,
            ScesRetVal::Timeout => ErrValue::Timeout,
            ScesRetVal::StackOverflow => ErrValue::StackOverflow,
            ScesRetVal::Permission => ErrValue::Permission,
            ScesRetVal::NullRef => ErrValue::NullReference,
            ScesRetVal::NotSupport => ErrValue::NotSupport,
            ScesRetVal::NotAvailable => ErrValue::NotAvailable,
            ScesRetVal::MemAllocFailure => ErrValue::MemAllocFailure,
            ScesRetVal::FormatFailure => ErrValue::FormatFailure,
            ScesRetVal::LowLevelFailure => ErrValue::LowLevelFailure,
            ScesRetVal::InstanceCreateFailure => ErrValue::InstanceCreateFailure,
            ScesRetVal::InstanceNotFound => ErrValue::InstanceNotFound,
            ScesRetVal::InstanceDuplicate => ErrValue::InstanceDuplicate,
            ScesRetVal::InstanceInUse => ErrValue::InstanceInUse,
            ScesRetVal::InstanceUnavailable => ErrValue::InstanceUnavailable,
            ScesRetVal::McuHwFailure => ErrValue::McuHwFailure,
            ScesRetVal::McuClockFailure => ErrValue::McuClockFailure,
            ScesRetVal::McuReset => ErrValue::McuReset,
            ScesRetVal::OsKernelErr => ErrValue::OsKernelErr,
            ScesRetVal::OsEventErr => ErrValue::OsEventErr,
            ScesRetVal::OsMemPoolErr => ErrValue::OsMemPoolErr,
            ScesRetVal::OsMqErr => ErrValue::OsMessageQueueErr,
            ScesRetVal::OsMutexErr => ErrValue::OsMutexErr,
            ScesRetVal::OsSemaphoreErr => ErrValue::OsSemaphoreErr,
            ScesRetVal::OsTaskErr => ErrValue::OsTaskErr,
            ScesRetVal::OsTimerErr => ErrValue::OsTimerErr,
            ScesRetVal::FsMountFailure => ErrValue::FsMountFailure,
            ScesRetVal::FsFormatFailure => ErrValue::FsFormatFailure,
            ScesRetVal::FsNotValidFs => ErrValue::FsNotValidFs,
            ScesRetVal::FsNotFile => ErrValue::FsNotFile,
            ScesRetVal::FsNotDir => ErrValue::FsNotDir,
            ScesRetVal::FsDirNotEmpty => ErrValue::FsDirNotEmpty,
            ScesRetVal::FsDiskNotReady => ErrValue::FsDiskNotReady,
            ScesRetVal::FsDiskWriteProtected => ErrValue::FsDiskWriteProtected,
            ScesRetVal::FsDiskIoErr => ErrValue::FsDiskIoErr,
            ScesRetVal::Unknown => ErrValue::Unknown,
        }
    }
}

impl From<ErrValue> for ScesRetVal
{
    fn from(err: ErrValue) -> Self
    {
        match err
        {
            ErrValue::None => ScesRetVal::Ok,
            ErrValue::Param => ScesRetVal::ParamErr,
            ErrValue::Busy => ScesRetVal::Busy,
            ErrValue::Timeout => ScesRetVal::Timeout,
            ErrValue::StackOverflow => ScesRetVal::StackOverflow,
            ErrValue::Permission => ScesRetVal::Permission,
            ErrValue::NullReference => ScesRetVal::NullRef,
            ErrValue::NotSupport => ScesRetVal::NotSupport,
            ErrValue::NotAvailable => ScesRetVal::NotAvailable,
            ErrValue::MemAllocFailure => ScesRetVal::MemAllocFailure,
            ErrValue::FormatFailure => ScesRetVal::FormatFailure,
            ErrValue::LowLevelFailure => ScesRetVal::LowLevelFailure,
            ErrValue::InstanceCreateFailure => ScesRetVal::InstanceCreateFailure,
            ErrValue::InstanceNotFound => ScesRetVal::InstanceNotFound,
            ErrValue::InstanceDuplicate => ScesRetVal::InstanceDuplicate,
            ErrValue::InstanceInUse => ScesRetVal::InstanceInUse,
            ErrValue::InstanceUnavailable => ScesRetVal::InstanceUnavailable,
            ErrValue::McuHwFailure => ScesRetVal::McuHwFailure,
            ErrValue::McuClockFailure => ScesRetVal::McuClockFailure,
            ErrValue::McuReset => ScesRetVal::McuReset,
            ErrValue::OsKernelErr => ScesRetVal::OsKernelErr,
            ErrValue::OsEventErr => ScesRetVal::OsEventErr,
            ErrValue::OsMemPoolErr => ScesRetVal::OsMemPoolErr,
            ErrValue::OsMessageQueueErr => ScesRetVal::OsMqErr,
            ErrValue::OsMutexErr => ScesRetVal::OsMutexErr,
            ErrValue::OsSemaphoreErr => ScesRetVal::OsSemaphoreErr,
            ErrValue::OsTaskErr => ScesRetVal::OsTaskErr,
            ErrValue::OsTimerErr => ScesRetVal::OsTimerErr,
            ErrValue::FsMountFailure => ScesRetVal::FsMountFailure,
            ErrValue::FsFormatFailure => ScesRetVal::FsFormatFailure,
            ErrValue::FsNotValidFs => ScesRetVal::FsNotValidFs,
            ErrValue::FsNotFile => ScesRetVal::FsNotFile,
            ErrValue::FsNotDir => ScesRetVal::FsNotDir,
            ErrValue::FsDirNotEmpty => ScesRetVal::FsDirNotEmpty,
            ErrValue::FsDiskNotReady => ScesRetVal::FsDiskNotReady,
            ErrValue::FsDiskWriteProtected => ScesRetVal::FsDiskWriteProtected,
            ErrValue::FsDiskIoErr => ScesRetVal::FsDiskIoErr,
            ErrValue::Unknown => ScesRetVal::Unknown,
        }
    }
}

impl ScesRetVal
{
    pub fn map<T>(&self, value: T) -> RetValue<T>
    {
        match self
        {
            ScesRetVal::Ok => Ok(value),
            _ => Err((*self).into()),
        }
    }
}
