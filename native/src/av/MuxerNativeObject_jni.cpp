
#include "ffmpeg4kj_av_Muxer.h"
#include "JniUtil.h"
#include "MuxerNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    addStream
 * Signature: (Lffmpeg4kj/av/Codec;)Lffmpeg4kj/av/Stream;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Muxer_addStream
        (JNIEnv* env, jobject obj, jobject codec) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        auto codecNativeObject = get_native_object<CodecNativeObject>(env, codec);
        auto stream = nativeObject->addStream(codecNativeObject);
        static jclass streamClazz = jni_FindClass(env, streamClazz, StreamNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
        auto ret =  env->NewObject(streamClazz, cstr, make_java_native_object_ptr(stream));
        return nativeObject->updateReference("getStream_" + std::to_string(stream->getStream()->index), ret);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    writeHeader
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Muxer_writeHeader
        (JNIEnv* env, jobject obj, jstring options) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        std::string optionsStr = options != nullptr
                ? get_utf8_string_from_java(env, options)
                : "";
        return nativeObject->writeHeader(optionsStr);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    writeFrame
 * Signature: (Lffmpeg4kj/av/Packet;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Muxer_writeFrame
        (JNIEnv* env, jobject obj, jobject packet) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        auto packetNativeObject = get_native_object<PacketNativeObject>(env, packet);
        nativeObject->writeFrame(packetNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    flushFrames
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Muxer_flushFrames
        (JNIEnv* env, jobject obj) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        return nativeObject->flushFrames();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    writeInterleavedFrame
 * Signature: (Lffmpeg4kj/av/Packet;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Muxer_writeInterleavedFrame
        (JNIEnv* env, jobject obj, jobject packet) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        auto packetNativeObject = get_native_object<PacketNativeObject>(env, packet);
        nativeObject->writeInterleavedFrame(packetNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    flushInterleavedFrames
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Muxer_flushInterleavedFrames
        (JNIEnv* env, jobject obj) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        nativeObject->flushInterleavedFrames();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    writeTrailer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Muxer_writeTrailer
        (JNIEnv* env, jobject obj) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        nativeObject->writeTrailer();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    openOutput
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lffmpeg4kj/av/IOContext;)Lffmpeg4kj/av/Muxer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Muxer_openOutput
        (JNIEnv* env, jclass obj, jstring format, jstring fileName, jobject ioContext) {

    std::string formatString = format == nullptr
            ? ""
            : get_utf8_string_from_java(env, format);

    std::string fileNameString = format == nullptr
            ? ""
            : get_utf8_string_from_java(env, fileName);

    auto ioContextNativeObject = ioContext != nullptr
            ? get_native_object<IOContextNativeObject>(env, ioContext)
            : nullptr;

    try {
        auto nativeObject = MuxerNativeObject::openOutput(formatString, fileNameString, ioContextNativeObject);
        if (ioContextNativeObject != nullptr) {
            nativeObject->addReference("ioContext", ioContext);
        }
        static jclass muxerClazz = jni_FindClass(env, muxerClazz, MuxerNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, muxerClazz, cstr, "<init>", "(J)V");
        return env->NewObject(muxerClazz, cstr, make_java_native_object_ptr(nativeObject));
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Muxer
 * Method:    closeOutput
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Muxer_closeOutput
        (JNIEnv* env, jobject obj) {
    try {
        auto nativeObject = get_native_object<MuxerNativeObject>(env, obj);
        nativeObject->closeOutput();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}
