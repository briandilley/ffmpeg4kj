package ffmpeg4kj.av

import ffmpeg4kj.util.NativeEnum

enum class PictureStructure(override val nativeEnumValue: Int)
    : NativeEnum {

    AV_PICTURE_STRUCTURE_UNKNOWN(0),      //< unknown
    AV_PICTURE_STRUCTURE_TOP_FIELD(1),    //< coded as top field
    AV_PICTURE_STRUCTURE_BOTTOM_FIELD(2), //< coded as bottom field
    AV_PICTURE_STRUCTURE_FRAME(3),        //< coded as frame
    ;

    companion object {
        @JvmStatic
        fun forNativeEnumValue(nativeEnumValue: Int) =
            ffmpeg4kj.util.forNativeEnumValue(values(), nativeEnumValue)
    }
}
