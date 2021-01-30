package ffmpeg4kj.av

const val AVPROBE_SCORE_EXTENSION  = 50 ///< score for file extension
const val AVPROBE_SCORE_MIME       = 75 ///< score for file mime type
const val AVPROBE_SCORE_MAX       = 100 ///< maximum score

const val AVPROBE_SCORE_RETRY: Int = (AVPROBE_SCORE_MAX/4)
const val AVPROBE_SCORE_STREAM_RETRY = (AVPROBE_SCORE_MAX/4-1)

const val AVPROBE_PADDING_SIZE = 32             ///< extra allocated bytes at the end of the probe buffer

/// Demuxer will use avio_open, no opened file should be provided by the caller.
const val AVFMT_NOFILE        = 0x0001
const val AVFMT_NEEDNUMBER    = 0x0002 /**< Needs '%d' in filename. */
const val AVFMT_SHOW_IDS      = 0x0008 /**< Show format stream IDs numbers. */
const val AVFMT_GLOBALHEADER  = 0x0040 /**< Format wants global header. */
const val AVFMT_NOTIMESTAMPS  = 0x0080 /**< Format does not need / have any timestamps. */
const val AVFMT_GENERIC_INDEX = 0x0100 /**< Use generic index building code. */
const val AVFMT_TS_DISCONT    = 0x0200 /**< Format allows timestamp discontinuities. Note, muxers always require valid (monotone) timestamps */
const val AVFMT_VARIABLE_FPS  = 0x0400 /**< Format allows variable fps. */
const val AVFMT_NODIMENSIONS  = 0x0800 /**< Format does not need width/height */
const val AVFMT_NOSTREAMS     = 0x1000 /**< Format does not require any streams */
const val AVFMT_NOBINSEARCH   = 0x2000 /**< Format does not allow to fall back on binary search via read_timestamp */
const val AVFMT_NOGENSEARCH   = 0x4000 /**< Format does not allow to fall back on generic search */
const val AVFMT_NO_BYTE_SEEK  = 0x8000 /**< Format does not allow seeking by bytes */
const val AVFMT_ALLOW_FLUSH  = 0x10000 /**< Format allows flushing. If not set, the muxer will not receive a NULL packet in the write_packet function. */
const val AVFMT_TS_NONSTRICT = 0x20000 /**< Format does not require strictly
                                        increasing timestamps, but they must
                                        still be monotonic */

const val AVFMT_TS_NEGATIVE  = 0x40000 /**< Format allows muxing negative
                                        timestamps. If not set the timestamp
                                        will be shifted in av_write_frame and
                                        av_interleaved_write_frame so they
                                        start from 0.
                                        The user or muxer can override this through
                                        AVFormatContext.avoid_negative_ts
                                         */

const val AVFMT_SEEK_TO_PTS   = 0x4000000 /**< Seeking is based on PTS */


const val AV_DISPOSITION_DEFAULT   = 0x0001
const val AV_DISPOSITION_DUB       = 0x0002
const val AV_DISPOSITION_ORIGINAL  = 0x0004
const val AV_DISPOSITION_COMMENT   = 0x0008
const val AV_DISPOSITION_LYRICS    = 0x0010
const val AV_DISPOSITION_KARAOKE   = 0x0020

/**
 * Track should be used during playback by default.
 * Useful for subtitle track that should be displayed
 * even when user did not explicitly ask for subtitles.
 */
const val AV_DISPOSITION_FORCED    = 0x0040
const val AV_DISPOSITION_HEARING_IMPAIRED  = 0x0080  /**< stream for hearing impaired audiences */
const val AV_DISPOSITION_VISUAL_IMPAIRED   = 0x0100  /**< stream for visual impaired audiences */
const val AV_DISPOSITION_CLEAN_EFFECTS     = 0x0200  /**< stream without voice */
/**
 * The stream is stored in the file as an attached picture/"cover art" (e.g.
 * APIC frame in ID3v2). The first (usually only) packet associated with it
 * will be returned among the first few packets read from the file unless
 * seeking takes place. It can also be accessed at any time in
 * AVStream.attached_pic.
 */
const val AV_DISPOSITION_ATTACHED_PIC      = 0x0400
/**
 * The stream is sparse, and contains thumbnail images, often corresponding
 * to chapter markers. Only ever used with AV_DISPOSITION_ATTACHED_PIC.
 */
const val AV_DISPOSITION_TIMED_THUMBNAILS  = 0x0800

/**
 * To specify text track kind (different from subtitles default).
 */
const val AV_DISPOSITION_CAPTIONS     = 0x10000
const val AV_DISPOSITION_DESCRIPTIONS = 0x20000
const val AV_DISPOSITION_METADATA     = 0x40000
const val AV_DISPOSITION_DEPENDENT    = 0x80000 ///< dependent audio stream (mix_type=0 in mpegts)
const val AV_DISPOSITION_STILL_IMAGE = 0x100000 ///< still images in video stream (still_picture_flag=1 in mpegts)

/**
 * Options for behavior on timestamp wrap detection.
 */
const val AV_PTS_WRAP_IGNORE      = 0   ///< ignore the wrap
const val AV_PTS_WRAP_ADD_OFFSET  = 1   ///< add the format specific offset on wrap detection
const val AV_PTS_WRAP_SUB_OFFSET  = -1  ///< subtract the format specific offset on wrap detection


