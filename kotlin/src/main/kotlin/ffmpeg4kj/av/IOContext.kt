package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

@FunctionalInterface
interface ReadFunction {
    fun read(dest: ByteBuffer): Int
}

@FunctionalInterface
interface WriteFunction {
    fun write(src: ByteBuffer): Int
}

@FunctionalInterface
interface SeekFunction {
    fun seek(offset: Long, whence: Int): Long
}

class IOContext private constructor(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    companion object {

        @JvmStatic
        external fun createIOContext(
            bufferSize: Int,
            read: ReadFunction? = null,
            write: WriteFunction? = null,
            seek: SeekFunction? = null): IOContext
    }

    private external fun _close()

    override fun close() {
        this._close()
        super.close()
    }
}
