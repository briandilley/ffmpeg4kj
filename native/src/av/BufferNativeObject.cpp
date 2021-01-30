
#include "BufferNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_BUFFER_NOT_NULL \
    if (this->buffer == nullptr) { \
        throw Poco::IllegalStateException("Buffer is null"); \
    }

BufferNativeObject::~BufferNativeObject() {
    this->buffer = nullptr;
}

BufferNativeObject::BufferNativeObject(AVBufferRef* buffer) :
        AbstractNativeObject(BufferNativeObject_JAVA_TYPE_NAME),
        buffer(buffer) {
}

BufferNativeObject::BufferNativeObject(const BufferNativeObject& other) :
        AbstractNativeObject(other),
        buffer(other.buffer) {
}

BufferNativeObject::BufferNativeObject(BufferNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        buffer(nullptr) {
    swap(*this, other);
}

BufferNativeObject& BufferNativeObject::operator=(BufferNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(BufferNativeObject& lhs, BufferNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.buffer, rhs.buffer);
}

AVBufferRef* BufferNativeObject::getBuffer() {
    return this->buffer;
}

int BufferNativeObject::getSize() {
    ASSERT_BUFFER_NOT_NULL
    return this->buffer->size;
}

bool BufferNativeObject::isWritable() {
    ASSERT_BUFFER_NOT_NULL
    return av_buffer_is_writable(this->buffer) == 1;
}

std::shared_ptr<BufferNativeObject> BufferNativeObject::ref() {
    ASSERT_BUFFER_NOT_NULL
    AVBufferRef* ref = av_buffer_ref(this->buffer);
    if (ref == nullptr) {
        throw Poco::RuntimeException("av_buffer_ref produced a nullptr");
    }
    return std::make_shared<BufferNativeObject>(ref);
}

void BufferNativeObject::makeWritable() {
    ASSERT_BUFFER_NOT_NULL
    int ret = av_buffer_make_writable(&this->buffer);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_buffer_make_writable (" + ffmpeg_error_string(ret) + ")");
    }
}

void BufferNativeObject::unref() {
    if (this->buffer == nullptr) {
        return;
    }
    av_buffer_unref(&this->buffer);
}

int BufferNativeObject::refCount() {
    ASSERT_BUFFER_NOT_NULL
    return av_buffer_get_ref_count(this->buffer);
}

std::shared_ptr<BufferNativeObject> BufferNativeObject::makeNew(int size) {
    AVBufferRef* buffer = av_buffer_alloc(size);
    if (buffer == nullptr) {
        throw Poco::OutOfMemoryException("Unable to av_buffer_alloc");
    }
    return std::make_shared<BufferNativeObject>(buffer);
}
