package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class BufferPool(size: Int) : AbstractNativeObject(new(size)) {

    companion object {

        @JvmStatic
        private external fun new(size: Int): Long
    }

    external fun getBuffer(): Buffer

    external fun unInit()

    override fun close() {
        unInit()
        super.close()
    }
}