const val AVFMTCTX_NOHEADER      = 0x0001 /**< signal that no header is present
                                            (streams are added dynamically) */
const val AVFMTCTX_UNSEEKABLE    = 0x0002 /**< signal that the stream is definitely
                                            not seekable, and attempts to call the
                                            seek function will fail. For some
                                            network protocols (e.g. HLS), this can
                                            change dynamically at runtime. */

const val AVFMT_FLAG_GENPTS       = 0x0001 ///< Generate missing pts even if it requires parsing future frames.
const val AVFMT_FLAG_IGNIDX       = 0x0002 ///< Ignore index.
const val AVFMT_FLAG_NONBLOCK     = 0x0004 ///< Do not block when reading packets from input.
const val AVFMT_FLAG_IGNDTS       = 0x0008 ///< Ignore DTS on frames that contain both DTS & PTS
const val AVFMT_FLAG_NOFILLIN     = 0x0010 ///< Do not infer any values from other values, just return what is stored in the container
const val AVFMT_FLAG_NOPARSE      = 0x0020 ///< Do not use AVParsers, you also must set AVFMT_FLAG_NOFILLIN as the fillin code works on frames and no parsing -> no frames. Also seeking to frames can not work if parsing to find frame boundaries has been disabled
const val AVFMT_FLAG_NOBUFFER     = 0x0040 ///< Do not buffer frames when possible
const val AVFMT_FLAG_CUSTOM_IO    = 0x0080 ///< The caller has supplied a custom AVIOContext, don't avio_close() it.
const val AVFMT_FLAG_DISCARD_CORRUPT  = 0x0100 ///< Discard frames marked corrupted
const val AVFMT_FLAG_FLUSH_PACKETS    = 0x0200 ///< Flush the AVIOContext every packet.
/**
 * When muxing, try to avoid writing any random/volatile data to the output.
 * This includes any random IDs, real-time timestamps/dates, muxer version, etc.
 *
 * This flag is mainly intended for testing.
 */
const val AVFMT_FLAG_BITEXACT         = 0x0400
const val AVFMT_FLAG_MP4A_LATM    = 0x8000 ///< Deprecated, does nothing.
const val AVFMT_FLAG_SORT_DTS    = 0x10000 ///< try to interleave outputted packets by dts (using this flag can slow demuxing down)
const val AVFMT_FLAG_PRIV_OPT    = 0x20000 ///< Enable use of private options by delaying codec open (this could be made default once all code is converted)
const val AVFMT_FLAG_KEEP_SIDE_DATA = 0x40000 ///< Deprecated, does nothing.
const val AVFMT_FLAG_FAST_SEEK   = 0x80000 ///< Enable fast, but inaccurate seeks for some formats
const val AVFMT_FLAG_SHORTEST   = 0x100000 ///< Stop muxing when the shortest stream stops.
const val AVFMT_FLAG_AUTO_BSF   = 0x200000 ///< Add bitstream filters as requested by the muxer


const val AVSEEK_FLAG_BACKWARD = 1 ///< seek backward
const val AVSEEK_FLAG_BYTE     = 2 ///< seeking based on position in bytes
const val AVSEEK_FLAG_ANY      = 4 ///< seek to any frame, even non-keyframes
const val AVSEEK_FLAG_FRAME    = 8 ///< seeking based on frame number

/**
 * @addtogroup lavf_encoding
 * @{
 */

const val AVSTREAM_INIT_IN_WRITE_HEADER = 0 ///< stream parameters initialized in avformat_write_header
const val AVSTREAM_INIT_IN_INIT_OUTPUT  = 1 ///< stream parameters initialized in avformat_init_output

const val AV_FRAME_FILENAME_FLAGS_MULTIPLE = 1 ///< Allow multiple %d

/**
 * Allow decoders to produce frames with data planes that are not aligned
 * to CPU requirements (e.g. due to cropping).
 */
const val AV_CODEC_FLAG_UNALIGNED       = (1 shl  0)
/**
 * Use fixed qscale.
 */
const val AV_CODEC_FLAG_QSCALE          = (1 shl  1)
/**
 * 4 MV per MB allowed / advanced prediction for H.263.
 */
const val AV_CODEC_FLAG_4MV             = (1 shl  2)
/**
 * Output even those frames that might be corrupted.
 */
const val AV_CODEC_FLAG_OUTPUT_CORRUPT  = (1 shl  3)
/**
 * Use qpel MC.
 */
const val AV_CODEC_FLAG_QPEL            = (1 shl  4)
/**
 * Don't output frames whose parameters differ from first
 * decoded frame in stream.
 */
const val AV_CODEC_FLAG_DROPCHANGED     = (1 shl  5)
/**
 * Use internal 2pass ratecontrol in first pass mode.
 */
const val AV_CODEC_FLAG_PASS1           = (1 shl  9)
/**
 * Use internal 2pass ratecontrol in second pass mode.
 */
const val AV_CODEC_FLAG_PASS2           = (1 shl 10)
/**
 * loop filter.
 */
const val AV_CODEC_FLAG_LOOP_FILTER     = (1 shl 11)
/**
 * Only decode/encode grayscale.
 */
