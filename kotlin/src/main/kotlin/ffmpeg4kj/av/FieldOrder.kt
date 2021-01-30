package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class FieldOrder(override val nativeEnumValue: Int)
    : NativeEnum {

    AV_FIELD_UNKNOWN(0),
    AV_FIELD_PROGRESSIVE(1),
    AV_FIELD_TT(2),          //< Top coded_first, top displayed first
    AV_FIELD_BB(3),          //< Bottom coded first, bottom displayed first
    AV_FIELD_TB(4),          //< Top coded first, bottom displayed first
    AV_FIELD_BT(5),          //< Bottom coded first, top displayed first
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
