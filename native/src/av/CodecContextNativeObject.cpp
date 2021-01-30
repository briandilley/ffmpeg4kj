
#include "CodecContextNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_NOT_FREED \
    if (this->context == nullptr) { \
        throw Poco::IllegalStateException("AVCodecContext has been freed"); \
    }

CodecContextNativeObject::~CodecContextNativeObject() {
    this->_open = false;
    this->codec = nullptr;
    this->context = nullptr;
}

CodecContextNativeObject::CodecContextNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context) :
        AbstractNativeObject(CodecContextNativeObject_JAVA_TYPE_NAME),
        codec(codec),
        context(context),
        _open(false) {

}

CodecContextNativeObject::CodecContextNativeObject(const CodecContextNativeObject& other) :
        AbstractNativeObject(other),
        codec(other.codec),
        context(other.context),
        _open(other._open) {
}

CodecContextNativeObject::CodecContextNativeObject(CodecContextNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        codec(nullptr),
        context(nullptr),
        _open(false) {
    swap(*this, other);
}

CodecContextNativeObject& CodecContextNativeObject::operator=(CodecContextNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(CodecContextNativeObject& lhs, CodecContextNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.codec, rhs.codec);
    std::swap(lhs.context, rhs.context);
    std::swap(lhs._open, rhs._open);
}

std::shared_ptr<CodecNativeObject> CodecContextNativeObject::getCodec() {
    return this->codec;
}

AVCodecContext* CodecContextNativeObject::getCodecContext() {
    return this->context;
}

std::shared_ptr<CodecNativeObject> CodecContextNativeObject::getRequiredCodec() {
    ASSERT_NOT_FREED
    return this->codec;
}

AVCodecContext* CodecContextNativeObject::getRequiredCodecContext() {
    ASSERT_NOT_FREED
    return this->context;
}

void CodecContextNativeObject::open(const std::string& openOptions) {
    ASSERT_NOT_FREED

    AVDictionary* options = string_to_av_dict(openOptions);

    int ret = avcodec_open2(this->context, this->codec->getRequiredCodec(), &options);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avcodec_open2 (" + ffmpeg_error_string(ret) + ")");
    }
    this->_open = true;

    av_dict_free(&options);
}

bool CodecContextNativeObject::isOpen() {
    return this->_open;
}

void CodecContextNativeObject::setParameters(std::shared_ptr<CodecParametersNativeObject> params) {
    ASSERT_NOT_FREED
    int ret = avcodec_parameters_to_context(this->context, params->getCodecParameters());
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avcodec_parameters_to_context (" + ffmpeg_error_string(ret) + ")");
    }
}

void CodecContextNativeObject::getParameters(std::shared_ptr<CodecParametersNativeObject> params) {
    ASSERT_NOT_FREED
    int ret = avcodec_parameters_from_context(params->getCodecParameters(), this->context);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to avcodec_parameters_from_context (" + ffmpeg_error_string(ret) + ")");
    }
}

void CodecContextNativeObject::free() {
    if (this->context == nullptr) {
        return;
    }
    avcodec_free_context(&this->context);
    this->_open = false;
    this->context = nullptr;
}

void CodecContextNativeObject::allocateExtraData(int size) {
    if (this->getRequiredCodecContext()->extradata_size > 0
        && this->getRequiredCodecContext()->extradata != nullptr) {
        throw Poco::IllegalStateException("Extra data already exists");
    }
    this->getRequiredCodecContext()->extradata = (uint8_t*)av_malloc(size);
    this->getRequiredCodecContext()->extradata_size = size;
    this->selfAllocatedExtraData = true;
}

void CodecContextNativeObject::deallocateExtraData() {
    if (!this->selfAllocatedExtraData) {
        throw Poco::IllegalStateException("Haven't self alocated extra data");
    }
    av_free(this->getRequiredCodecContext()->extradata);
    this->getRequiredCodecContext()->extradata = nullptr;
    this->getRequiredCodecContext()->extradata_size = 0;
}