const val AV_CODEC_FLAG_GRAY            = (1 shl 13)
/**
 * error[?] variables will be set during encoding.
 */
const val AV_CODEC_FLAG_PSNR            = (1 shl 15)
/**
 * Input bitstream might be truncated at a random location
 * instead of only at frame boundaries.
 */
const val AV_CODEC_FLAG_TRUNCATED       = (1 shl 16)
/**
 * Use interlaced DCT.
 */
const val AV_CODEC_FLAG_INTERLACED_DCT  = (1 shl 18)
/**
 * Force low delay.
 */
const val AV_CODEC_FLAG_LOW_DELAY       = (1 shl 19)
/**
 * Place global headers in extradata instead of every keyframe.
 */
const val AV_CODEC_FLAG_GLOBAL_HEADER   = (1 shl 22)
/**
 * Use only bitexact stuff (except (I)DCT).
 */
const val AV_CODEC_FLAG_BITEXACT        = (1 shl 23)
/* Fx : Flag for H.263+ extra options */
/**
 * H.263 advanced intra coding / MPEG-4 AC prediction
 */
const val AV_CODEC_FLAG_AC_PRED         = (1 shl 24)
/**
 * interlaced motion estimation
 */
const val AV_CODEC_FLAG_INTERLACED_ME   = (1 shl 29)
const val AV_CODEC_FLAG_CLOSED_GOP      = (1 shl 31)

/**
 * Allow non spec compliant speedup tricks.
 */
const val AV_CODEC_FLAG2_FAST           = (1 shl  0)
/**
 * Skip bitstream encoding.
 */
const val AV_CODEC_FLAG2_NO_OUTPUT      = (1 shl  2)
/**
 * Place global headers at every keyframe instead of in extradata.
 */
const val AV_CODEC_FLAG2_LOCAL_HEADER   = (1 shl  3)

/**
 * timecode is in drop frame format. DEPRECATED!!!!
 */
const val AV_CODEC_FLAG2_DROP_FRAME_TIMECODE = (1 shl 13)

/**
 * Input bitstream might be truncated at a packet boundaries
 * instead of only at frame boundaries.
 */
const val AV_CODEC_FLAG2_CHUNKS         = (1 shl 15)
/**
 * Discard cropping information from SPS.
 */
const val AV_CODEC_FLAG2_IGNORE_CROP    = (1 shl 16)

/**
 * Show all frames before the first keyframe
 */
const val AV_CODEC_FLAG2_SHOW_ALL       = (1 shl 22)
/**
 * Export motion vectors through frame side data
 */
const val AV_CODEC_FLAG2_EXPORT_MVS     = (1 shl 28)
/**
 * Do not skip samples and export skip information as frame side data
 */
const val AV_CODEC_FLAG2_SKIP_MANUAL    = (1 shl 29)
/**
 * Do not reset ASS ReadOrder field on flush (subtitles decoding)
 */
const val AV_CODEC_FLAG2_RO_FLUSH_NOOP  = (1 shl 30)

/* Unsupported options :
 *              Syntax Arithmetic coding (SAC)
 *              Reference Picture Selection
 *              Independent Segment Decoding */
/* /Fx */
/* codec capabilities */

/**
 * Decoder can use draw_horiz_band callback.
 */
const val AV_CODEC_CAP_DRAW_HORIZ_BAND     = (1 shl  0)
/**
 * Codec uses get_buffer() for allocating buffers and supports custom allocators.
 * If not set, it might not use get_buffer() at all or use operations that
 * assume the buffer was allocated by avcodec_default_get_buffer.
 */
const val AV_CODEC_CAP_DR1                 = (1 shl  1)
const val AV_CODEC_CAP_TRUNCATED           = (1 shl  3)
/**
 * Encoder or decoder requires flushing with NULL input at the end in order to
 * give the complete and correct output.
 *
 * NOTE: If this flag is not set, the codec is guaranteed to never be fed with
 *       with NULL data. The user can still send NULL data to the public encode
 *       or decode function, but libavcodec will not pass it along to the codec
 *       unless this flag is set.
 *
 * Decoders:
 * The decoder has a non-zero delay and needs to be fed with avpkt->data=NULL,
 * avpkt->size=0 at the end to get the delayed data until the decoder no longer
 * returns frames.
 *
 * Encoders:
 * The encoder needs to be fed with NULL data at the end of encoding until the
 * encoder no longer returns data.
 *
 * NOTE: For encoders implementing the AVCodec.encode2() function, setting this
 *       flag also means that the encoder must set the pts and duration for
 *       each output packet. If this flag is not set, the pts and duration will
 *       be determined by libavcodec from the input frame.
 */
const val AV_CODEC_CAP_DELAY               = (1 shl  5)
/**
 * Codec can be fed a final frame with a smaller size.
 * This can be used to prevent truncation of the last audio samples.
 */
const val AV_CODEC_CAP_SMALL_LAST_FRAME    = (1 shl  6)

/**
 * Codec can output multiple frames per AVPacket
 * Normally demuxers return one frame at a time, demuxers which do not do
 * are connected to a parser to split what they return into proper frames.
 * This flag is reserved to the very rare category of codecs which have a
 * bitstream that cannot be split into frames without timeconsuming
 * operations like full decoding. Demuxers carrying such bitstreams thus
 * may return multiple frames in a packet. This has many disadvantages like
 * prohibiting stream copy in many cases thus it should only be considered
 * as a last resort.
 */
