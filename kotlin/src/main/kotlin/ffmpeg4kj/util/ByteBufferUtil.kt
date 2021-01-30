package ffmpeg4kj.util

import java.nio.ByteBuffer

fun requireDirect(buffer: ByteBuffer): ByteBuffer {
    require(buffer.isDirect) { "ByteBuffer must be direct" }
    return buffer
}
