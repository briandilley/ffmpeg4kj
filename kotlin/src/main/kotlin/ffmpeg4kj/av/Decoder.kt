package ffmpeg4kj.av

class Decoder private constructor(nativeStatePtr: Long)
    : CodecContext(nativeStatePtr) {

    companion object {

        /**
         * avcodec_alloc_context3
         */
        @JvmStatic
        external fun createDecoder(codec: Codec): Decoder

        @JvmStatic
        fun createDecoder(codecId: CodecID): Decoder {
            val codec = Codec.findDecoderById(codecId)
                ?: throw IllegalArgumentException("Decoder not found for $codecId")
            return createDecoder(codec)
        }

    }

    private external fun eof(): Boolean
    val eof: Boolean get() = eof()

    /**
     * avcodec_send_packet
     *      AVERROR(EAGAIN):   false
     *      AVERROR_EOF:       false / sets eof flag
     *      AVERROR(EINVAL):   exception
     *      AVERROR(ENOMEM):   exception
     */
    external fun sendPacket(packet: Packet): Boolean

    /**
     * avcodec_receive_frame
     *      AVERROR(EAGAIN):   false
     *      AVERROR_EOF:       false / sets eof flag
     *      AVERROR(EINVAL):   exception
     *      AVERROR(ENOMEM):   exception
     */
    external fun receiveFrame(frame: Frame): Boolean

    external fun flush(): Boolean
}
