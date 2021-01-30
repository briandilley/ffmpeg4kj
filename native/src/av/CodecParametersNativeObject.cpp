
#include "CodecParametersNativeObject.h"

using namespace ffmpeg4kj::util;

static void free_params(AVCodecParameters* params) {
    avcodec_parameters_free(&params);
}

static std::shared_ptr<AVCodecParameters> alloc_params() {
    std::shared_ptr<AVCodecParameters> params(avcodec_parameters_alloc(), free_params);
    return params;
}

CodecParametersNativeObject::~CodecParametersNativeObject() {
    this->paramsRef = nullptr;
    this->params = nullptr;
}

CodecParametersNativeObject::CodecParametersNativeObject() :
        AbstractNativeObject(CodecParametersNativeObject_JAVA_TYPE_NAME),
        paramsRef(nullptr),
        params(alloc_params()) {

}

CodecParametersNativeObject::CodecParametersNativeObject(AVCodecParameters* paramsRef) :
        AbstractNativeObject(CodecParametersNativeObject_JAVA_TYPE_NAME),
        paramsRef(paramsRef),
        params(nullptr) {

}

CodecParametersNativeObject::CodecParametersNativeObject(const CodecParametersNativeObject& other) :
        AbstractNativeObject(other),
        paramsRef(other.paramsRef),
        params(other.params) {
}

CodecParametersNativeObject::CodecParametersNativeObject(CodecParametersNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        paramsRef(nullptr),
        params(nullptr) {
    swap(*this, other);
}

CodecParametersNativeObject& CodecParametersNativeObject::operator=(CodecParametersNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(CodecParametersNativeObject& lhs, CodecParametersNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.paramsRef, rhs.paramsRef);
    std::swap(lhs.params, rhs.params);
}

AVCodecParameters* CodecParametersNativeObject::getCodecParameters() {
    return this->paramsRef != nullptr
           ? this->paramsRef
           : this->params.get();
}

void CodecParametersNativeObject::copyFrom(std::shared_ptr<CodecParametersNativeObject> other) {
    int ret = avcodec_parameters_copy(this->getCodecParameters(), other->getCodecParameters());
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to avcodec_parameters_from_context " + ffmpeg_error_string(ret));
    }
}