const val AV_CODEC_CAP_SUBFRAMES           = (1 shl  8)
/**
 * Codec is experimental and is thus avoided in favor of non experimental
 * encoders
 */
const val AV_CODEC_CAP_EXPERIMENTAL        = (1 shl  9)
/**
 * Codec should fill in channel configuration and samplerate instead of container
 */
const val AV_CODEC_CAP_CHANNEL_CONF        = (1 shl 10)
/**
 * Codec supports frame-level multithreading.
 */
const val AV_CODEC_CAP_FRAME_THREADS       = (1 shl 12)
/**
 * Codec supports slice-based (or partition-based) multithreading.
 */
const val AV_CODEC_CAP_SLICE_THREADS       = (1 shl 13)
/**
 * Codec supports changed parameters at any point.
 */
const val AV_CODEC_CAP_PARAM_CHANGE        = (1 shl 14)
/**
 * Codec supports avctx->thread_count == 0 (auto).
 */
const val AV_CODEC_CAP_AUTO_THREADS        = (1 shl 15)
/**
 * Audio encoder supports receiving a different number of samples in each call.
 */
const val AV_CODEC_CAP_VARIABLE_FRAME_SIZE = (1 shl 16)
/**
 * Decoder is not a preferred choice for probing.
 * This indicates that the decoder is not a good choice for probing.
 * It could for example be an expensive to spin up hardware decoder,
 * or it could simply not provide a lot of useful information about
 * the stream.
 * A decoder marked with this flag should only be used as last resort
 * choice for probing.
 */
const val AV_CODEC_CAP_AVOID_PROBING       = (1 shl 17)
/**
 * Codec is intra only.
 */
const val AV_CODEC_CAP_INTRA_ONLY       = 0x40000000
/**
 * Codec is lossless.
 */
const val AV_CODEC_CAP_LOSSLESS         = 0x80000000

/**
 * Codec is backed by a hardware implementation. Typically used to
 * identify a non-hwaccel hardware decoder. For information about hwaccels, use
 * avcodec_get_hw_config() instead.
 */
const val AV_CODEC_CAP_HARDWARE            = (1 shl 18)

/**
 * Codec is potentially backed by a hardware implementation, but not
 * necessarily. This is used instead of AV_CODEC_CAP_HARDWARE, if the
 * implementation provides some sort of internal fallback.
 */
const val AV_CODEC_CAP_HYBRID              = (1 shl 19)

/**
 * This codec takes the reordered_opaque field from input AVFrames
 * and returns it in the corresponding field in AVCodecContext after
 * encoding.
 */
const val AV_CODEC_CAP_ENCODER_REORDERED_OPAQUE = (1 shl 20)

const val FF_CMP_SAD          = 0
const val FF_CMP_SSE          = 1
const val FF_CMP_SATD         = 2
const val FF_CMP_DCT          = 3
const val FF_CMP_PSNR         = 4
const val FF_CMP_BIT          = 5
const val FF_CMP_RD           = 6
const val FF_CMP_ZERO         = 7
const val FF_CMP_VSAD         = 8
const val FF_CMP_VSSE         = 9
const val FF_CMP_NSSE         = 10
const val FF_CMP_W53          = 11
const val FF_CMP_W97          = 12
const val FF_CMP_DCTMAX       = 13
const val FF_CMP_DCT264       = 14
const val FF_CMP_MEDIAN_SAD   = 15
const val FF_CMP_CHROMA       = 256

const val SLICE_FLAG_CODED_ORDER    = 0x0001 ///< draw_horiz_band() is called in coded order instead of display
const val SLICE_FLAG_ALLOW_FIELD    = 0x0002 ///< allow draw_horiz_band() with field slices (MPEG-2 field pics)
const val SLICE_FLAG_ALLOW_PLANE    = 0x0004 ///< allow draw_horiz_band() with 1 component at a time (SVQ1)

const val FF_MB_DECISION_SIMPLE = 0        ///< uses mb_cmp
const val FF_MB_DECISION_BITS   = 1        ///< chooses the one which needs the fewest bits
const val FF_MB_DECISION_RD     = 2        ///< rate distortion

const val FF_BUG_AUTODETECT       = 1  ///< autodetection
const val FF_BUG_XVID_ILACE       = 4
const val FF_BUG_UMP4             = 8
const val FF_BUG_NO_PADDING       = 16
const val FF_BUG_AMV              = 32
const val FF_BUG_QPEL_CHROMA      = 64
const val FF_BUG_STD_QPEL         = 128
const val FF_BUG_QPEL_CHROMA2     = 256
const val FF_BUG_DIRECT_BLOCKSIZE = 512
const val FF_BUG_EDGE             = 1024
const val FF_BUG_HPEL_CHROMA      = 2048
const val FF_BUG_DC_CLIP          = 4096
const val FF_BUG_MS               = 8192 ///< Work around various bugs in Microsoft's broken decoders.
const val FF_BUG_TRUNCATED       = 16384
const val FF_BUG_IEDGE           = 32768

