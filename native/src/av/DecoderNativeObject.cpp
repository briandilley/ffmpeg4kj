
#include "DecoderNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_OPEN \
    if (!this->isOpen()) { \
        throw Poco::IllegalStateException("Not open"); \
    }

DecoderNativeObject::~DecoderNativeObject() {
    this->eof = true;
}

DecoderNativeObject::DecoderNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context) :
        CodecContextNativeObject(codec, context),
        eof(false) {

}

DecoderNativeObject::DecoderNativeObject(const DecoderNativeObject& other) :
        CodecContextNativeObject(other),
        eof(other.eof) {
}

DecoderNativeObject::DecoderNativeObject(DecoderNativeObject&& other) noexcept :
        CodecContextNativeObject(std::move(other)),
        eof(false) {
    swap(*this, other);
}

DecoderNativeObject& DecoderNativeObject::operator=(DecoderNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(DecoderNativeObject& lhs, DecoderNativeObject& rhs) {
    std::swap(static_cast<CodecContextNativeObject&>(lhs), static_cast<CodecContextNativeObject&>(rhs));
    std::swap(lhs.eof, rhs.eof);
}

std::shared_ptr<DecoderNativeObject> DecoderNativeObject::createDecoder(std::shared_ptr<CodecNativeObject> codec) {
    AVCodecContext* context = avcodec_alloc_context3(codec->getRequiredCodec());
    if (context == nullptr) {
        throw Poco::RuntimeException("Unable to avcodec_alloc_context3");
    }

    return std::make_shared<DecoderNativeObject>(codec, context);
}

bool DecoderNativeObject::isEof() {
    return this->eof;
}

bool DecoderNativeObject::sendPacket(std::shared_ptr<PacketNativeObject> packet) {
    ASSERT_OPEN
    int ret = avcodec_send_packet(this->getRequiredCodecContext(), packet->getPacket());
    if (ret >= 0) {
        return true;
    } else if (ret == AVERROR(EAGAIN)) {
        return false;
    } else if (ret == AVERROR_EOF) {
        this->eof = true;
        return false;
    } else {
        throw Poco::RuntimeException(
                "Unable to avcodec_send_packet (" + ffmpeg_error_string(ret) + ")");
    }
}

bool DecoderNativeObject::receiveFrame(std::shared_ptr<FrameNativeObject> frame) {
    ASSERT_OPEN
    int ret = avcodec_receive_frame(this->getRequiredCodecContext(), frame->getRequiredFrame().get());
    if (ret >= 0) {
        return true;
    } else if (ret == AVERROR(EAGAIN)) {
        return false;
    } else if (ret == AVERROR_EOF) {
        this->eof = true;
        return false;
    } else {
        throw Poco::RuntimeException(
                "Unable to avcodec_receive_frame (" + ffmpeg_error_string(ret) + ")");
    }
}

bool DecoderNativeObject::flush() {
    ASSERT_OPEN
    int ret = avcodec_send_packet(this->getRequiredCodecContext(), nullptr);
    this->eof = true;
    if (ret >= 0) {
        return true;
    } else if (ret == AVERROR(EAGAIN)) {
        return false;
    } else if (ret == AVERROR_EOF) {
        return false;
    } else {
        throw Poco::RuntimeException(
                "Unable to avcodec_send_packet (flush) (" + ffmpeg_error_string(ret) + ")");
    }
}

void DecoderNativeObject::free() {
    CodecContextNativeObject::free();
    this->eof = true;
}
