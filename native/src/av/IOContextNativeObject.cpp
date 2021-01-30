
#include "IOContextNativeObject.h"

#include <utility>

using namespace ffmpeg4kj::util;


IOContextNativeObject::~IOContextNativeObject() {
    this->close();
    this->context = nullptr;
    this->read = nullptr;
    this->write = nullptr;
    this->seek = nullptr;
}

IOContextNativeObject::IOContextNativeObject(
        int bufferSize,
        std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> read,
        std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> write,
        std::function<int64_t(IOContextNativeObject* obj, int64_t offset, int whence)> seek) :
        AbstractNativeObject(IOContextNativeObject_JAVA_TYPE_NAME),
        context(nullptr),
        read(read),
        write(write),
        seek(seek) {

    auto* buffer = (unsigned char*)av_malloc(bufferSize);
    if (buffer == nullptr) {
        throw Poco::RuntimeException("Unable to av_malloc");
    }

    this->context = avio_alloc_context(
            buffer,
            bufferSize,
            write != nullptr ? 1 : 0,
            this,
            read != nullptr ? &IOContextNativeObject::readCallback : nullptr,
            write != nullptr ? &IOContextNativeObject::writeCallback : nullptr,
            seek != nullptr ? &IOContextNativeObject::seekCallback : nullptr);

    if (this->context == nullptr) {
        throw Poco::RuntimeException("Unable to avio_alloc_context");
    }
}

IOContextNativeObject::IOContextNativeObject(const IOContextNativeObject& other) :
        AbstractNativeObject(other),
        context(other.context),
        read(other.read),
        write(other.write),
        seek(other.seek) {
}

IOContextNativeObject::IOContextNativeObject(IOContextNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        context(nullptr),
        read(nullptr),
        write(nullptr),
        seek(nullptr) {
    swap(*this, other);
}

IOContextNativeObject& IOContextNativeObject::operator=(IOContextNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(IOContextNativeObject& lhs, IOContextNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.context, rhs.context);
    std::swap(lhs.read, rhs.read);
    std::swap(lhs.write, rhs.write);
    std::swap(lhs.seek, rhs.seek);
}

AVIOContext* IOContextNativeObject::getContext() {
    return this->context;
}

AVIOContext* IOContextNativeObject::getRequiredContext() {
    if (this->context == nullptr) {
        throw Poco::IllegalStateException("AVIOContext has been freed");
    }
    return this->context;
}

void IOContextNativeObject::close() {
    if (this->context != nullptr) {
        av_free(this->context->buffer);
        avio_context_free(&this->context);
    }
    this->context = nullptr;
}

int IOContextNativeObject::readCallback(void* opaque, uint8_t *buf, int buf_size) {
    auto obj = static_cast<IOContextNativeObject*>(opaque);
    return obj->read(obj, buf, buf_size);
}

int IOContextNativeObject::writeCallback(void* opaque, uint8_t *buf, int buf_size) {
    auto obj = static_cast<IOContextNativeObject*>(opaque);
    return obj->write(obj, buf, buf_size);
}

int64_t IOContextNativeObject::seekCallback(void* opaque, int64_t offset, int whence) {
    auto obj = static_cast<IOContextNativeObject*>(opaque);
    return obj->seek(obj, offset, whence);
}

std::function<int(IOContextNativeObject* nativeObject, uint8_t *buf, int buf_size)> ffmpeg4kj::util::create_read_function_for_java(const std::string& refName) {
    return [refName](IOContextNativeObject* nativeObject, uint8_t *buf, int buf_size) {
        jni_WithAttachedEnv(
            jobject obj = nativeObject->getReference(refName);
            if (env->IsSameObject(obj, nullptr)) {
                poco_error(nativeObject->getLogger(), "ReadFunction is null");
                THROW_NULL_POINTER_EXCEPTION_JAVA(env, "ReadFunction is null");
                return AVERROR_UNKNOWN;
            }
            static jclass clazz = jni_FindClass(env, clazz, ReadFunction_JAVA_TYPE_NAME);
            static jmethodID method = jni_GetMethodId(env, clazz, method, "read", "(Ljava/nio/ByteBuffer;)I");
            return env->CallIntMethod(obj, method, env->NewDirectByteBuffer(buf, buf_size));
        )
    };
}

std::function<int(IOContextNativeObject* nativeObject, uint8_t *buf, int buf_size)> ffmpeg4kj::util::create_write_function_for_java(const std::string& refName) {
    return [refName](IOContextNativeObject* nativeObject, uint8_t *buf, int buf_size) {
        jni_WithAttachedEnv(
            jobject obj = nativeObject->getReference(refName);
            if (env->IsSameObject(obj, nullptr)) {
                poco_error(nativeObject->getLogger(), "WriteFunction is null");
                THROW_NULL_POINTER_EXCEPTION_JAVA(env, "WriteFunction is null");
                return AVERROR_UNKNOWN;
            }
            static jclass clazz = jni_FindClass(env, clazz, WriteFunction_JAVA_TYPE_NAME);
            static jmethodID method = jni_GetMethodId(env, clazz, method, "write", "(Ljava/nio/ByteBuffer;)I");
            return env->CallIntMethod(obj, method, env->NewDirectByteBuffer(buf, buf_size));
        )
    };
}

std::function<int64_t(IOContextNativeObject* nativeObject, int64_t offset, int whence)> ffmpeg4kj::util::create_seek_function_for_java(const std::string& refName) {
    return [refName](IOContextNativeObject* nativeObject, int64_t offset, int whence) {
        jni_WithAttachedEnv(
            jobject obj = nativeObject->getReference(refName);
            if (env->IsSameObject(obj, nullptr)) {
                poco_error(nativeObject->getLogger(), "SeekFunction is null");
                THROW_NULL_POINTER_EXCEPTION_JAVA(env, "SeekFunction is null");
                return AVERROR_UNKNOWN;
            }
            static jclass clazz = jni_FindClass(env, clazz, SeekFunction_JAVA_TYPE_NAME);
            static jmethodID method = jni_GetMethodId(env, clazz, method, "seek", "(JI)I");
            return env->CallIntMethod(obj, method, offset, whence);
        )
    };
}
