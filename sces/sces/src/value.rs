//! The common return value type and error kinds list.

use core::cell::BorrowMutError;

/// `ErrValue` includes all kinds of errors' code in sces.
///
/// Every function in sces which will return a result may has exception situation,
/// and this exception situation, will return an `ErrValue`.
/// The caller should get the code, judge it and do the related handle process.
///
/// This enum is aligned with the `scesRetVal_t` enumeration defined in sces.h.
#[derive(Debug)]
#[repr(u8)]
pub enum ErrValue
{
    //===============================
    // General logic errors 0-31
    //===============================
    /// No error occurred. Success.
    None = 0,

    /// Invalid parameter passed to function.
    Param = 1,

    /// Resource is busy and cannot perform the operation.
    Busy = 2,

    /// Operation timed out.
    Timeout = 3,

    /// Stack overflow occurred.
    StackOverflow = 4,

    /// Permission denied for the operation.
    Permission = 5,

    /// Null pointer or object reference encountered.
    NullReference = 6,

    /// Operation not supported.
    NotSupport = 8,

    /// Resource not available.
    NotAvailable = 9,

    //===============================
    // Basic operation errors 32-47
    //===============================
    /// Memory allocation failed.
    MemAllocFailure = 32,

    /// Format operation failed.
    FormatFailure = 33,

    /// Low-level API operation failed.
    LowLevelFailure = 34,

    //===============================
    // Instance management errors 48-63
    //===============================
    /// Failed to create instance.
    InstanceCreateFailure = 48,

    /// Instance not found.
    InstanceNotFound = 49,

    /// Instance already exists (duplicate).
    InstanceDuplicate = 50,

    /// Instance is in use and cannot be borrowed.
    InstanceInUse = 51,

    /// Instance is unavailable.
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
    OsMessageQueueErr = 83,

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

    /// Directory is not empty.
    FsDirNotEmpty = 97,

    /// Not a file.
    FsNotFile = 98,

    /// Not a directory.
    FsNotDir = 99,

    //===============================
    // Network errors 112-127
    //===============================
    // Reserved for future use

    //===============================
    // Peripheral extension errors 128-254
    //===============================
    // Reserved for future use

    //===============================
    // Unknown error 255
    //===============================
    /// Unknown error occurred.
    Unknown = 255,
}

impl From<BorrowMutError> for ErrValue
{
    /// When occur the `BorrowMutError`, it could be covert to `ErrValue::InstanceInUse`.
    fn from(_: BorrowMutError) -> Self
    {
        ErrValue::InstanceInUse
    }
}

/// `RetValue` is common type of return value for sces functions.
///
/// It is a packed type of RUST `Result<T, E>` type, but specificed the E with ErrValue,
/// which is also the common error code definition of sces.
pub type RetValue<T> = core::result::Result<T, ErrValue>;

impl From<ErrValue> for RetValue<()>
{
    /// Convert an `ErrValue` into a `RetValue<()>`.
    ///
    /// If the `ErrValue` is `ErrValue::None`, it will return `Ok(())`,
    /// otherwise it will return `Err(err)`.
    fn from(err: ErrValue) -> Self
    {
        match err
        {
            ErrValue::None => Ok(()),
            _ => Err(err),
        }
    }
}
