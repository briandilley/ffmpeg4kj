package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class SampleFormat(override val nativeEnumValue: Int)
    : NativeEnum {

    AV_SAMPLE_FMT_NONE(-1), // = -1,
    AV_SAMPLE_FMT_U8(0),          ///< unsigned 8 bits
    AV_SAMPLE_FMT_S16(1),         ///< signed 16 bits
    AV_SAMPLE_FMT_S32(2),         ///< signed 32 bits
    AV_SAMPLE_FMT_FLT(3),         ///< float
    AV_SAMPLE_FMT_DBL(4),         ///< double

    AV_SAMPLE_FMT_U8P(5),         ///< unsigned 8 bits, planar
    AV_SAMPLE_FMT_S16P(6),        ///< signed 16 bits, planar
    AV_SAMPLE_FMT_S32P(7),        ///< signed 32 bits, planar
    AV_SAMPLE_FMT_FLTP(8),        ///< float, planar
    AV_SAMPLE_FMT_DBLP(9),        ///< double, planar
    AV_SAMPLE_FMT_S64(10),         ///< signed 64 bits
    AV_SAMPLE_FMT_S64P(11),        ///< signed 64 bits, planar

    AV_SAMPLE_FMT_NB(12)           ///< Number of sample formats. DO NOT USE if linking dynamically
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
