package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject

abstract class FormatContext(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    private external fun streamCount(): Int
    val streamCount: Int get() = streamCount()

    external fun getStream(index: Int): Stream?

    /**
     *  av_dump_format
     */
    external fun dump(isOutput: Boolean);

    private external fun ctxFlags(): Int
    private external fun ctxFlags(ctxFlags: Int)
    var ctxFlags: Int
        get() = ctxFlags()
        set(value) { ctxFlags(value) }

    private external fun url(): String
    private external fun url(url: String)
    var url: String
        get() = url()
        set(value) { url(value) }

    private external fun startTime(): Long
    val startTime: Long
        get() = startTime()

    private external fun duration(): Long
    private external fun duration(duration: Long)
    var duration: Long
        get() = duration()
        set(value) { duration(value) }

    private external fun bitRate(): Long
    private external fun bitRate(bitRate: Long)
    var bitRate: Long
        get() = bitRate()
        set(value) { bitRate(value) }

    private external fun maxDelay(): Int
    private external fun maxDelay(maxDelay: Int)
    var maxDelay: Int
        get() = maxDelay()
        set(value) { maxDelay(value) }

    private external fun flags(): Int
    private external fun flags(flags: Int)
    var flags: Int
        get() = flags()
        set(value) { flags(value) }

    private external fun probeSize(): Long
    private external fun probeSize(probeSize: Long)
    var probeSize: Long
        get() = probeSize()
        set(value) { probeSize(value) }

    private external fun maxAnalyzeDuration(): Long
    private external fun maxAnalyzeDuration(maxAnalyzeDuration: Long)
    var maxAnalyzeDuration: Long
        get() = maxAnalyzeDuration()
        set(value) { maxAnalyzeDuration(value) }

    private external fun videoCodecId(): CodecID
    private external fun videoCodecId(videoCodecId: CodecID)
    var videoCodecId: CodecID
        get() = videoCodecId()
        set(value) { videoCodecId(value) }

    private external fun audioCodecId(): CodecID
    private external fun audioCodecId(audioCodecId: CodecID)
    var audioCodecId: CodecID
        get() = audioCodecId()
        set(value) { audioCodecId(value) }

    private external fun subtitleCodecId(): CodecID
    private external fun subtitleCodecId(subtitleCodecId: CodecID)
    var subtitleCodecId: CodecID
        get() = subtitleCodecId()
        set(value) { subtitleCodecId(value) }

    private external fun maxIndexSize(): Int
    private external fun maxIndexSize(maxIndexSize: Int)
    var maxIndexSize: Int
        get() = maxIndexSize()
        set(value) { maxIndexSize(value) }

    private external fun maxPictureBuffer(): Int
    private external fun maxPictureBuffer(maxPictureBuffer: Int)
    var maxPictureBuffer: Int
        get() = maxPictureBuffer()
        set(value) { maxPictureBuffer(value) }

    private external fun startTimeRealtime(): Long
    private external fun startTimeRealtime(startTimeRealtime: Long)
    var startTimeRealtime: Long
        get() = startTimeRealtime()
        set(value) { startTimeRealtime(value) }

    private external fun fpsProbeSize(): Int
    private external fun fpsProbeSize(fpsProbeSize: Int)
    var fpsProbeSize: Int
        get() = fpsProbeSize()
        set(value) { fpsProbeSize(value) }

    private external fun errorRecognition(): Int
    private external fun errorRecognition(errorRecognition: Int)
    var errorRecognition: Int
        get() = errorRecognition()
        set(value) { errorRecognition(value) }

    private external fun debug(): Int
    private external fun debug(debug: Int)
    var debug: Int
        get() = debug()
        set(value) { debug(value) }

    private external fun maxInterleaveDelta(): Long
    private external fun maxInterleaveDelta(maxInterleaveDelta: Long)
    var maxInterleaveDelta: Long
        get() = maxInterleaveDelta()
        set(value) { maxInterleaveDelta(value) }

    private external fun strictStdCompliance(): Int
    private external fun strictStdCompliance(strictStdCompliance: Int)
    var strictStdCompliance: Int
        get() = strictStdCompliance()
        set(value) { strictStdCompliance(value) }

    private external fun eventFlags(): Int
    private external fun eventFlags(eventFlags: Int)
    var eventFlags: Int
        get() = eventFlags()
        set(value) { eventFlags(value) }

    private external fun maxTsProbe(): Int
    private external fun maxTsProbe(maxTsProbe: Int)
    var maxTsProbe: Int
        get() = maxTsProbe()
        set(value) { maxTsProbe(value) }

    private external fun avoidNegativeTs(): Int
    private external fun avoidNegativeTs(avoidNegativeTs: Int)
    var avoidNegativeTs: Int
        get() = avoidNegativeTs()
        set(value) { avoidNegativeTs(value) }

    private external fun audioPreload(): Int
    private external fun audioPreload(audioPreload: Int)
    var audioPreload: Int
        get() = audioPreload()
        set(value) { audioPreload(value) }

    private external fun maxChunkDuration(): Int
    private external fun maxChunkDuration(maxChunkDuration: Int)
    var maxChunkDuration: Int
        get() = maxChunkDuration()
        set(value) { maxChunkDuration(value) }

    private external fun maxChunkSize(): Int
    private external fun maxChunkSize(maxChunkSize: Int)
    var maxChunkSize: Int
        get() = maxChunkSize()
        set(value) { maxChunkSize(value) }

    private external fun useWallClockAsTimestamps(): Int
    private external fun useWallClockAsTimestamps(useWallClockAsTimestamps: Int)
    var useWallClockAsTimestamps: Int
        get() = useWallClockAsTimestamps()
        set(value) { useWallClockAsTimestamps(value) }

    private external fun avioFlags(): Int
    private external fun avioFlags(avioFlags: Int)
    var avioFlags: Int
        get() = avioFlags()
        set(value) { avioFlags(value) }

    private external fun skipInitialBytes(): Int
    private external fun skipInitialBytes(skipInitialBytes: Int)
    var skipInitialBytes: Int
        get() = skipInitialBytes()
        set(value) { skipInitialBytes(value) }

    private external fun correctTsOverflow(): Int
    private external fun correctTsOverflow(correctTsOverflow: Int)
    var correctTsOverflow: Int
        get() = correctTsOverflow()
        set(value) { correctTsOverflow(value) }

    private external fun seek2any(): Int
    private external fun seek2any(seek2any: Int)
    var seek2any: Int
        get() = seek2any()
        set(value) { seek2any(value) }

    private external fun flushPackets(): Int
    private external fun flushPackets(flushPackets: Int)
    var flushPackets: Int
        get() = flushPackets()
        set(value) { flushPackets(value) }

    private external fun propbeScore(): Int
    private external fun propbeScore(propbeScore: Int)
    var propbeScore: Int
        get() = propbeScore()
        set(value) { propbeScore(value) }

    private external fun formatProbeSize(): Int
    private external fun formatProbeSize(formatProbeSize: Int)
    var formatProbeSize: Int
        get() = formatProbeSize()
        set(value) { formatProbeSize(value) }

    private external fun videoCodec(): Codec
    private external fun videoCodec(videoCodec: Codec)
    var videoCodec: Codec
        get() = videoCodec()
        set(value) { videoCodec(value) }

    private external fun audioCodec(): Codec
    private external fun audioCodec(audioCodec: Codec)
    var audioCodec: Codec
        get() = audioCodec()
        set(value) { audioCodec(value) }

    private external fun subtitleCodec(): Codec
    private external fun subtitleCodec(subtitleCodec: Codec)
    var subtitleCodec: Codec
        get() = subtitleCodec()
        set(value) { subtitleCodec(value) }

    private external fun dataCodec(): Codec
    private external fun dataCodec(dataCodec: Codec)
    var dataCodec: Codec
        get() = dataCodec()
        set(value) { dataCodec(value) }

    private external fun metadataHeaderPadding(): Int
    private external fun metadataHeaderPadding(metadataHeaderPadding: Int)
    var metadataHeaderPadding: Int
        get() = metadataHeaderPadding()
        set(value) { metadataHeaderPadding(value) }

    private external fun outputTsOffset(): Long
    private external fun outputTsOffset(outputTsOffset: Long)
    var outputTsOffset: Long
        get() = outputTsOffset()
        set(value) { outputTsOffset(value) }

    private external fun dataCodecId(): CodecID
    private external fun dataCodecId(dataCodecId: CodecID)
    var dataCodecId: CodecID
        get() = dataCodecId()
        set(value) { dataCodecId(value) }

    private external fun maxStreams(): Int
    private external fun maxStreams(maxStreams: Int)
    var maxStreams: Int
        get() = maxStreams()
        set(value) { maxStreams(value) }

    private external fun skipEstimateDurationFromPts(): Int
    private external fun skipEstimateDurationFromPts(skipEstimateDurationFromPts: Int)
    var skipEstimateDurationFromPts: Int
        get() = skipEstimateDurationFromPts()
        set(value) { skipEstimateDurationFromPts(value) }
}
