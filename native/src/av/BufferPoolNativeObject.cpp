
#include "BufferPoolNativeObject.h"

using namespace ffmpeg4kj::util;

#define ASSERT_POOL_NOT_NULL \
    if (this->pool == nullptr) { \
        throw Poco::IllegalStateException("Pool is null"); \
    }

BufferPoolNativeObject::~BufferPoolNativeObject() {
    this->pool = nullptr;
}

BufferPoolNativeObject::BufferPoolNativeObject(AVBufferPool* pool) :
        AbstractNativeObject(BufferPoolNativeObject_JAVA_TYPE_NAME),
        pool(pool) {
}

BufferPoolNativeObject::BufferPoolNativeObject(const BufferPoolNativeObject& other) :
        AbstractNativeObject(other),
        pool(other.pool) {
}

BufferPoolNativeObject::BufferPoolNativeObject(BufferPoolNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        pool(nullptr) {
    swap(*this, other);
}

BufferPoolNativeObject& BufferPoolNativeObject::operator=(BufferPoolNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(BufferPoolNativeObject& lhs, BufferPoolNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.pool, rhs.pool);
}

AVBufferPool* BufferPoolNativeObject::getPool() {
    ASSERT_POOL_NOT_NULL
    return this->pool;
}

std::shared_ptr<BufferNativeObject> BufferPoolNativeObject::getBuffer() {
    ASSERT_POOL_NOT_NULL
    AVBufferRef* buffer = av_buffer_pool_get(this->pool);
    if (buffer == nullptr) {
        throw Poco::RuntimeException("Unable to av_buffer_pool_get");
    }
    return std::make_shared<BufferNativeObject>(buffer);
}

void BufferPoolNativeObject::unInit() {
    if (this->pool == nullptr) {
        return;
    }
    av_buffer_pool_uninit(&this->pool);
}

std::shared_ptr<BufferPoolNativeObject> BufferPoolNativeObject::makeNew(int size) {
    AVBufferPool* pool = av_buffer_pool_init(size, nullptr);
    if (pool == nullptr) {
        throw Poco::RuntimeException("Unable to av_buffer_pool_init");
    }
    return std::make_shared<BufferPoolNativeObject>(pool);
}
