package ffmpeg4kj.av

// const val MKTAG= (a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
fun MKTAG(a: Number, b: Number, c: Number, d: Number): Int = ((a.toInt()) or ((b.toInt()) shl 8) or ((c.toInt()) shl 16) or ((d.toInt()) shl 24))
fun MKTAG(a: Char, b: Char, c: Char, d: Char): Int = MKTAG(a.toByte(), b.toByte(), c.toByte(), d.toByte())

fun AVERROR(e: Number): Int = if (e.toInt() < 0) { e.toInt() } else { -e.toInt() }
fun AVUNERROR(e: Number): Int = if (e.toInt() < 0) { e.toInt() } else { -e.toInt() }

fun FFERRTAG(a: Number, b: Number, c: Number, d: Number): Int = (-MKTAG(a, b, c, d))
fun FFERRTAG(a: Char, b: Char, c: Char, d: Char): Int = (-MKTAG(a.toByte(), b.toByte(), c.toByte(), d.toByte()))


/*
 * Error codes
 */

const val EPERM           = 1               /* Operation not permitted */
const val ENOENT          = 2               /* No such file or directory */
const val ESRCH           = 3               /* No such process */
const val EINTR           = 4               /* Interrupted system call */
const val EIO             = 5               /* Input/output error */
const val ENXIO           = 6               /* Device not configured */
const val E2BIG           = 7               /* Argument list too long */
const val ENOEXEC         = 8               /* Exec format error */
const val EBADF           = 9               /* Bad file descriptor */
const val ECHILD          = 10              /* No child processes */
const val EDEADLK         = 11              /* Resource deadlock avoided */
/* 11 was EAGAIN */
const val ENOMEM          = 12              /* Cannot allocate memory */
const val EACCES          = 13              /* Permission denied */
const val EFAULT          = 14              /* Bad address */
const val ENOTBLK         = 15              /* Block device required */
const val EBUSY           = 16              /* Device / Resource busy */
const val EEXIST          = 17              /* File exists */
const val EXDEV           = 18              /* Cross-device link */
const val ENODEV          = 19              /* Operation not supported by device */
const val ENOTDIR         = 20              /* Not a directory */
const val EISDIR          = 21              /* Is a directory */
const val EINVAL          = 22              /* Invalid argument */
const val ENFILE          = 23              /* Too many open files in system */
const val EMFILE          = 24              /* Too many open files */
const val ENOTTY          = 25              /* Inappropriate ioctl for device */
const val ETXTBSY         = 26              /* Text file busy */
const val EFBIG           = 27              /* File too large */
const val ENOSPC          = 28              /* No space left on device */
const val ESPIPE          = 29              /* Illegal seek */
const val EROFS           = 30              /* Read-only file system */
const val EMLINK          = 31              /* Too many links */
const val EPIPE           = 32              /* Broken pipe */

/* math software */
const val EDOM            = 33              /* Numerical argument out of domain */
const val ERANGE          = 34              /* Result too large */

/* non-blocking and interrupt i/o */
const val EAGAIN          = 35              /* Resource temporarily unavailable */
const val EWOULDBLOCK     = EAGAIN          /* Operation would block */
const val EINPROGRESS     = 36              /* Operation now in progress */
const val EALREADY        = 37              /* Operation already in progress */

/* ipc/network software -- argument errors */
const val ENOTSOCK        = 38              /* Socket operation on non-socket */
const val EDESTADDRREQ    = 39              /* Destination address required */
const val EMSGSIZE        = 40              /* Message too long */
const val EPROTOTYPE      = 41              /* Protocol wrong type for socket */
const val ENOPROTOOPT     = 42              /* Protocol not available */
const val EPROTONOSUPPORT = 43              /* Protocol not supported */

const val ESOCKTNOSUPPORT = 44              /* Socket type not supported */

const val ENOTSUP         = 45              /* Operation not supported */

const val EPFNOSUPPORT    = 46              /* Protocol family not supported */

const val EAFNOSUPPORT    = 47              /* Address family not supported by protocol family */
const val EADDRINUSE      = 48              /* Address already in use */
const val EADDRNOTAVAIL   = 49              /* Can't assign requested address */

/* ipc/network software -- operational errors */
const val ENETDOWN        = 50              /* Network is down */
const val ENETUNREACH     = 51              /* Network is unreachable */
const val ENETRESET       = 52              /* Network dropped connection on reset */
const val ECONNABORTED    = 53              /* Software caused connection abort */
const val ECONNRESET      = 54              /* Connection reset by peer */
const val ENOBUFS         = 55              /* No buffer space available */
const val EISCONN         = 56              /* Socket is already connected */
const val ENOTCONN        = 57              /* Socket is not connected */

const val ESHUTDOWN       = 58              /* Can't send after socket shutdown */
const val ETOOMANYREFS    = 59              /* Too many references: can't splice */

const val ETIMEDOUT       = 60              /* Operation timed out */
const val ECONNREFUSED    = 61              /* Connection refused */

const val ELOOP           = 62              /* Too many levels of symbolic links */
const val ENAMETOOLONG    = 63              /* File name too long */

/* should be rearranged */

const val EHOSTDOWN       = 64              /* Host is down */

const val EHOSTUNREACH    = 65              /* No route to host */
const val ENOTEMPTY       = 66              /* Directory not empty */

/* quotas & mush */

const val EPROCLIM        = 67              /* Too many processes */
const val EUSERS          = 68              /* Too many users */

