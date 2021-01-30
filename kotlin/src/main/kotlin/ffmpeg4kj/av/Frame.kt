package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

class Frame(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    constructor() : this(new())

    companion object {

        @JvmStatic
        private external fun new(): Long
    }

    /**
     * av_frame_get_buffer
     */
    external fun allocateBuffers(align: Int = 0)

    /**
     * av_frame_ref
     */
    external fun ref(dest: Frame? = null): Frame

    /**
     * av_frame_unref
     */
    external fun unref()

    /**
     * av_frame_free
     */
    external fun free()

    external fun setBuffer(index: Int, buffer: Buffer?, lineSize: Int)
    external fun getBuffer(index: Int): Buffer?

    external fun setData(index: Int, byteBuffer: ByteBuffer?, lineSize: Int)
    external fun getData(index: Int): ByteBuffer?

    external fun getLineSize(index: Int): Int

    private external fun format(format: Int)
    private external fun format(): Int
    var format: Int
        get() = format()
        set(value) { format(value) }

    var pixelFormat: PixelFormat
        get() = PixelFormat.forNativeEnumValue(this.format)
        set(value) { format(value.nativeEnumValue) }

    var sampleFormat: SampleFormat
        get() = SampleFormat.forNativeEnumValue(this.format)
        set(value) { format(value.nativeEnumValue) }

    private external fun pts(): Long
    private external fun pts(pts: Long)
    var pts: Long
        get() = pts()
        set(value) = pts(value)
    private external fun packetDts(): Long
    private external fun packetDts(packetDts: Long)
    var packetDts: Long
        get() = packetDts()
        set(value) = packetDts(value)
    private external fun packetDuration(): Long
    private external fun packetDuration(packetDuration: Long)
    var packetDuration: Long
        get() = packetDuration()
        set(value) = packetDuration(value)

    private external fun ptsSeconds(): Seconds
    val ptsSeconds: Seconds get() = ptsSeconds()
    private external fun packetDtsSeconds(): Seconds
    val packetDtsSeconds: Seconds get() = packetDtsSeconds()
    private external fun packetDurationSeconds(): Seconds
    val packetDurationSeconds: Seconds get() = packetDurationSeconds()

    private external fun ptsMillis(): Milliseconds
    val ptsMillis: Milliseconds get() = ptsMillis()
    private external fun packetDtsMillis(): Milliseconds
    val packetDtsMillis: Milliseconds get() = packetDtsMillis()
    private external fun packetDurationMillis(): Milliseconds
    val packetDurationMillis: Milliseconds get() = packetDurationMillis()

    private external fun flags(flags: Int)
    private external fun flags(): Int
    var flags: Int
        get() = flags()
        set(value) { flags(value) }

    private external fun packetPos(packetPos: Long)
    private external fun packetPos(): Long
    var packetPos: Long
        get() = packetPos()
        set(value) { packetPos(value) }

    private external fun packetSize(packetSize: Int)
    private external fun packetSize(): Int
    var packetSize: Int
        get() = packetSize()
        set(value) { packetSize(value) }

    // video

    private external fun width(width: Int)
    private external fun width(): Int
    var width: Int
        get() = width()
        set(value) { width(value) }

    private external fun height(height: Int)
    private external fun height(): Int
    var height: Int
        get() = height()
        set(value) { height(value) }

    private external fun keyFrame(keyFrame: Boolean)
    private external fun keyFrame(): Boolean
    var keyFrame: Boolean
        get() = keyFrame()
        set(value) { keyFrame(value) }

    private external fun pictureType(pictureType: Int)
    private external fun pictureType(): Int
    var pictureType: Int
        get() = pictureType()
        set(value) { pictureType(value) }

    private external fun quality(quality: Int)
    private external fun quality(): Int
    var quality: Int
        get() = quality()
        set(value) { quality(value) }

    private external fun cropTop(cropTop: Int)
    private external fun cropTop(): Int
    var cropTop: Int
        get() = cropTop()
        set(value) { cropTop(value) }

    private external fun cropLeft(cropLeft: Int)
    private external fun cropLeft(): Int
    var cropLeft: Int
        get() = cropLeft()
        set(value) { cropLeft(value) }

    private external fun cropRight(cropRight: Int)
    private external fun cropRight(): Int
    var cropRight: Int
        get() = cropRight()
        set(value) { cropRight(value) }

    private external fun cropBottom(cropBottom: Int)
    private external fun cropBottom(): Int
    var cropBottom: Int
        get() = cropBottom()
        set(value) { cropBottom(value) }

    // audio

    private external fun numberOfSamples(numberOfSamples: Int)
    private external fun numberOfSamples(): Int
    var numberOfSamples: Int
        get() = numberOfSamples()
        set(value) { numberOfSamples(value) }

    private external fun sampleRate(sampleRate: Int)
    private external fun sampleRate(): Int
    var sampleRate: Int
        get() = sampleRate()
        set(value) { sampleRate(value) }

    private external fun channelLayout(channelLayout: Long)
    private external fun channelLayout(): Long
    var channelLayout: Long
        get() = channelLayout()
        set(value) { channelLayout(value) }

    private external fun numberOfChannels(numberOfChannels: Int)
    private external fun numberOfChannels(): Int
    var numberOfChannels: Int
        get() = numberOfChannels()
        set(value) { numberOfChannels(value) }

}
