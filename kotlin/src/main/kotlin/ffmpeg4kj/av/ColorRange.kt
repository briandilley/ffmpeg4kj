package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class ColorRange(override val nativeEnumValue: Int)
    : NativeEnum {

    AVCOL_RANGE_UNSPECIFIED(0),
    AVCOL_RANGE_MPEG(1), ///< the normal 219*2^(n-8) "MPEG" YUV ranges
    AVCOL_RANGE_JPEG(2), ///< the normal     2^n-1   "JPEG" YUV ranges
    AVCOL_RANGE_NB(3)               ///< Not part of ABI
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
