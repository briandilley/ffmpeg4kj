package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class Stream private constructor(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    external fun getEncoderCodec(): Codec
    external fun getDecoderCodec(): Codec

    external fun createEncoder(): Encoder
    external fun createDecoder(): Decoder

    private external fun id(): Int
    val id: Int get() = id()

    private external fun index(): Int
    val index: Int get() = index()

    private external fun codecParameters(): CodecParameters
    val codecParameters: CodecParameters get() = codecParameters()

    private external fun timeBase(): Rational
    var timeBase: Rational get() = timeBase()
        set(value) {
            timeBase.den = value.den
            timeBase.num = value.num
        }

    private external fun numberOfFrames(): Int
    private external fun numberOfFrames(numberOfFrames: Int)
    var numberOfFrames: Int
        get() = numberOfFrames()
        set(value) = numberOfFrames(value)

    private external fun disposition(): Int
    private external fun disposition(disposition: Int)
    var disposition: Int
        get() = disposition()
        set(value) = disposition(value)

    private external fun discard(): Discard
    private external fun discard(discard: Discard)
    var discard: Discard
        get() = discard()
        set(value) = discard(value)

    private external fun sampleAspectRatio(): Rational
    var sampleAspectRatio: Rational get() = sampleAspectRatio()
        set(value) {
            sampleAspectRatio.den = value.den
            sampleAspectRatio.num = value.num
        }

    private external fun averageFrameRate(): Rational
    var averageFrameRate: Rational get() = averageFrameRate()
        set(value) {
            averageFrameRate.den = value.den
            averageFrameRate.num = value.num
        }

    private external fun realFrameRate(): Rational
    var realFrameRate: Rational get() = realFrameRate()
        set(value) {
            realFrameRate.den = value.den
            realFrameRate.num = value.num
        }

    private external fun startTime(): Long
    private external fun startTime(startTime: Long)
    var startTime: Long
        get() = startTime()
        set(value) = startTime(value)

    private external fun startTimeSeconds(): Seconds
    val startTimeSeconds: Seconds get() = startTimeSeconds()
    private external fun startTimeMillis(): Milliseconds
    val startTimeMillis: Milliseconds get() = startTimeMillis()

    private external fun duration(): Long
    private external fun duration(duration: Long)
    var duration: Long
        get() = duration()
        set(value) = duration(value)

    private external fun durationSeconds(): Seconds
    val durationSeconds: Seconds get() = durationSeconds()
    private external fun durationMillis(): Milliseconds
    val durationMillis: Milliseconds get() = durationMillis()

}