const val FF_COMPLIANCE_VERY_STRICT   = 2 ///< Strictly conform to an older more strict version of the spec or reference software.
const val FF_COMPLIANCE_STRICT        = 1 ///< Strictly conform to all the things in the spec no matter what consequences.
const val FF_COMPLIANCE_NORMAL        = 0
const val FF_COMPLIANCE_UNOFFICIAL   = -1 ///< Allow unofficial extensions
const val FF_COMPLIANCE_EXPERIMENTAL = -2 ///< Allow nonstandardized experimental things.

const val FF_EC_GUESS_MVS   = 1
const val FF_EC_DEBLOCK     = 2
const val FF_EC_FAVOR_INTER = 256

const val FF_DEBUG_PICT_INFO   = 1
const val FF_DEBUG_RC          = 2
const val FF_DEBUG_BITSTREAM   = 4
const val FF_DEBUG_MB_TYPE     = 8
const val FF_DEBUG_QP          = 16

/**
 * @deprecated this option does nothing
 */
const val FF_DEBUG_MV          = 32

const val FF_DEBUG_DCT_COEFF   = 0x00000040
const val FF_DEBUG_SKIP        = 0x00000080
const val FF_DEBUG_STARTCODE   = 0x00000100
const val FF_DEBUG_ER          = 0x00000400
const val FF_DEBUG_MMCO        = 0x00000800
const val FF_DEBUG_BUGS        = 0x00001000

const val FF_DEBUG_VIS_QP      = 0x00002000
const val FF_DEBUG_VIS_MB_TYPE = 0x00004000

const val FF_DEBUG_BUFFERS     = 0x00008000
const val FF_DEBUG_THREADS     = 0x00010000
const val FF_DEBUG_GREEN_MD    = 0x00800000
const val FF_DEBUG_NOMC        = 0x01000000

const val AV_EF_CRCCHECK  = (1 shl 0)
const val AV_EF_BITSTREAM = (1 shl 1)          ///< detect bitstream specification deviations
const val AV_EF_BUFFER    = (1 shl 2)          ///< detect improper bitstream length
const val AV_EF_EXPLODE   = (1 shl 3)          ///< abort decoding on minor error detection

const val AV_EF_IGNORE_ERR = (1 shl 15)        ///< ignore errors and continue
const val AV_EF_CAREFUL    = (1 shl 16)        ///< consider things that violate the spec, are fast to calculate and have not been seen in the wild as errors
const val AV_EF_COMPLIANT  = (1 shl 17)        ///< consider all spec non compliances as errors
const val AV_EF_AGGRESSIVE = (1 shl 18)        ///< consider things that a sane encoder should not do as an error

const val FF_DCT_AUTO    = 0
const val FF_DCT_FASTINT = 1
const val FF_DCT_INT     = 2
const val FF_DCT_MMX     = 3
const val FF_DCT_ALTIVEC = 5
const val FF_DCT_FAAN    = 6

const val FF_IDCT_AUTO          = 0
const val FF_IDCT_INT           = 1
const val FF_IDCT_SIMPLE        = 2
const val FF_IDCT_SIMPLEMMX     = 3
const val FF_IDCT_ARM           = 7
const val FF_IDCT_ALTIVEC       = 8
const val FF_IDCT_SIMPLEARM     = 10
const val FF_IDCT_XVID          = 14
const val FF_IDCT_SIMPLEARMV5TE = 16
const val FF_IDCT_SIMPLEARMV6   = 17
const val FF_IDCT_FAAN          = 20
const val FF_IDCT_SIMPLENEON    = 22
const val FF_IDCT_NONE          = 24 /* Used by XvMC to extract IDCT coefficients with FF_IDCT_PERM_NONE */
const val FF_IDCT_SIMPLEAUTO    = 128

const val FF_THREAD_FRAME   = 1 ///< Decode more than one frame at once
const val FF_THREAD_SLICE   = 2 ///< Decode more than one part of a single frame at once

const val FF_PROFILE_UNKNOWN = -99
const val FF_PROFILE_RESERVED = -100

const val FF_PROFILE_AAC_MAIN = 0
const val FF_PROFILE_AAC_LOW  = 1
const val FF_PROFILE_AAC_SSR  = 2
const val FF_PROFILE_AAC_LTP  = 3
const val FF_PROFILE_AAC_HE   = 4
const val FF_PROFILE_AAC_HE_V2 = 28
const val FF_PROFILE_AAC_LD   = 22
const val FF_PROFILE_AAC_ELD  = 38
const val FF_PROFILE_MPEG2_AAC_LOW = 128
const val FF_PROFILE_MPEG2_AAC_HE  = 131

const val FF_PROFILE_DNXHD         = 0
const val FF_PROFILE_DNXHR_LB      = 1
const val FF_PROFILE_DNXHR_SQ      = 2
const val FF_PROFILE_DNXHR_HQ      = 3
const val FF_PROFILE_DNXHR_HQX     = 4
const val FF_PROFILE_DNXHR_444     = 5

const val FF_PROFILE_DTS         = 20
const val FF_PROFILE_DTS_ES      = 30
const val FF_PROFILE_DTS_96_24   = 40
const val FF_PROFILE_DTS_HD_HRA  = 50
const val FF_PROFILE_DTS_HD_MA   = 60
const val FF_PROFILE_DTS_EXPRESS = 70

