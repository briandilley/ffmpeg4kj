
#include "ffmpeg4kj_av_BufferPool.h"
#include "JniUtil.h"
#include "BufferPoolNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_BufferPool
 * Method:    getAVBuffer
 * Signature: ()Lffmpeg4kj/av/AVBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_BufferPool_getBuffer
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferPoolNativeObject>(env, obj);

    std::shared_ptr<BufferNativeObject> buffer;
    try {
        buffer = nativeObject->getBuffer();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return nullptr;
    }

    static jclass bufferClazz = jni_FindClass(env, bufferClazz, BufferNativeObject_JAVA_TYPE_NAME);
    static jmethodID ctr = jni_GetMethodId(env, bufferClazz, ctr, "<init>", "(J)V");
    return env->NewObject(bufferClazz, ctr, make_java_native_object_ptr(buffer));
}

/**
 * Class:     ffmpeg4kj_av_BufferPool
 * Method:    unInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_BufferPool_unInit
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<BufferPoolNativeObject>(env, obj);
    nativeObject->unInit();
}

/**
 * Class:     ffmpeg4kj_av_BufferPool
 * Method:    new
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_BufferPool_new
        (JNIEnv* env, jclass obj, jint size) {

    std::shared_ptr<BufferPoolNativeObject> nativeObject;
    try {
        nativeObject = BufferPoolNativeObject::makeNew(size);
    } catch (Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return 0;
    }

    return make_java_native_object_ptr(nativeObject);
}
