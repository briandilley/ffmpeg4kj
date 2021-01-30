
#include "EncoderNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_OPEN \
    if (!this->isOpen()) { \
        throw Poco::IllegalStateException("Not open"); \
    }

EncoderNativeObject::~EncoderNativeObject() {
    this->eof = true;
}

EncoderNativeObject::EncoderNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context) :
        CodecContextNativeObject(codec, context),
        eof(false) {

}

EncoderNativeObject::EncoderNativeObject(const EncoderNativeObject& other) :
        CodecContextNativeObject(other),
        eof(other.eof) {
}

EncoderNativeObject::EncoderNativeObject(EncoderNativeObject&& other) noexcept :
        CodecContextNativeObject(std::move(other)),
        eof(false) {
    swap(*this, other);
}

EncoderNativeObject& EncoderNativeObject::operator=(EncoderNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(EncoderNativeObject& lhs, EncoderNativeObject& rhs) {
    std::swap(static_cast<CodecContextNativeObject&>(lhs), static_cast<CodecContextNativeObject&>(rhs));
    std::swap(lhs.eof, rhs.eof);
}

std::shared_ptr<EncoderNativeObject> EncoderNativeObject::createEncoder(std::shared_ptr<CodecNativeObject> codec) {
    AVCodecContext* context = avcodec_alloc_context3(codec->getRequiredCodec());
    if (context == nullptr) {
        throw Poco::RuntimeException("Unable to avcodec_alloc_context3");
    }

    return std::make_shared<EncoderNativeObject>(codec, context);
}

bool EncoderNativeObject::isEof() {
    return this->eof;
}

bool EncoderNativeObject::sendFrame(std::shared_ptr<FrameNativeObject> frame) {
    ASSERT_OPEN
    int ret = avcodec_send_frame(this->getRequiredCodecContext(), frame->getRequiredFrame().get());
    if (ret >= 0) {
        return true;
    } else if (ret == AVERROR(EAGAIN)) {
        return false;
    } else if (ret == AVERROR_EOF) {
        this->eof = true;
        return false;
    } else {
        throw Poco::RuntimeException(
                "Unable to avcodec_send_frame (" + ffmpeg_error_string(ret) + ")");
    }
}

bool EncoderNativeObject::receivePacket(std::shared_ptr<PacketNativeObject> packet) {
    ASSERT_OPEN
    int ret = avcodec_receive_packet(this->getRequiredCodecContext(), packet->getPacket());
    if (ret >= 0) {
        return true;
    } else if (ret == AVERROR(EAGAIN)) {
        return false;
    } else if (ret == AVERROR_EOF) {
        this->eof = true;
        return false;
    } else {
        throw Poco::RuntimeException(
                "Unable to avcodec_receive_packet (" + ffmpeg_error_string(ret) + ")");
    }
}

bool EncoderNativeObject::flush() {
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

void EncoderNativeObject::free() {
    CodecContextNativeObject::free();
    this->eof = true;
}
