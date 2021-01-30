package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

abstract class CodecContext(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    private external fun codec(): Codec
    val codec: Codec get() = codec()

    private external fun isOpen(): Boolean
    val open: Boolean get() = isOpen()

    /**
     * avcodec_parameters_to_context
     */
    external fun setParameters(params: CodecParameters)

    /**
     * avcodec_parameters_from_context
     */
    external fun getParameters(params: CodecParameters)

    /**
     * avcodec_open2
     */
    external fun open(openOptions: String? = null)

    /**
     * avcodec_free_context
     */
    external fun free()

    override fun close() {
        free()
        super.close()
    }

    external fun allocateExtraData(size: Int)
    external fun deallocateExtraData();

    private external fun extradata(): ByteBuffer
    private external fun extradata(extradata: ByteBuffer)
    var extradata: ByteBuffer
        get() = extradata()
        set(value) { extradata(value) }

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

    private external fun codecTag(): Int
    private external fun codecTag(codecTag: Int)
    var codecTag: Int
        get() = codecTag()
        set(value) { codecTag(value) }

    private external fun bitRate(): Long
    private external fun bitRate(bitRate: Long)
    var bitRate: Long
        get() = bitRate()
        set(value) { bitRate(value) }

    private external fun bitRateTolerance(): Int
    private external fun bitRateTolerance(bitRateTolerance: Int)
    var bitRateTolerance: Int
        get() = bitRateTolerance()
        set(value) { bitRateTolerance(value) }

    private external fun globalQuality(): Int
    private external fun globalQuality(globalQuality: Int)
    var globalQuality: Int
        get() = globalQuality()
        set(value) { globalQuality(value) }

    private external fun compressionLevel(): Int
    private external fun compressionLevel(compressionLevel: Int)
    var compressionLevel: Int
        get() = compressionLevel()
        set(value) { compressionLevel(value) }

    private external fun flags(): Int
    private external fun flags(flags: Int)
    var flags: Int
        get() = flags()
        set(value) { flags(value) }

    private external fun flags2(): Int
    private external fun flags2(flags2: Int)
    var flags2: Int
        get() = flags2()
        set(value) { flags2(value) }

    private external fun timeBase(): Rational
    var timeBase: Rational get() = timeBase()
        set(value) {
            timeBase.num = value.num
            timeBase.den = value.den
        }

    private external fun ticksPerFrame(): Int
    private external fun ticksPerFrame(ticksPerFrame: Int)
    var ticksPerFrame: Int
        get() = ticksPerFrame()
        set(value) { ticksPerFrame(value) }

    private external fun delay(): Int
    private external fun delay(delay: Int)
    var delay: Int
        get() = delay()
        set(value) { delay(value) }

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

    private external fun codedWidth(): Int
    private external fun codedWidth(codedWidth: Int)
    var codedWidth: Int
        get() = codedWidth()
        set(value) { codedWidth(value) }

    private external fun codedHeight(): Int
    private external fun codedHeight(codedHeight: Int)
    var codedHeight: Int
        get() = codedHeight()
        set(value) { codedHeight(value) }

    private external fun gopSize(): Int
    private external fun gopSize(gopSize: Int)
    var gopSize: Int
        get() = gopSize()
        set(value) { gopSize(value) }

    private external fun pixelFormat(): PixelFormat
    private external fun pixelFormat(pixelFormat: PixelFormat)
    var pixelFormat: PixelFormat
        get() = pixelFormat()
        set(value) { pixelFormat(value) }

    private external fun maxBFrames(): Int
    private external fun maxBFrames(maxBFrames: Int)
    var maxBFrames: Int
        get() = maxBFrames()
        set(value) { maxBFrames(value) }

    private external fun bQuantFactor(): Float
    private external fun bQuantFactor(bQuantFactor: Float)
    var bQuantFactor: Float
        get() = bQuantFactor()
        set(value) { bQuantFactor(value) }

    private external fun bQuantOffset(): Float
    private external fun bQuantOffset(bQuantOffset: Float)
    var bQuantOffset: Float
        get() = bQuantOffset()
        set(value) { bQuantOffset(value) }

    private external fun iQuantFactor(): Float
    private external fun iQuantFactor(iQuantFactor: Float)
    var iQuantFactor: Float
        get() = iQuantFactor()
        set(value) { iQuantFactor(value) }

    private external fun iQuantOffset(): Float
    private external fun iQuantOffset(iQuantOffset: Float)
    var iQuantOffset: Float
        get() = iQuantOffset()
        set(value) { iQuantOffset(value) }

    private external fun lumiMasking(): Float
    private external fun lumiMasking(lumiMasking: Float)
    var lumiMasking: Float
        get() = lumiMasking()
        set(value) { lumiMasking(value) }

    private external fun temporalCplxMasking(): Float
    private external fun temporalCplxMasking(temporalCplxMasking: Float)
    var temporalCplxMasking: Float
        get() = temporalCplxMasking()
        set(value) { temporalCplxMasking(value) }

    private external fun spacialCplxMasking(): Float
    private external fun spacialCplxMasking(spacialCplxMasking: Float)
    var spacialCplxMasking: Float
        get() = spacialCplxMasking()
        set(value) { spacialCplxMasking(value) }

    private external fun pMasking(): Float
    private external fun pMasking(pMasking: Float)
    var pMasking: Float
        get() = pMasking()
        set(value) { pMasking(value) }

    private external fun darkMasking(): Float
    private external fun darkMasking(darkMasking: Float)
    var darkMasking: Float
        get() = darkMasking()
        set(value) { darkMasking(value) }

    private external fun sliceCount(): Int
    private external fun sliceCount(sliceCount: Int)
    var sliceCount: Int
        get() = sliceCount()
        set(value) { sliceCount(value) }

    private external fun sampleAspectRatio(): Rational
    var sampleAspectRatio: Rational get() = sampleAspectRatio()
        set(value) {
            sampleAspectRatio.num = value.num
            sampleAspectRatio.den = value.den
        }

    private external fun meCmp(): Int
    private external fun meCmp(meCmp: Int)
    var meCmp: Int
        get() = meCmp()
        set(value) { meCmp(value) }

    private external fun meSubCmp(): Int
    private external fun meSubCmp(meSubCmp: Int)
    var meSubCmp: Int
        get() = meSubCmp()
        set(value) { meSubCmp(value) }

    private external fun mbCmp(): Int
    private external fun mbCmp(mbCmp: Int)
    var mbCmp: Int
        get() = mbCmp()
        set(value) { mbCmp(value) }

    private external fun ildctCmp(): Int
    private external fun ildctCmp(ildctCmp: Int)
    var ildctCmp: Int
        get() = ildctCmp()
        set(value) { ildctCmp(value) }

    private external fun diaSize(): Int
    private external fun diaSize(diaSize: Int)
    var diaSize: Int
        get() = diaSize()
        set(value) { diaSize(value) }

    private external fun lastPredictorCount(): Int
    private external fun lastPredictorCount(lastPredictorCount: Int)
    var lastPredictorCount: Int
        get() = lastPredictorCount()
        set(value) { lastPredictorCount(value) }

    private external fun mePreCmp(): Int
    private external fun mePreCmp(mePreCmp: Int)
    var mePreCmp: Int
        get() = mePreCmp()
        set(value) { mePreCmp(value) }

    private external fun preDiaSize(): Int
    private external fun preDiaSize(preDiaSize: Int)
    var preDiaSize: Int
        get() = preDiaSize()
        set(value) { preDiaSize(value) }

    private external fun meSubpelQuality(): Int
    private external fun meSubpelQuality(meSubpelQuality: Int)
    var meSubpelQuality: Int
        get() = meSubpelQuality()
        set(value) { meSubpelQuality(value) }

    private external fun meRange(): Int
    private external fun meRange(meRange: Int)
    var meRange: Int
        get() = meRange()
        set(value) { meRange(value) }

    private external fun sliceFlags(): Int
    private external fun sliceFlags(sliceFlags: Int)
    var sliceFlags: Int
        get() = sliceFlags()
        set(value) { sliceFlags(value) }

    private external fun mbDecision(): Int
    private external fun mbDecision(mbDecision: Int)
    var mbDecision: Int
        get() = mbDecision()
        set(value) { mbDecision(value) }

    private external fun intraDcPrecision(): Int
    private external fun intraDcPrecision(intraDcPrecision: Int)
    var intraDcPrecision: Int
        get() = intraDcPrecision()
        set(value) { intraDcPrecision(value) }

    private external fun skipTop(): Int
    private external fun skipTop(skipTop: Int)
    var skipTop: Int
        get() = skipTop()
        set(value) { skipTop(value) }

    private external fun skipBottom(): Int
    private external fun skipBottom(skipBottom: Int)
    var skipBottom: Int
        get() = skipBottom()
        set(value) { skipBottom(value) }

    private external fun mbLmin(): Int
    private external fun mbLmin(mbLmin: Int)
    var mbLmin: Int
        get() = mbLmin()
        set(value) { mbLmin(value) }

    private external fun mbLmax(): Int
    private external fun mbLmax(mbLmax: Int)
    var mbLmax: Int
        get() = mbLmax()
        set(value) { mbLmax(value) }

    private external fun bidirRefine(): Int
    private external fun bidirRefine(bidirRefine: Int)
    var bidirRefine: Int
        get() = bidirRefine()
        set(value) { bidirRefine(value) }

    private external fun keyintMin(): Int
    private external fun keyintMin(keyintMin: Int)
    var keyintMin: Int
        get() = keyintMin()
        set(value) { keyintMin(value) }

    private external fun refs(): Int
    private external fun refs(refs: Int)
    var refs: Int
        get() = refs()
        set(value) { refs(value) }

    private external fun mv0Threshoold(): Int
    private external fun mv0Threshoold(mv0Threshoold: Int)
    var mv0Threshoold: Int
        get() = mv0Threshoold()
        set(value) { mv0Threshoold(value) }

    private external fun colorPrimaries(): ColorPrimaries
    private external fun colorPrimaries(colorPrimaries: ColorPrimaries)
    var colorPrimaries: ColorPrimaries
        get() = colorPrimaries()
        set(value) { colorPrimaries(value) }

    private external fun colorTrc(): ColorTransferCharacteristic
    private external fun colorTrc(colorTrc: ColorTransferCharacteristic)
    var colorTrc: ColorTransferCharacteristic
        get() = colorTrc()
        set(value) { colorTrc(value) }

    private external fun colorSpace(): ColorSpace
    private external fun colorSpace(colorSpace: ColorSpace)
    var colorSpace: ColorSpace
        get() = colorSpace()
        set(value) { colorSpace(value) }

    private external fun colorRange(): ColorRange
    private external fun colorRange(colorRange: ColorRange)
    var colorRange: ColorRange
        get() = colorRange()
        set(value) { colorRange(value) }

    private external fun chromaSampleLocation(): ChromaLocation
    private external fun chromaSampleLocation(chromaSampleLocation: ChromaLocation)
    var chromaSampleLocation: ChromaLocation
        get() = chromaSampleLocation()
        set(value) { chromaSampleLocation(value) }

    private external fun slices(): Int
    private external fun slices(slices: Int)
    var slices: Int
        get() = slices()
        set(value) { slices(value) }

    private external fun fieldOrder(): FieldOrder
    private external fun fieldOrder(fieldOrder: FieldOrder)
    var fieldOrder: FieldOrder
        get() = fieldOrder()
        set(value) { fieldOrder(value) }

    private external fun sampleRate(): Int
    private external fun sampleRate(sampleRate: Int)
    var sampleRate: Int
        get() = sampleRate()
        set(value) { sampleRate(value) }

    private external fun channels(): Int
    private external fun channels(channels: Int)
    var channels: Int
        get() = channels()
        set(value) { channels(value) }

    private external fun sampleFmt(): SampleFormat
    private external fun sampleFmt(sampleFmt: SampleFormat)
    var sampleFmt: SampleFormat
        get() = sampleFmt()
        set(value) { sampleFmt(value) }

    private external fun frameSize(): Int
    val frameSize: Int
        get() = frameSize()

    private external fun frameNumber(): Int
    val frameNumber: Int
        get() = frameNumber()

    private external fun cutoff(): Int
    private external fun cutoff(cutoff: Int)
    var cutoff: Int
        get() = cutoff()
        set(value) { cutoff(value) }

    private external fun blockAlign(): Int
    private external fun blockAlign(blockAlign: Int)
    var blockAlign: Int
        get() = blockAlign()
        set(value) { blockAlign(value) }

    private external fun channelLayout(): Long
    private external fun channelLayout(channelLayout: Long)
    var channelLayout: Long
        get() = channelLayout()
        set(value) { channelLayout(value) }

    private external fun requestChannelLayout(): Long
    private external fun requestChannelLayout(requestChannelLayout: Long)
    var requestChannelLayout: Long
        get() = requestChannelLayout()
        set(value) { requestChannelLayout(value) }

    private external fun requestSampleFormat(): SampleFormat
    private external fun requestSampleFormat(requestSampleFormat: SampleFormat)
    var requestSampleFormat: SampleFormat
        get() = requestSampleFormat()
        set(value) { requestSampleFormat(value) }

    // TODO: get_buffer2

    private external fun qCompress(): Float
    private external fun qCompress(qCompress: Float)
    var qCompress: Float
        get() = qCompress()
        set(value) { qCompress(value) }

    private external fun qBlur(): Float
    private external fun qBlur(qBlur: Float)
    var qBlur: Float
        get() = qBlur()
        set(value) { qBlur(value) }

    private external fun qMin(): Int
    private external fun qMin(qMin: Int)
    var qMin: Int
        get() = qMin()
        set(value) { qMin(value) }

    private external fun qMax(): Int
    private external fun qMax(qMax: Int)
    var qMax: Int
        get() = qMax()
        set(value) { qMax(value) }

    private external fun maxQDiff(): Int
    private external fun maxQDiff(maxQDiff: Int)
    var maxQDiff: Int
        get() = maxQDiff()
        set(value) { maxQDiff(value) }

    private external fun rcBufferSize(): Int
    private external fun rcBufferSize(rcBufferSize: Int)
    var rcBufferSize: Int
        get() = rcBufferSize()
        set(value) { rcBufferSize(value) }

    private external fun rcMaxRate(): Int
    private external fun rcMaxRate(rcMaxRate: Int)
    var rcMaxRate: Int
        get() = rcMaxRate()
        set(value) { rcMaxRate(value) }

    private external fun rcMinRate(): Int
    private external fun rcMinRate(rcMinRate: Int)
    var rcMinRate: Int
        get() = rcMinRate()
        set(value) { rcMinRate(value) }

    private external fun rcMaxAvailableVbvUse(): Float
    private external fun rcMaxAvailableVbvUse(rcMaxAvailableVbvUse: Float)
    var rcMaxAvailableVbvUse: Float
        get() = rcMaxAvailableVbvUse()
        set(value) { rcMaxAvailableVbvUse(value) }

    private external fun rcMinVbvOverflowUse(): Float
    private external fun rcMinVbvOverflowUse(rcMinVbvOverflowUse: Float)
    var rcMinVbvOverflowUse: Float
        get() = rcMinVbvOverflowUse()
        set(value) { rcMinVbvOverflowUse(value) }

    private external fun rcInitialBufferOccupancy(): Int
    private external fun rcInitialBufferOccupancy(rcInitialBufferOccupancy: Int)
    var rcInitialBufferOccupancy: Int
        get() = rcInitialBufferOccupancy()
        set(value) { rcInitialBufferOccupancy(value) }

    private external fun trellis(): Int
    private external fun trellis(trellis: Int)
    var trellis: Int
        get() = trellis()
        set(value) { trellis(value) }

    private external fun workaroundBugs(): Int
    private external fun workaroundBugs(workaroundBugs: Int)
    var workaroundBugs: Int
        get() = workaroundBugs()
        set(value) { workaroundBugs(value) }

    private external fun strictStdCompliance(): Int
    private external fun strictStdCompliance(strictStdCompliance: Int)
    var strictStdCompliance: Int
        get() = strictStdCompliance()
        set(value) { strictStdCompliance(value) }

    private external fun errorConcealment(): Int
    private external fun errorConcealment(errorConcealment: Int)
    var errorConcealment: Int
        get() = errorConcealment()
        set(value) { errorConcealment(value) }

    private external fun debug(): Int
    private external fun debug(debug: Int)
    var debug: Int
        get() = debug()
        set(value) { debug(value) }

    private external fun errRecognition(): Int
    private external fun errRecognition(errRecognition: Int)
    var errRecognition: Int
        get() = errRecognition()
        set(value) { errRecognition(value) }

    private external fun reorderedOpaque(): Long
    private external fun reorderedOpaque(reorderedOpaque: Long)
    var reorderedOpaque: Long
        get() = reorderedOpaque()
        set(value) { reorderedOpaque(value) }

    private external fun dctAlgo(): Int
    private external fun dctAlgo(dctAlgo: Int)
    var dctAlgo: Int
        get() = dctAlgo()
        set(value) { dctAlgo(value) }

    private external fun idctAlgo(): Int
    private external fun idctAlgo(idctAlgo: Int)
    var idctAlgo: Int
        get() = idctAlgo()
        set(value) { idctAlgo(value) }

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

    private external fun threadCount(): Int
    private external fun threadCount(threadCount: Int)
    var threadCount: Int
        get() = threadCount()
        set(value) { threadCount(value) }

    private external fun threadType(): Int
    private external fun threadType(threadType: Int)
    var threadType: Int
        get() = threadType()
        set(value) { threadType(value) }

    private external fun activeThreadType(): Int
    val activeThreadType: Int
        get() = activeThreadType()

    // TODO: int thread_safe_callbacks, execute, execute2

    private external fun nsseWeight(): Int
    private external fun nsseWeight(nsseWeight: Int)
    var nsseWeight: Int
        get() = nsseWeight()
        set(value) { nsseWeight(value) }

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

    private external fun skipLoopFilter(): Discard
    private external fun skipLoopFilter(skipLoopFilter: Discard)
    var skipLoopFilter: Discard
        get() = skipLoopFilter()
        set(value) { skipLoopFilter(value) }

    private external fun skipIdct(): Discard
    private external fun skipIdct(skipIdct: Discard)
    var skipIdct: Discard
        get() = skipIdct()
        set(value) { skipIdct(value) }

    private external fun skipFrame(): Discard
    private external fun skipFrame(skipFrame: Discard)
    var skipFrame: Discard
        get() = skipFrame()
        set(value) { skipFrame(value) }

    private external fun initialPadding(): Int
    private external fun initialPadding(initialPadding: Int)
    var initialPadding: Int
        get() = initialPadding()
        set(value) { initialPadding(value) }

    private external fun frameRate(): Rational
    var frameRate: Rational get() = frameRate()
        set(value) {
            frameRate.num = value.num
            frameRate.den = value.den
        }

    private external fun swPixFmt(): PixelFormat
    private external fun swPixFmt(swPixFmt: PixelFormat)
    var swPixFmt: PixelFormat
        get() = swPixFmt()
        set(value) { swPixFmt(value) }

    private external fun pktTimeBase(): Rational
    var pktTimeBase: Rational get() = pktTimeBase()
        set(value) {
            pktTimeBase.num = value.num
            pktTimeBase.den = value.den
        }

    private external fun skipAlpha(): Int
    private external fun skipAlpha(skipAlpha: Int)
    var skipAlpha: Int
        get() = skipAlpha()
        set(value) { skipAlpha(value) }

    private external fun seekPreroll(): Int
    private external fun seekPreroll(seekPreroll: Int)
    var seekPreroll: Int
        get() = seekPreroll()
        set(value) { seekPreroll(value) }

    private external fun trailingPadding(): Int
    private external fun trailingPadding(trailingPadding: Int)
    var trailingPadding: Int
        get() = trailingPadding()
        set(value) { trailingPadding(value) }

    private external fun maxPixels(): Long
    private external fun maxPixels(maxPixels: Long)
    var maxPixels: Long
        get() = maxPixels()
        set(value) { maxPixels(value) }

    private external fun hwAccelFlags(): Int
    private external fun hwAccelFlags(hwAccelFlags: Int)
    var hwAccelFlags: Int
        get() = hwAccelFlags()
        set(value) { hwAccelFlags(value) }

    private external fun applyCropping(): Int
    private external fun applyCropping(applyCropping: Int)
    var applyCropping: Int
        get() = applyCropping()
        set(value) { applyCropping(value) }

    private external fun extraHwFrames(): Int
    private external fun extraHwFrames(extraHwFrames: Int)
    var extraHwFrames: Int
        get() = extraHwFrames()
        set(value) { extraHwFrames(value) }

    private external fun discardDamagedPercentage(): Int
    private external fun discardDamagedPercentage(discardDamagedPercentage: Int)
    var discardDamagedPercentage: Int
        get() = discardDamagedPercentage()
        set(value) { discardDamagedPercentage(value) }
}