const val EDQUOT          = 69              /* Disc quota exceeded */

/* Network File System */
const val ESTALE          = 70              /* Stale NFS file handle */

const val EREMOTE         = 71              /* Too many levels of remote in path */
const val EBADRPC         = 72              /* RPC struct is bad */
const val ERPCMISMATCH    = 73              /* RPC version wrong */
const val EPROGUNAVAIL    = 74              /* RPC prog. not avail */
const val EPROGMISMATCH   = 75              /* Program version wrong */
const val EPROCUNAVAIL    = 76              /* Bad procedure for program */

const val ENOLCK          = 77              /* No locks available */
const val ENOSYS          = 78              /* Function not implemented */

const val EFTYPE          = 79              /* Inappropriate file type or format */
const val EAUTH           = 80              /* Authentication error */
const val ENEEDAUTH       = 81              /* Need authenticator */

/* Intelligent device errors */
const val EPWROFF         = 82      /* Device power is off */
const val EDEVERR         = 83      /* Device error, e.g. paper out */

const val EOVERFLOW       = 84              /* Value too large to be stored in data type */

/* Program loading errors */
const val EBADEXEC        = 85      /* Bad executable */
const val EBADARCH        = 86      /* Bad CPU type in executable */
const val ESHLIBVERS      = 87      /* Shared library version mismatch */
const val EBADMACHO       = 88      /* Malformed Macho file */

const val ECANCELED       = 89              /* Operation canceled */

const val EIDRM           = 90              /* Identifier removed */
const val ENOMSG          = 91              /* No message of desired type */
const val EILSEQ          = 92              /* Illegal byte sequence */
const val ENOATTR         = 93              /* Attribute not found */

const val EBADMSG         = 94              /* Bad message */
const val EMULTIHOP       = 95              /* Reserved */
const val ENODATA         = 96              /* No message available on STREAM */
const val ENOLINK         = 97              /* Reserved */
const val ENOSR           = 98              /* No STREAM resources */
const val ENOSTR          = 99              /* Not a STREAM */
const val EPROTO          = 100             /* Protocol error */
const val ETIME           = 101             /* STREAM ioctl timeout */

/* This value is only discrete when compiling __DARWIN_UNIX03, or KERNEL */
const val EOPNOTSUPP      = 102             /* Operation not supported on socket */

const val ENOPOLICY       = 103             /* No such policy registered */

const val ENOTRECOVERABLE = 104             /* State not recoverable */
const val EOWNERDEAD      = 105             /* Previous owner died */

const val EQFULL          = 106             /* Interface output queue is full */
const val ELAST           = 106             /* Must be equal largest errno */


val AVERROR_EAGAIN             = AVERROR(EAGAIN)
val AVERROR_BSF_NOT_FOUND      = FFERRTAG(0xF8.toChar(),'B','S','F') ///< Bitstream filter not found
val AVERROR_BUG                = FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
val AVERROR_BUFFER_TOO_SMALL   = FFERRTAG( 'B','U','F','S') ///< Buffer too small
val AVERROR_DECODER_NOT_FOUND  = FFERRTAG(0xF8.toChar(),'D','E','C') ///< Decoder not found
val AVERROR_DEMUXER_NOT_FOUND  = FFERRTAG(0xF8.toChar(),'D','E','M') ///< Demuxer not found
val AVERROR_ENCODER_NOT_FOUND  = FFERRTAG(0xF8.toChar(),'E','N','C') ///< Encoder not found
val AVERROR_EOF                = FFERRTAG( 'E','O','F',' ') ///< End of file
val AVERROR_EXIT               = FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
val AVERROR_EXTERNAL           = FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
val AVERROR_FILTER_NOT_FOUND   = FFERRTAG(0xF8.toChar(),'F','I','L') ///< Filter not found
val AVERROR_INVALIDDATA        = FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
val AVERROR_MUXER_NOT_FOUND    = FFERRTAG(0xF8.toChar(),'M','U','X') ///< Muxer not found
val AVERROR_OPTION_NOT_FOUND   = FFERRTAG(0xF8.toChar(),'O','P','T') ///< Option not found
val AVERROR_PATCHWELCOME       = FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
val AVERROR_PROTOCOL_NOT_FOUND = FFERRTAG(0xF8.toChar(),'P','R','O') ///< Protocol not found

val AVERROR_STREAM_NOT_FOUND   = FFERRTAG(0xF8.toChar(),'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
val AVERROR_BUG2               = FFERRTAG( 'B','U','G',' ')
val AVERROR_UNKNOWN            = FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
val AVERROR_EXPERIMENTAL       = (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
val AVERROR_INPUT_CHANGED      = (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
val AVERROR_OUTPUT_CHANGED     = (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
val AVERROR_HTTP_BAD_REQUEST   = FFERRTAG(0xF8.toChar(),'4','0','0')
val AVERROR_HTTP_UNAUTHORIZED  = FFERRTAG(0xF8.toChar(),'4','0','1')
val AVERROR_HTTP_FORBIDDEN     = FFERRTAG(0xF8.toChar(),'4','0','3')
val AVERROR_HTTP_NOT_FOUND     = FFERRTAG(0xF8.toChar(),'4','0','4')
val AVERROR_HTTP_OTHER_4XX     = FFERRTAG(0xF8.toChar(),'4','X','X')
val AVERROR_HTTP_SERVER_ERROR  = FFERRTAG(0xF8.toChar(),'5','X','X')

val AV_ERROR_MAX_STRING_SIZE = 64
