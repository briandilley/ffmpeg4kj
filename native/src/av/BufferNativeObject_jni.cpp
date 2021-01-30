
#include "ffmpeg4kj_av_Buffer.h"
#include "JniUtil.h"
#include "BufferNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    buffer
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Buffer_buffer
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);
    AVBufferRef* buffer = nativeObject->getBuffer();
    if (buffer == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "Buffer is null");
        return nullptr;
    }
    jobject ret = env->NewDirectByteBuffer(buffer->data, buffer->size);

    if (!nativeObject->isWritable()) {
        static jclass byteBufferClass = jni_GetObjectClass(env, byteBufferClass, ret);
        static jmethodID mid = jni_GetMethodId(
                env, byteBufferClass, mid, "asReadOnlyBuffer", "()Ljava/nio/ByteBuffer;");
        ret = env->CallObjectMethod(ret, mid);
        if (was_exception_thrown(env)) {
            return nullptr;
        }
    }

    return ret;
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Buffer_size
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);

    try {
        return nativeObject->getSize();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    writable
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Buffer_writable
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);

    try {
        return nativeObject->isWritable();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    makeWritable
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Buffer_makeWritable
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);

    try {
        nativeObject->makeWritable();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    ref
 * Signature: ()Lffmpeg4kj/av/AVBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Buffer_ref
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);

    std::shared_ptr<BufferNativeObject> ref;
    try {
        ref = nativeObject->ref();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return nullptr;
    }

    static jclass bufferClazz = jni_FindClass(env, bufferClazz, BufferNativeObject_JAVA_TYPE_NAME);
    static jmethodID ctr = jni_GetMethodId(env, bufferClazz, ctr, "<init>", "(J)V");
    return env->NewObject(bufferClazz, ctr, make_java_native_object_ptr(ref));
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    unref
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Buffer_unref
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);
    nativeObject->unref();
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    refCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Buffer_refCount
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferNativeObject>(env, obj);

    try {
        return nativeObject->refCount();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    new
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Buffer_new
        (JNIEnv* env, jclass clazz, jint size) {

    std::shared_ptr<BufferNativeObject> nativeObject;
    try {
        nativeObject = BufferNativeObject::makeNew(size);
    } catch (Poco::OutOfMemoryException& e) {
        THROW_OUT_OF_MEMORY_ERROR_JAVA(env, e.message());
        return 0;
    }

    return make_java_native_object_ptr(nativeObject);
}