const val FF_PROFILE_MPEG2_422    = 0
const val FF_PROFILE_MPEG2_HIGH   = 1
const val FF_PROFILE_MPEG2_SS     = 2
const val FF_PROFILE_MPEG2_SNR_SCALABLE  = 3
const val FF_PROFILE_MPEG2_MAIN   = 4
const val FF_PROFILE_MPEG2_SIMPLE = 5

const val FF_PROFILE_H264_CONSTRAINED  = (1 shl 9)  // 8+1; constraint_set1_flag
const val FF_PROFILE_H264_INTRA        = (1 shl 11) // 8+3; constraint_set3_flag

const val FF_PROFILE_H264_BASELINE             = 66
const val FF_PROFILE_H264_CONSTRAINED_BASELINE = (66 or FF_PROFILE_H264_CONSTRAINED)
const val FF_PROFILE_H264_MAIN                 = 77
const val FF_PROFILE_H264_EXTENDED             = 88
const val FF_PROFILE_H264_HIGH                 = 100
const val FF_PROFILE_H264_HIGH_10              = 110
const val FF_PROFILE_H264_HIGH_10_INTRA        = (110 or FF_PROFILE_H264_INTRA)
const val FF_PROFILE_H264_MULTIVIEW_HIGH       = 118
const val FF_PROFILE_H264_HIGH_422             = 122
const val FF_PROFILE_H264_HIGH_422_INTRA       = (122 or FF_PROFILE_H264_INTRA)
const val FF_PROFILE_H264_STEREO_HIGH          = 128
const val FF_PROFILE_H264_HIGH_444             = 144
const val FF_PROFILE_H264_HIGH_444_PREDICTIVE  = 244
const val FF_PROFILE_H264_HIGH_444_INTRA       = (244 or FF_PROFILE_H264_INTRA)
const val FF_PROFILE_H264_CAVLC_444            = 44

const val FF_PROFILE_VC1_SIMPLE   = 0
const val FF_PROFILE_VC1_MAIN     = 1
const val FF_PROFILE_VC1_COMPLEX  = 2
const val FF_PROFILE_VC1_ADVANCED = 3

const val FF_PROFILE_MPEG4_SIMPLE                     = 0
const val FF_PROFILE_MPEG4_SIMPLE_SCALABLE            = 1
const val FF_PROFILE_MPEG4_CORE                       = 2
const val FF_PROFILE_MPEG4_MAIN                       = 3
const val FF_PROFILE_MPEG4_N_BIT                      = 4
const val FF_PROFILE_MPEG4_SCALABLE_TEXTURE           = 5
const val FF_PROFILE_MPEG4_SIMPLE_FACE_ANIMATION      = 6
const val FF_PROFILE_MPEG4_BASIC_ANIMATED_TEXTURE     = 7
const val FF_PROFILE_MPEG4_HYBRID                     = 8
const val FF_PROFILE_MPEG4_ADVANCED_REAL_TIME         = 9
const val FF_PROFILE_MPEG4_CORE_SCALABLE             = 10
const val FF_PROFILE_MPEG4_ADVANCED_CODING           = 11
const val FF_PROFILE_MPEG4_ADVANCED_CORE             = 12
const val FF_PROFILE_MPEG4_ADVANCED_SCALABLE_TEXTURE = 13
const val FF_PROFILE_MPEG4_SIMPLE_STUDIO             = 14
const val FF_PROFILE_MPEG4_ADVANCED_SIMPLE           = 15

const val FF_PROFILE_JPEG2000_CSTREAM_RESTRICTION_0   = 1
const val FF_PROFILE_JPEG2000_CSTREAM_RESTRICTION_1   = 2
const val FF_PROFILE_JPEG2000_CSTREAM_NO_RESTRICTION  = 32768
const val FF_PROFILE_JPEG2000_DCINEMA_2K              = 3
const val FF_PROFILE_JPEG2000_DCINEMA_4K              = 4

const val FF_PROFILE_VP9_0                            = 0
const val FF_PROFILE_VP9_1                            = 1
const val FF_PROFILE_VP9_2                            = 2
const val FF_PROFILE_VP9_3                            = 3

const val FF_PROFILE_HEVC_MAIN                        = 1
const val FF_PROFILE_HEVC_MAIN_10                     = 2
const val FF_PROFILE_HEVC_MAIN_STILL_PICTURE          = 3
const val FF_PROFILE_HEVC_REXT                        = 4

const val FF_PROFILE_AV1_MAIN                         = 0
const val FF_PROFILE_AV1_HIGH                         = 1
const val FF_PROFILE_AV1_PROFESSIONAL                 = 2

const val FF_PROFILE_MJPEG_HUFFMAN_BASELINE_DCT            = 0xc0
const val FF_PROFILE_MJPEG_HUFFMAN_EXTENDED_SEQUENTIAL_DCT = 0xc1
const val FF_PROFILE_MJPEG_HUFFMAN_PROGRESSIVE_DCT         = 0xc2
const val FF_PROFILE_MJPEG_HUFFMAN_LOSSLESS                = 0xc3
const val FF_PROFILE_MJPEG_JPEG_LS                         = 0xf7

