
#include "CodecNativeObject.h"

using namespace ffmpeg4kj::util;

std::shared_ptr<CodecNativeObject> CodecNativeObject::findEncoderByName(std::string& name) {
    AVCodec* codec = avcodec_find_encoder_by_name(name.c_str());
    if (codec == nullptr) {
        return nullptr;
    }
    return std::make_shared<CodecNativeObject>(codec);
}

std::shared_ptr<CodecNativeObject> CodecNativeObject::findEncoderById(AVCodecID id) {
    AVCodec* codec = avcodec_find_encoder((AVCodecID)id);
    if (codec == nullptr) {
        return nullptr;
    }
    return std::make_shared<CodecNativeObject>(codec);
}


std::shared_ptr<CodecNativeObject> CodecNativeObject::findDecoderByName(std::string& name) {
    AVCodec* codec = avcodec_find_decoder_by_name(name.c_str());
    if (codec == nullptr) {
        return nullptr;
    }
    return std::make_shared<CodecNativeObject>(codec);
}

std::shared_ptr<CodecNativeObject> CodecNativeObject::findDecoderById(AVCodecID id) {
    AVCodec* codec = avcodec_find_decoder((AVCodecID)id);
    if (codec == nullptr) {
        return nullptr;
    }
    return std::make_shared<CodecNativeObject>(codec);
}

CodecNativeObject::~CodecNativeObject() {
    this->codec = nullptr;
}

CodecNativeObject::CodecNativeObject(AVCodec* codec) :
        AbstractNativeObject(CodecNativeObject_JAVA_TYPE_NAME),
        codec(codec) {
}

CodecNativeObject::CodecNativeObject(const CodecNativeObject& other) :
        AbstractNativeObject(other),
        codec(other.codec) {
}

CodecNativeObject::CodecNativeObject(CodecNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        codec(nullptr) {
    swap(*this, other);
}

CodecNativeObject& CodecNativeObject::operator=(CodecNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(CodecNativeObject& lhs, CodecNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.codec, rhs.codec);
}

AVCodec* CodecNativeObject::getCodec() {
    return this->codec;
}

AVCodec* CodecNativeObject::getRequiredCodec() {
    if (this->codec == nullptr) {
        throw Poco::IllegalStateException("codec is null");
    }
    return this->codec;
}

AVCodecID CodecNativeObject::getId() {
    return this->codec->id;
}

int CodecNativeObject::getType() {
    return this->codec->type;
}

int CodecNativeObject::getCapabilities() {
    return this->codec->capabilities;
}

std::string CodecNativeObject::getName() {
    if (this->codec->name == nullptr) {
        return "";
    }
    return this->codec->name;
}

std::string CodecNativeObject::getWrapperName() {
    if (this->codec->wrapper_name == nullptr) {
        return "";
    }
    return this->codec->wrapper_name;
}

std::string CodecNativeObject::getLongName() {
    if (this->codec->long_name == nullptr) {
        return "";
    }
    return this->codec->long_name;
}
