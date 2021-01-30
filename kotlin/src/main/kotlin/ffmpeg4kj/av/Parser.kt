package ffmpeg4kj.av

import ffmpeg4kj.util.AbstractNativeObject
import java.nio.ByteBuffer

class Parser private constructor(nativeStatePtr: Long)
    : AbstractNativeObject(nativeStatePtr) {

    companion object {

        @JvmStatic
        external fun createParser(id: CodecID): Parser

    }

    external fun update(byteBuffer: ByteBuffer)

    /**
     * Uses av_parser_parse2 on data fed to it by the update method.
     */
    external fun parse(codecContext: CodecContext, packet: Packet, pts: Long = 0, dts: Long = 0, pos: Long = AV_NOPTS_VALUE): Boolean

    /**
     * av_parser_parse2
     */
    external fun parse(codecContext: CodecContext, input: ByteBuffer, pts: Long = 0, dts: Long = 0, pos: Long = AV_NOPTS_VALUE): ByteBuffer?

    /**
     * av_parser_close
     */
    external fun free()

    private external fun frameOffset(): Long
    private external fun frameOffset(frameOffset: Long)
    var frameOffset: Long
        get() = frameOffset()
        set(value) { frameOffset(value) }

    private external fun curOffset(): Long
    private external fun curOffset(curOffset: Long)
    var curOffset: Long
        get() = curOffset()
        set(value) { curOffset(value) }

    private external fun nextFrameOffset(): Long
    private external fun nextFrameOffset(nextFrameOffset: Long)
    var nextFrameOffset: Long
        get() = nextFrameOffset()
        set(value) { nextFrameOffset(value) }

    private external fun pictType(): Int
    private external fun pictType(pictType: Int)
    var pictType: Int
        get() = pictType()
        set(value) { pictType(value) }

    private external fun repeatPict(): Int
    private external fun repeatPict(repeatPict: Int)
    var repeatPict: Int
        get() = repeatPict()
        set(value) { repeatPict(value) }

    private external fun pts(): Long
    private external fun pts(pts: Long)
    var pts: Long
        get() = pts()
        set(value) { pts(value) }

    private external fun dts(): Long
    private external fun dts(dts: Long)
    var dts: Long
        get() = dts()
        set(value) { dts(value) }

    private external fun lastPts(): Long
    private external fun lastPts(lastPts: Long)
    var lastPts: Long
        get() = lastPts()
        set(value) { lastPts(value) }

    private external fun lastDts(): Long
    private external fun lastDts(lastDts: Long)
    var lastDts: Long
        get() = lastDts()
        set(value) { lastDts(value) }

    private external fun fetchTimestamp(): Int
    private external fun fetchTimestamp(fetchTimestamp: Int)
    var fetchTimestamp: Int
        get() = fetchTimestamp()
        set(value) { fetchTimestamp(value) }

    private external fun currentFrameStartIndex(): Int
    private external fun currentFrameStartIndex(currentFrameStartIndex: Int)
    var currentFrameStartIndex: Int
        get() = currentFrameStartIndex()
        set(value) { currentFrameStartIndex(value) }

    external fun getCurrentFrameOffset(index: Int): Long
    external fun setCurrentFrameOffset(index: Int, value: Long)

    external fun getCurrentFramePts(index: Int): Long
    external fun setCurrentFramePts(index: Int, value: Long)

    external fun getCurrentFrameDts(index: Int): Long
    external fun setCurrentFrameDts(index: Int, value: Long)

    private external fun flags(): Int
    private external fun flags(flags: Int)
    var flags: Int
        get() = flags()
        set(value) { flags(value) }

    private external fun offset(): Long
    private external fun offset(offset: Long)
    var offset: Long
        get() = offset()
        set(value) { offset(value) }

    external fun getCurrentFrameEnd(index: Int): Long
    external fun setCurrentFrameEnd(index: Int, value: Long)

    private external fun keyFrame(): Int
    private external fun keyFrame(keyFrame: Int)
    var keyFrame: Int
        get() = keyFrame()
        set(value) { keyFrame(value) }

    private external fun dtsSyncPoint(): Int
    private external fun dtsSyncPoint(dtsSyncPoint: Int)
    var dtsSyncPoint: Int
        get() = dtsSyncPoint()
        set(value) { dtsSyncPoint(value) }

    private external fun dtsRefDtsDelta(): Int
    private external fun dtsRefDtsDelta(dtsRefDtsDelta: Int)
    var dtsRefDtsDelta: Int
        get() = dtsRefDtsDelta()
        set(value) { dtsRefDtsDelta(value) }

    private external fun ptsDtsDelta(): Int
    private external fun ptsDtsDelta(ptsDtsDelta: Int)
    var ptsDtsDelta: Int
        get() = ptsDtsDelta()
        set(value) { ptsDtsDelta(value) }

    external fun getCurrentFramePos(index: Int): Long
    external fun setCurrentFramePos(index: Int, value: Long)

    private external fun pos(): Long
    private external fun pos(pos: Long)
    var pos: Long
        get() = pos()
        set(value) { pos(value) }

    private external fun lastPos(): Long
    private external fun lastPos(lastPos: Long)
    var lastPos: Long
        get() = lastPos()
        set(value) { lastPos(value) }

    private external fun duration(): Int
    private external fun duration(duration: Int)
    var duration: Int
        get() = duration()
        set(value) { duration(value) }

    private external fun fieldOrder(): FieldOrder
    private external fun fieldOrder(fieldOrder: FieldOrder)
    var fieldOrder: FieldOrder
        get() = fieldOrder()
        set(value) { fieldOrder(value) }

    private external fun pictureStructure(): PictureStructure
    private external fun pictureStructure(pictureStructure: PictureStructure)
    var pictureStructure: PictureStructure
        get() = pictureStructure()
        set(value) { pictureStructure(value) }

    private external fun outputPictureNumber(): Int
    private external fun outputPictureNumber(outputPictureNumber: Int)
    var outputPictureNumber: Int
        get() = outputPictureNumber()
        set(value) { outputPictureNumber(value) }

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

    private external fun format(): Int
    private external fun format(format: Int)
    var format: Int
        get() = format()
        set(value) { format(value) }
}
