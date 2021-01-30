
#include "StreamNativeObject.h"

using namespace ffmpeg4kj::util;

StreamNativeObject::~StreamNativeObject() {
    this->stream = nullptr;
}

StreamNativeObject::StreamNativeObject(AVStream* stream) :
        AbstractNativeObject(StreamNativeObject_JAVA_TYPE_NAME),
        stream(stream) {

}

StreamNativeObject::StreamNativeObject(const StreamNativeObject& other) :
        AbstractNativeObject(other),
        stream(other.stream) {
}

StreamNativeObject::StreamNativeObject(StreamNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        stream(nullptr) {
    swap(*this, other);
}

StreamNativeObject& StreamNativeObject::operator=(StreamNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(StreamNativeObject& lhs, StreamNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.stream, rhs.stream);
}

AVStream* StreamNativeObject::getStream() {
    return this->stream;
}

std::shared_ptr<CodecParametersNativeObject> StreamNativeObject::getParameters() {
    return std::make_shared<CodecParametersNativeObject>(this->stream->codecpar);
}

void StreamNativeObject::setParameters(std::shared_ptr<CodecParametersNativeObject> params) {
    int ret = avcodec_parameters_copy(this->getStream()->codecpar, params->getCodecParameters());
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to avcodec_parameters_copy (" + ffmpeg_error_string(ret) + ")");
    }
}

std::shared_ptr<EncoderNativeObject> StreamNativeObject::createEncoder() {
    auto ret = EncoderNativeObject::createEncoder(this->getEncoderCodec());
    ret->setParameters(this->getParameters());
    return ret;
}

std::shared_ptr<DecoderNativeObject> StreamNativeObject::createDecoder() {
    auto ret = DecoderNativeObject::createDecoder(this->getDecoderCodec());
    ret->setParameters(this->getParameters());
    return ret;
}

std::shared_ptr<CodecNativeObject> StreamNativeObject::getEncoderCodec() {
    auto codec = CodecNativeObject::findEncoderById(this->getStream()->codecpar->codec_id);
    if (codec == nullptr) {
        throw Poco::RuntimeException("Unable to avcodec_find_encoder");
    }
    return codec;
}

std::shared_ptr<CodecNativeObject> StreamNativeObject::getDecoderCodec() {
    auto codec = CodecNativeObject::findDecoderById(this->getStream()->codecpar->codec_id);
    if (codec == nullptr) {
        throw Poco::RuntimeException("Unable to avcodec_find_encoder");
    }
    return codec;
}

