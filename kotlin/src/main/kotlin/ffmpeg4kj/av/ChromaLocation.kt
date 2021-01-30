package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class ChromaLocation(override val nativeEnumValue: Int)
    : NativeEnum {
    AVCHROMA_LOC_UNSPECIFIED(0),
    AVCHROMA_LOC_LEFT(1), ///< MPEG-2/4 4:2:0, H.264 default for 4:2:0
    AVCHROMA_LOC_CENTER(2), ///< MPEG-1 4:2:0, JPEG 4:2:0, H.263 4:2:0
    AVCHROMA_LOC_TOPLEFT(3), ///< ITU-R 601, SMPTE 274M 296M S314M(DV 4:1:1), mpeg2 4:2:2
    AVCHROMA_LOC_TOP(4),
    AVCHROMA_LOC_BOTTOMLEFT(5),
    AVCHROMA_LOC_BOTTOM(6),
    AVCHROMA_LOC_NB(7)               ///< Not part of ABI
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
