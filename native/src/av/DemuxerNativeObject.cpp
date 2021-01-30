
#include "DemuxerNativeObject.h"

using namespace ffmpeg4kj::util;

std::shared_ptr<DemuxerNativeObject> DemuxerNativeObject::openInput(
        const std::string& url,
        const std::string& options,
        std::shared_ptr<IOContextNativeObject> ioContext) {

    const char* urlCstr = url.empty()
        ? nullptr
        : url.c_str();

    AVDictionary* dictionaryOptions = string_to_av_dict(options);

    AVFormatContext* context = nullptr;
    if (ioContext != nullptr) {
        context = avformat_alloc_context();
        if (context == nullptr) {
            throw Poco::RuntimeException("Unable to avformat_alloc_context");
        }
        context->pb = ioContext->getRequiredContext();
    }

    int ret = avformat_open_input(&context, urlCstr, nullptr, &dictionaryOptions);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avformat_open_input (" + ffmpeg_error_string(ret) + ")");
    }

    return std::make_shared<DemuxerNativeObject>(context);
}

DemuxerNativeObject::~DemuxerNativeObject() {

}

DemuxerNativeObject::DemuxerNativeObject(AVFormatContext* context) :
        FormatContextNativeObject(context) {

}

DemuxerNativeObject::DemuxerNativeObject(const DemuxerNativeObject& other) :
        FormatContextNativeObject(other) {
}

DemuxerNativeObject::DemuxerNativeObject(DemuxerNativeObject&& other) noexcept :
        FormatContextNativeObject(std::move(other)) {
    swap(*this, other);
}

DemuxerNativeObject& DemuxerNativeObject::operator=(DemuxerNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(DemuxerNativeObject& lhs, DemuxerNativeObject& rhs) {
    std::swap(static_cast<FormatContextNativeObject&>(lhs), static_cast<FormatContextNativeObject&>(rhs));
}

void DemuxerNativeObject::findStreams(const std::string& options) {
    if (this->getStreamCount() > 0) {
        return;
    }
    AVDictionary* dictionaryOptions = string_to_av_dict(options);
    int ret = avformat_find_stream_info(this->getRequiredFormatContext(), &dictionaryOptions);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avformat_find_stream_info (" + ffmpeg_error_string(ret) + "): " + options);
    }
}

int DemuxerNativeObject::findBestStreamIndex(AVMediaType type, int wantedStreamNumber, int relatedStream, int flags) {
    int ret = av_find_best_stream(
            this->getRequiredFormatContext(), type, wantedStreamNumber, relatedStream, nullptr, flags);
    if (ret == AVERROR_STREAM_NOT_FOUND) {
        return -1;
    } else if (ret == AVERROR_DECODER_NOT_FOUND) {
        throw Poco::RuntimeException(
                "Unable to av_find_best_stream (AVERROR_DECODER_NOT_FOUND)");
    } else if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_find_best_stream (" + ffmpeg_error_string(ret) + ")");
    }
    return ret;
}


bool DemuxerNativeObject::readFrame(std::shared_ptr<PacketNativeObject> packet) {
    int ret = av_read_frame(this->getRequiredFormatContext(), packet->getPacket());
    if (ret == 0) {
        return true;
    } else if (ret == AVERROR_EOF) {
        return false;
    }
    throw Poco::RuntimeException(
            "Unable to av_read_frame (" + ffmpeg_error_string(ret) + ")");
}

void DemuxerNativeObject::closeInput() {
    FormatContextNativeObject::free(&avformat_close_input);
}
