
#include "ffmpeg4kj_av_IOContext.h"
#include "JniUtil.h"
#include "IOContextNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_IOContext
 * Method:    _close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_IOContext__1close
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<IOContextNativeObject>(env, obj);
    nativeObject->close();
}

/**
 * Class:     ffmpeg4kj_av_IOContext
 * Method:    createIOContext
 * Signature: (ILffmpeg4kj/av/ReadFunction;Lffmpeg4kj/av/WriteFunction;Lffmpeg4kj/av/SeekFunction;)Lffmpeg4kj/av/IOContext;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_IOContext_createIOContext
        (JNIEnv* env, jclass clazz, jint bufferSize, jobject read, jobject write, jobject seek) {

    if (read == nullptr && write == nullptr && seek == nullptr) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, "Need at least one IO function");
        return (jobject)nullptr;
    }

    try {
        auto nativeObject = std::make_shared<IOContextNativeObject>(
                bufferSize,
                read != nullptr ? create_read_function_for_java("readFunction") : nullptr,
                write != nullptr ? create_write_function_for_java("writeFunction") : nullptr,
                seek != nullptr ? create_seek_function_for_java("seekFunction") : nullptr);

        nativeObject->addReference("readFunction", read);
        nativeObject->addReference("writeFunction", write);
        nativeObject->addReference("seekFunction", seek);

        static jclass retClass = jni_FindClass(env, retClass, IOContextNativeObject_JAVA_TYPE_NAME);
        static jmethodID retCstr = jni_GetMethodId(env, retClass, retCstr, "<init>", "(J)V");
        return env->NewObject(retClass, retCstr, make_java_native_object_ptr(nativeObject));

    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}
