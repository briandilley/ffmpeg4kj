package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

class Packet
    : AbstractNativeObject {

    internal constructor(nativeStatePtr: Long) : super(nativeStatePtr)

    constructor() : this(newEmpty())

    constructor(byteBuffer: ByteBuffer) : this() {
        this.data = byteBuffer
    }

    constructor(buffer: Buffer) : this() {
        this.buffer = buffer
    }

    companion object {

        @JvmStatic
        private external fun newEmpty(): Long
    }

    /**
     * av_packet_rescale_ts
     */
    external fun rescaleTs(tbSrc: Rational, tbDst: Rational)

    /**
     * av_new_packet
     */
    external fun allocateBuffer(size: Int)

    /**
     * av_shrink_packet
     */
    external fun shrinkBuffer(size: Int)

    /**
     * av_grow_packet
     */
    external fun growBuffer(growBy: Int)

    /**
     * av_packet_ref
     */
    external fun ref(dest: Packet? = null): Packet

    /**
     * av_packet_unref
     */
    external fun unref()

    /**
     * av_init_packet
     */
    external fun init()

    private external fun buffer(buffer: Buffer?)
    private external fun buffer(): Buffer?
    var buffer: Buffer?
        get() = buffer()
        set(value) { buffer(value) }

    private external fun pts(pts: Long)
    private external fun pts(): Long
    var pts: Long
        get() = pts()
        set(value) { pts(value) }
    private external fun dts(dts: Long)
    private external fun dts(): Long
    var dts: Long
        get() = dts()
        set(value) { dts(value) }
    private external fun duration(duration: Long)
    private external fun duration(): Long
    var duration: Long
        get() = duration()
        set(value) { duration(value) }

    private external fun ptsSeconds(): Seconds
    val ptsSeconds: Seconds get() = ptsSeconds()
    private external fun dtsSeconds(): Seconds
    val dtsSeconds: Seconds get() = dtsSeconds()
    private external fun durationSeconds(): Seconds
    val durationSeconds: Seconds get() = durationSeconds()

    private external fun ptsMillis(): Milliseconds
    val ptsMillis: Milliseconds get() = ptsMillis()
    private external fun dtsMillis(): Milliseconds
    val dtsMillis: Milliseconds get() = dtsMillis()
    private external fun durationMillis(): Milliseconds
    val durationMillis: Milliseconds get() = durationMillis()

    private external fun data(data: ByteBuffer?)
    private external fun data(): ByteBuffer?
    var data: ByteBuffer?
        get() = data()
        set(value) { data(value) }

    private external fun dataSize(): Int
    val dataSize: Int get() = dataSize()

    private external fun streamIndex(streamIndex: Int)
    private external fun streamIndex(): Int
    var streamIndex: Int
        get() = streamIndex()
        set(value) { streamIndex(value) }

    private external fun flags(flags: Int)
    private external fun flags(): Int
    var flags: Int
        get() = flags()
        set(value) { flags(value) }

    private external fun pos(pos: Long)
    private external fun pos(): Long
    var pos: Long
        get() = pos()
        set(value) { pos(value) }

}
