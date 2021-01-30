package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

class Buffer
    : AbstractNativeObject {

    internal constructor(nativeStatePtr: Long) : super(nativeStatePtr)

    constructor(size: Int) : super(new(size))

    companion object {

        @JvmStatic
        private external fun new(size: Int): Long
    }


    private external fun buffer(): ByteBuffer
    val buffer: ByteBuffer get() = buffer()

    private external fun size(): Int
    val size: Int get() = size()

    private external fun writable(): Boolean
    val writable: Boolean get() = writable()

    external fun makeWritable()
    external fun ref(): Buffer
    external fun unref()

    private external fun refCount(): Int
    val refCount: Int get() = refCount()

}