const val FF_PROFILE_SBC_MSBC                         = 1

const val FF_PROFILE_PRORES_PROXY     = 0
const val FF_PROFILE_PRORES_LT        = 1
const val FF_PROFILE_PRORES_STANDARD  = 2
const val FF_PROFILE_PRORES_HQ        = 3
const val FF_PROFILE_PRORES_4444      = 4
const val FF_PROFILE_PRORES_XQ        = 5

const val FF_PROFILE_ARIB_PROFILE_A = 0
const val FF_PROFILE_ARIB_PROFILE_C = 1

const val FF_LEVEL_UNKNOWN = -99

/**
 * Hardware acceleration should be used for decoding even if the codec level
 * used is unknown or higher than the maximum supported level reported by the
 * hardware driver.
 *
 * It's generally a good idea to pass this flag unless you have a specific
 * reason not to, as hardware tends to under-report supported levels.
 */
const val AV_HWACCEL_FLAG_IGNORE_LEVEL = (1 shl 0)

/**
 * Hardware acceleration can output YUV pixel formats with a different chroma
 * sampling than 4:2:0 and/or other than 8 bits per component.
 */
const val AV_HWACCEL_FLAG_ALLOW_HIGH_DEPTH = (1 shl 1)

/**
 * Hardware acceleration should still be attempted for decoding when the
 * codec profile does not match the reported capabilities of the hardware.
 *
 * For example, this can be used to try to decode baseline profile H.264
 * streams in hardware - it will often succeed, because many streams marked
 * as baseline profile actually conform to constrained baseline profile.
 *
 * @warning If the stream is actually not supported then the behaviour is
 *          undefined, and may include returning entirely incorrect output
 *          while indicating success.
 */
const val AV_HWACCEL_FLAG_ALLOW_PROFILE_MISMATCH = (1 shl 2)


const val FF_FDEBUG_TS = 0x0001

const val AVFMT_EVENT_FLAG_METADATA_UPDATED = 0x0001

const val AVFMT_AVOID_NEG_TS_AUTO             = -1 ///< Enabled when required by target format
const val AVFMT_AVOID_NEG_TS_MAKE_NON_NEGATIVE = 1 ///< Shift timestamps so they are non negative
const val AVFMT_AVOID_NEG_TS_MAKE_ZERO         = 2 ///< Shift timestamps so that they start at 0


const val AV_ROUND_ZERO       = 0 ///< Round toward zero.
const val AV_ROUND_INF        = 1 ///< Round away from zero.
const val AV_ROUND_DOWN       = 2 ///< Round toward -infinity.
const val AV_ROUND_UP     = 3 ///< Round toward +infinity.
const val AV_ROUND_NEAR_INF       = 5 ///< Round to nearest and halfway cases away from zero.
/**
 * Flag telling rescaling functions to pass `INT64_MIN`/`MAX` through
 * unchanged, avoiding special cases for #AV_NOPTS_VALUE.
 *
 * Unlike other values of the enumeration AVRounding, this value is a
 * bitmask that must be used in conjunction with another value of the
 * enumeration through a bitwise OR, in order to set behavior for normal
 * cases.
 *
 * @code{.c}
 * av_rescale_rnd(3, 1, 2, const val AV_ROUND_UP      = |const val AV_ROUND_PASS_MINMAX      = ; * // Rescaling 3:
 * //     Calculating 3 * 1 / 2
 * //     3 / 2 is rounded up to 2
 * //     => 2
 *
 * av_rescale_rnd(AV_NOPTS_VALUE, 1, 2, const val AV_ROUND_UP     = |const val AV_ROUND_PASS_MINMAX      = ; * // Rescaling AV_NOPTS_VALUE:
 * //     AV_NOPTS_VALUE == INT64_MIN
 * //     AV_NOPTS_VALUE is passed through
 * //     => AV_NOPTS_VALUE
 * @endcode
 */
const val AV_ROUND_PASS_MINMAX        = 8192


/**
 * Codec uses only intra compression.
 * Video and audio codecs only.
 */
const val AV_CODEC_PROP_INTRA_ONLY    = (1 shl 0)
/**
 * Codec supports lossy compression. Audio and video codecs only.
 * @note a codec may support both lossy and lossless
 * compression modes
 */
const val AV_CODEC_PROP_LOSSY         = (1 shl 1)
/**
 * Codec supports lossless compression. Audio and video codecs only.
 */
const val AV_CODEC_PROP_LOSSLESS      = (1 shl 2)
/**
 * Codec supports frame reordering. That is, the coded order (the order in which
 * the encoded packets are output by the encoders / stored / input to the
 * decoders) may be different from the presentation order of the corresponding
 * frames.
 *
 * For codecs that do not have this property set, PTS and DTS should always be
 * equal.
 */
const val AV_CODEC_PROP_REORDER       = (1 shl 3)
/**
 * Subtitle codec is bitmap based
 * Decoded AVSubtitle data can be read from the AVSubtitleRect->pict field.
 */
const val AV_CODEC_PROP_BITMAP_SUB    = (1 shl 16)
/**
 * Subtitle codec is text based.
 * Decoded AVSubtitle data can be read from the AVSubtitleRect->ass field.
 */
