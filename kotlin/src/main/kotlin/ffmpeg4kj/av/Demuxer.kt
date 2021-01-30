package ffmpeg4kj.av

class Demuxer private constructor(nativeStatePtr: Long)
    : FormatContext(nativeStatePtr) {

    companion object {

        /**
         * avformat_open_input
         */
        @JvmStatic
        external fun openInput(url: String? = null, options: String? = null, ioContext: IOContext? = null): Demuxer
    }

    fun createStreamDecoder(index: Int): Decoder {
        val stream = getStream(index)
            ?: throw IllegalArgumentException("Stream not found for index: $index")
        val decoder = Decoder.createDecoder(stream.codecParameters.codecId)
        decoder.setParameters(stream.codecParameters)
        return decoder
    }

    /**
     * avformat_find_stream_info
     */
    external fun findStreams(options: String? = null)

    /**
     * av_find_best_stream
     */
    external fun findBestStreamIndex(
        type: MediaType,
        wantedStreamNumber: Int = -1,
        relatedStream: Int = -1,
        flags: Int = -1): Int?

    /**
     * av_find_best_stream
     */
    fun findBestStream(
        type: MediaType,
        wantedStreamNumber: Int = -1,
        relatedStream: Int = -1,
        flags: Int = -1): Stream? = findBestStreamIndex(
            type, wantedStreamNumber, relatedStream, flags)?.let(::getStream)

    /**
     * av_read_frame
     * returns true on success
     * false if EOF and sets the eof flag
     * exception on error
     */
    external fun readFrame(packet: Packet): Boolean

    /**
     * avformat_close_input
     * avformat_free_context
     */
    external fun closeInput()

    fun dump() = dump(false)
}
