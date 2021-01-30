
#include "MuxerNativeObject.h"

using namespace ffmpeg4kj::util;

std::shared_ptr<MuxerNativeObject> MuxerNativeObject::openOutput(
        const std::string& format,
        const std::string& filename,
        std::shared_ptr<IOContextNativeObject> ioContext) {
    const char* formatCstr = format.empty()
        ? nullptr
        : format.c_str();

    const char* filenameCstr = filename.empty()
        ? nullptr
        : filename.c_str();

    AVFormatContext* context = nullptr;
    if (ioContext != nullptr) {
        context = avformat_alloc_context();
        if (context == nullptr) {
            throw Poco::RuntimeException("Unable to avformat_alloc_context");
        }
        context->pb = ioContext->getRequiredContext();
    }

    int ret = avformat_alloc_output_context2(&context, nullptr, formatCstr, filenameCstr);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avformat_alloc_output_context2 (" + ffmpeg_error_string(ret) + ")");
    }

    return std::make_shared<MuxerNativeObject>(context);
}

MuxerNativeObject::~MuxerNativeObject() {

}

MuxerNativeObject::MuxerNativeObject(AVFormatContext* context) :
        FormatContextNativeObject(context) {

}

MuxerNativeObject::MuxerNativeObject(const MuxerNativeObject& other) :
        FormatContextNativeObject(other) {
}

MuxerNativeObject::MuxerNativeObject(MuxerNativeObject&& other) noexcept :
        FormatContextNativeObject(std::move(other)) {
    swap(*this, other);
}

MuxerNativeObject& MuxerNativeObject::operator=(MuxerNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(MuxerNativeObject& lhs, MuxerNativeObject& rhs) {
    std::swap(static_cast<FormatContextNativeObject&>(lhs), static_cast<FormatContextNativeObject&>(rhs));
}

std::shared_ptr<StreamNativeObject> MuxerNativeObject::addStream(std::shared_ptr<CodecNativeObject> codec) {
    AVStream* stream = avformat_new_stream(this->getRequiredFormatContext(), codec->getCodec());
    if (stream == nullptr) {
        throw Poco::RuntimeException("Unable to avformat_new_stream");
    }
    return std::make_shared<StreamNativeObject>(stream);
}

bool MuxerNativeObject::writeHeader(const std::string& options) {

    if (!(this->getRequiredFormatContext()->oformat->flags & AVFMT_NOFILE)) {
        int ret = avio_open(
                &this->getRequiredFormatContext()->pb,
                this->getRequiredFormatContext()->url,
                AVIO_FLAG_WRITE);
        if (ret < 0) {
            throw Poco::RuntimeException(
                    "Unable to avformat_write_header (" + ffmpeg_error_string(ret) + "): " + options);
        }
    }

    AVDictionary* dictionaryOptions = string_to_av_dict(options);
    int ret = avformat_write_header(this->getRequiredFormatContext(), &dictionaryOptions);
    av_dict_free(&dictionaryOptions);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avformat_write_header (" + ffmpeg_error_string(ret) + "): " + options);
    }
    return ret == AVSTREAM_INIT_IN_WRITE_HEADER;
}

void MuxerNativeObject::writeFrame(std::shared_ptr<PacketNativeObject> packet) {
    int ret = av_write_frame(this->getRequiredFormatContext(), packet->getPacket());
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_write_frame (" + ffmpeg_error_string(ret) + ")");
    }
}

bool MuxerNativeObject::flushFrames() {
    int ret = av_write_frame(this->getRequiredFormatContext(), nullptr);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_write_frame (" + ffmpeg_error_string(ret) + ")");
    }
    return ret == 1;
}

void MuxerNativeObject::writeInterleavedFrame(std::shared_ptr<PacketNativeObject> packet) {
    int ret = av_interleaved_write_frame(this->getRequiredFormatContext(), packet->getPacket());
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_interleaved_write_frame (" + ffmpeg_error_string(ret) + ")");
    }
}

void MuxerNativeObject::flushInterleavedFrames() {
    int ret = av_interleaved_write_frame(this->getRequiredFormatContext(), nullptr);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_interleaved_write_frame (" + ffmpeg_error_string(ret) + ")");
    }
}

void MuxerNativeObject::writeTrailer() {
    int ret = av_write_trailer(this->getRequiredFormatContext());
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_write_trailer (" + ffmpeg_error_string(ret) + ")");
    }
}

void MuxerNativeObject::closeOutput() {
    FormatContextNativeObject::free(&avformat_free_context);
}