const val AV_CODEC_PROP_TEXT_SUB      = (1 shl 17)

/**
 * @ingroup lavc_decoding
 * Required number of additionally allocated bytes at the end of the input bitstream for decoding.
 * This is mainly needed because some optimized bitstream readers read
 * 32 or 64 bit at once and could read over the end.<br>
 * Note: If the first 23 bits of the additional bytes are not 0, then damaged
 * MPEG bitstreams could cause overread and segfault.
 */
const val AV_INPUT_BUFFER_PADDING_SIZE = 64

/**
 * @ingroup lavc_encoding
 * minimum encoding buffer size
 * Used to avoid some checks during header writing.
 */
const val AV_INPUT_BUFFER_MIN_SIZE = 16384

const val AV_PARSER_PTS_NB = 4

const val PARSER_FLAG_COMPLETE_FRAMES           = 0x0001
const val PARSER_FLAG_ONCE                      = 0x0002
/// Set if the parser has a valid file offset
const val PARSER_FLAG_FETCHED_OFFSET            = 0x0004
const val PARSER_FLAG_USE_CODEC_TS              = 0x1000


const val FF_LAMBDA_SHIFT = 7
const val FF_LAMBDA_SCALE = (1 shl FF_LAMBDA_SHIFT)
const val FF_QP2LAMBDA = 118 ///< factor to convert from H.263 QP to lambda
const val FF_LAMBDA_MAX = (256*128-1)

const val FF_QUALITY_SCALE = FF_LAMBDA_SCALE //FIXME maybe remove

/**
 * @}
 * @defgroup lavu_time Timestamp specific
 *
 * FFmpeg internal timebase and timestamp definitions
 *
 * @{
 */

/**
 * @brief Undefined timestamp value
 *
 * Usually reported by demuxer that work on containers that do not provide
 * either pts or dts.
 */

const val AV_NOPTS_VALUE: Long = (0x80000000 shl 32)

/**
 * Internal time base represented as integer
 */

const val AV_TIME_BASE            = 1000000

/**
 * Seeking works like for a local file.
 */
const val AVIO_SEEKABLE_NORMAL = (1 shl 0)

/**
 * Seeking by timestamp with avio_seek_time() is possible.
 */
const val AVIO_SEEKABLE_TIME   = (1 shl 1)

/**
 * @name URL open modes
 * The flags argument to avio_open must be one of the following
 * constants, optionally ORed with other flags.
 * @{
 */
const val AVIO_FLAG_READ  = 1                                      /**< read-only */
const val AVIO_FLAG_WRITE = 2                                      /**< write-only */
const val AVIO_FLAG_READ_WRITE = (AVIO_FLAG_READ or AVIO_FLAG_WRITE)  /**< read-write pseudo flag */
/**
 * @}
 */

/**
 * Use non-blocking mode.
 * If this flag is set, operations on the context will return
 * AVERROR(EAGAIN) if they can not be performed immediately.
 * If this flag is not set, operations on the context will never return
 * AVERROR(EAGAIN).
 * Note that this flag does not affect the opening/connecting of the
 * context. Connecting a protocol will always block if necessary (e.g. on
 * network protocols) but never hang (e.g. on busy devices).
 * Warning: non-blocking protocols is work-in-progress; this flag may be
 * silently ignored.
 */
const val AVIO_FLAG_NONBLOCK = 8

/**
 * Use direct mode.
 * avio_read and avio_write should if possible be satisfied directly
 * instead of going through a buffer, and avio_seek will always
 * call the underlying seek function directly.
 */
const val AVIO_FLAG_DIRECT = 0x8000

/* values for the flags, the stuff on the command line is different */
const val SWS_FAST_BILINEAR     = 1
const val SWS_BILINEAR          = 2
const val SWS_BICUBIC           = 4
const val SWS_X                 = 8
const val SWS_POINT          = 0x10
const val SWS_AREA           = 0x20
const val SWS_BICUBLIN       = 0x40
const val SWS_GAUSS          = 0x80
const val SWS_SINC          = 0x100
const val SWS_LANCZOS       = 0x200
const val SWS_SPLINE        = 0x400

const val SWS_SRC_V_CHR_DROP_MASK     = 0x30000
const val SWS_SRC_V_CHR_DROP_SHIFT    = 16

const val SWS_PARAM_DEFAULT           = 123456

const val SWS_PRINT_INFO              = 0x1000

//the following 3 flags are not completely implemented
//internal chrominance subsampling info
const val SWS_FULL_CHR_H_INT    = 0x2000
//input subsampling info
const val SWS_FULL_CHR_H_INP    = 0x4000
const val SWS_DIRECT_BGR        = 0x8000
const val SWS_ACCURATE_RND      = 0x40000
const val SWS_BITEXACT          = 0x80000
const val SWS_ERROR_DIFFUSION  = 0x800000

const val SWS_MAX_REDUCE_CUTOFF = 0.002

const val SWS_CS_ITU709         = 1
const val SWS_CS_FCC            = 4
const val SWS_CS_ITU601         = 5
const val SWS_CS_ITU624         = 5
const val SWS_CS_SMPTE170M      = 5
const val SWS_CS_SMPTE240M      = 7
const val SWS_CS_DEFAULT        = 5
const val SWS_CS_BT2020         = 9
