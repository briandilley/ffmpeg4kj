package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

class CodecParameters(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    constructor() : this(new())

    companion object {

        @JvmStatic
        private external fun new(): Long
    }

    external fun copyFrom(other: CodecParameters)

    private external fun codecType(): MediaType
    private external fun codecType(codecType: MediaType)
    var codecType: MediaType
        get() = codecType()
        set(value) { codecType(value) }

    private external fun codecId(): CodecID
    private external fun codecId(codecId: CodecID)
    var codecId: CodecID
        get() = codecId()
        set(value) { codecId(value) }

    private external fun codecTag(): Long
    private external fun codecTag(codecTag: Long)
    var codecTag: Long
        get() = codecTag()
        set(value) { codecTag(value) }

    private external fun pixelFormat(): PixelFormat
    private external fun pixelFormat(codecTag: PixelFormat)
    var pixelFormat: PixelFormat
        get() = pixelFormat()
        set(value) { pixelFormat(value) }

    private external fun sampleFormat(): SampleFormat
    private external fun sampleFormat(codecTag: SampleFormat)
    var sampleFormat: SampleFormat
        get() = sampleFormat()
        set(value) { sampleFormat(value) }

    private external fun bitRate(): Long
    private external fun bitRate(bitRate: Long)
    var bitRate: Long
        get() = bitRate()
        set(value) { bitRate(value) }

    private external fun bitsPerCodedSample(): Int
    private external fun bitsPerCodedSample(bitsPerCodedSample: Int)
    var bitsPerCodedSample: Int
        get() = bitsPerCodedSample()
        set(value) { bitsPerCodedSample(value) }

    private external fun bitsPerRawSample(): Int
    private external fun bitsPerRawSample(bitsPerRawSample: Int)
    var bitsPerRawSample: Int
        get() = bitsPerRawSample()
        set(value) { bitsPerRawSample(value) }

    private external fun profile(): Int
    private external fun profile(profile: Int)
    var profile: Int
        get() = profile()
        set(value) { profile(value) }

    private external fun level(): Int
    private external fun level(level: Int)
    var level: Int
        get() = level()
        set(value) { level(value) }

    private external fun width(): Int
    private external fun width(width: Int)
    var width: Int
        get() = width()
        set(value) { width(value) }

    private external fun height(): Int
    private external fun height(height: Int)
    var height: Int
        get() = height()
        set(value) { height(value) }

    private external fun sampleAspectRatio(): Rational
    var sampleAspectRatio: Rational get() = sampleAspectRatio()
        set(value) {
            sampleAspectRatio.den = value.den
            sampleAspectRatio.num = value.num
        }

    private external fun fieldOrder(): FieldOrder
    private external fun fieldOrder(fieldOrder: FieldOrder)
    var fieldOrder: FieldOrder
        get() = fieldOrder()
        set(value) { fieldOrder(value) }

    private external fun colorRange(): ColorRange
    private external fun colorRange(colorRange: ColorRange)
    var colorRange: ColorRange
        get() = colorRange()
        set(value) { colorRange(value) }

    private external fun colorPrimaries(): ColorPrimaries
    private external fun colorPrimaries(colorPrimaries: ColorPrimaries)
    var colorPrimaries: ColorPrimaries
        get() = colorPrimaries()
        set(value) { colorPrimaries(value) }

    private external fun colorTransferCharacteristic(): ColorTransferCharacteristic
    private external fun colorTransferCharacteristic(colorTransferCharacteristic: ColorTransferCharacteristic)
    var colorTransferCharacteristic: ColorTransferCharacteristic
        get() = colorTransferCharacteristic()
        set(value) { colorTransferCharacteristic(value) }

    private external fun colorSpace(): ColorSpace
    private external fun colorSpace(colorSpace: ColorSpace)
    var colorSpace: ColorSpace
        get() = colorSpace()
        set(value) { colorSpace(value) }

    private external fun chromaLocation(): ChromaLocation
    private external fun chromaLocation(chromaLocation: ChromaLocation)
    var chromaLocation: ChromaLocation
        get() = chromaLocation()
        set(value) { chromaLocation(value) }

    private external fun videoDelay(): Int
    private external fun videoDelay(videoDelay: Int)
    var videoDelay: Int
        get() = videoDelay()
        set(value) { videoDelay(value) }

    private external fun channelLayout(): Long
    private external fun channelLayout(channelLayout: Long)
    var channelLayout: Long
        get() = channelLayout()
        set(value) { channelLayout(value) }

    private external fun channels(): Int
    private external fun channels(channels: Int)
    var channels: Int
        get() = channels()
        set(value) { channels(value) }

    private external fun sampleRate(): Int
    private external fun sampleRate(sampleRate: Int)
    var sampleRate: Int
        get() = sampleRate()
        set(value) { sampleRate(value) }

    private external fun blockAlign(): Int
    private external fun blockAlign(blockAlign: Int)
    var blockAlign: Int
        get() = blockAlign()
        set(value) { blockAlign(value) }

    private external fun initialPadding(): Int
    private external fun initialPadding(initialPadding: Int)
    var initialPadding: Int
        get() = initialPadding()
        set(value) { initialPadding(value) }

    private external fun trailingPadding(): Int
    private external fun trailingPadding(trailingPadding: Int)
    var trailingPadding: Int
        get() = trailingPadding()
        set(value) { trailingPadding(value) }

    private external fun seekPreRoll(): Int
    private external fun seekPreRoll(seekPreRoll: Int)
    var seekPreRoll: Int
        get() = seekPreRoll()
        set(value) { seekPreRoll(value) }

}
