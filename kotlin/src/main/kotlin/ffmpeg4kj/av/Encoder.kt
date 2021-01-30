package ffmpeg4kj.av

class Encoder private constructor(nativeStatePtr: Long)
    : CodecContext(nativeStatePtr) {

    companion object {

        /**
         * avcodec_find_encoder
         * avcodec_alloc_context3
         * avcodec_open2
         */
        @JvmStatic
        external fun createEncoder(codec: Codec): Encoder

        @JvmStatic
        fun createEncoder(codecId: CodecID): Encoder {
            val codec = Codec.findEncoderById(codecId)
                ?: throw IllegalArgumentException("Encoder not found for $codecId")
            return createEncoder(codec)
        }

    }

    private external fun eof(): Boolean
    val eof: Boolean get() = eof()

    /**
     * avcodec_send_frame
     *      AVERROR(EAGAIN):   false
     *      AVERROR_EOF:       false / sets EOF flag
     *      AVERROR(EINVAL):   exception
     *      AVERROR(ENOMEM):   exception
     */
    external fun sendFrame(frame: Frame): Boolean

    /**
     * avcodec_receive_packet
     *      AVERROR(EAGAIN):   false
     *      AVERROR_EOF:       false / sets EOF flag
     *      AVERROR(EINVAL):   exception
     *      other errors: legitimate decoding errors
     */
    external fun receivePacket(packet: Packet): Boolean

    external fun flush(): Boolean

}
