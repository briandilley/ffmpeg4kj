package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class ImageConverter(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    companion object {

        /**
         * sws_getContext
         */
        @JvmStatic
        external fun createImageConverter(
            srcW: Int, srcH: Int, srcFormat: PixelFormat,
            dstW: Int, dstH: Int, dstFormat: PixelFormat,
            flags: Int): ImageConverter

    }

    /**
     * sws_scale
     */
    external fun convert(src: Frame, dst: Frame, srcSlice: Int = 0, srcSliceHeight: Int = src.height): Int

    /**
     * sws_freeContext
     */
    external fun free()
}

