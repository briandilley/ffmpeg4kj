package ffmpeg4kj.av

class Muxer private constructor(nativeStatePtr: Long)
    : FormatContext(nativeStatePtr) {

    companion object {

        /**
         * avformat_alloc_output_context2
         */
        @JvmStatic
        external fun openOutput(format: String? = null, filename: String? = null, ioContext: IOContext? = null): Muxer
    }

    /**
     * avformat_new_stream
     */
    external fun addStream(codec: Codec): Stream

    fun addStream(codecId: CodecID): Stream {
        val codec = Codec.findEncoderById(codecId)
            ?: throw IllegalArgumentException("Codec not found: $codecId")
        return addStream(codec)
    }

    fun addStream(encoder: Encoder): Stream {
        val ret = addStream(encoder.codecId)
        encoder.getParameters(ret.codecParameters)
        return ret
    }

    /**
     * avformat_write_header
     */
    external fun writeHeader(options: String? = null): Boolean

    /**
     * av_write_frame
     */
    external fun writeFrame(packet: Packet)

    /**
     * av_write_frame
     */
    external fun flushFrames(): Boolean

    /**
     * av_interleaved_write_frame
     */
    external fun writeInterleavedFrame(packet: Packet)

    /**
     * av_interleaved_write_frame
     */
    external fun flushInterleavedFrames()

    /**
     * av_write_trailer
     */
    external fun writeTrailer()

    /**
     * avformat_free_context
     */
    external fun closeOutput()

    fun dump() = dump(true)
}
