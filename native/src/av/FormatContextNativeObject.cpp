
#include "FormatContextNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_NOT_FREED \
    if (this->context == nullptr) { \
        throw Poco::IllegalStateException("AVFormatContext has been freed"); \
    }

FormatContextNativeObject::~FormatContextNativeObject() {
    this->context = nullptr;
}

FormatContextNativeObject::FormatContextNativeObject() :
        AbstractNativeObject(FormatContextNativeObject_JAVA_TYPE_NAME),
        context(nullptr) {

}

FormatContextNativeObject::FormatContextNativeObject(AVFormatContext* context) :
        AbstractNativeObject(FormatContextNativeObject_JAVA_TYPE_NAME),
        context(context) {

}

FormatContextNativeObject::FormatContextNativeObject(const FormatContextNativeObject& other) :
        AbstractNativeObject(other),
        context(other.context) {
}

FormatContextNativeObject::FormatContextNativeObject(FormatContextNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        context(nullptr) {
    swap(*this, other);
}

FormatContextNativeObject& FormatContextNativeObject::operator=(FormatContextNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(FormatContextNativeObject& lhs, FormatContextNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.context, rhs.context);
}

AVFormatContext* FormatContextNativeObject::getFormatContext() {
    return this->context;
}

AVFormatContext* FormatContextNativeObject::getRequiredFormatContext() {
    ASSERT_NOT_FREED
    return this->context;
}

int FormatContextNativeObject::getStreamCount() {
    ASSERT_NOT_FREED
    return this->context->nb_streams;
}

std::shared_ptr<StreamNativeObject> FormatContextNativeObject::getStream(int index) {
    ASSERT_NOT_FREED
    if (index >= this->context->nb_streams || index < 0) {
        throw Poco::RuntimeException("Invalid stream index");
    }
    return std::make_shared<StreamNativeObject>(this->context->streams[index]);
}

void FormatContextNativeObject::free(AVFormatContextFree free) {
    if (this->context != nullptr) {
        free(this->context);
    }
    this->context = nullptr;
}

void FormatContextNativeObject::free(AVFormatContextFreePtr free) {
    if (this->context != nullptr) {
        free(&this->context);
    }
    this->context = nullptr;
}

void FormatContextNativeObject::dump(bool isOutput) {
    av_dump_format(
            this->getRequiredFormatContext(), -1,
            this->getRequiredFormatContext()->url,
            isOutput ? 1 : 0);
}
