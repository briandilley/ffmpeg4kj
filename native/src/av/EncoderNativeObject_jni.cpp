
#include "ffmpeg4kj_av_Encoder.h"
#include "JniUtil.h"
#include "EncoderNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "PacketNativeObject.h"
#include "FrameNativeObject.h"
#include "CodecNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    open
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Encoder_open
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    return nativeObject->isOpen();
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    eof
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Encoder_eof
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    return nativeObject->isEof();
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    setParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Encoder_setParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    auto paramsNativeObject = get_native_object<CodecParametersNativeObject>(env, params);
    try {
        return nativeObject->setParameters(paramsNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    getParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Encoder_getParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    auto paramsNativeObject = get_native_object<CodecParametersNativeObject>(env, params);
    try {
        return nativeObject->getParameters(paramsNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    sendPacket
 * Signature: (Lffmpeg4kj/av/Packet;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Encoder_sendFrame
        (JNIEnv* env, jobject obj, jobject frame) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    auto frameNativeObject = get_native_object<FrameNativeObject>(env, frame);
    try {
        return nativeObject->sendFrame(frameNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    receiveFrame
 * Signature: (Lffmpeg4kj/av/Frame;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Encoder_receivePacket
        (JNIEnv* env, jobject obj, jobject packet) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    auto packetNativeObject = get_native_object<PacketNativeObject>(env, packet);
    try {
        return nativeObject->receivePacket(packetNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    flush
 * Signature: ()V
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Encoder_flush
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    try {
        return nativeObject->flush();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Encoder_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<EncoderNativeObject>(env, obj);
    nativeObject->free();
}

/**
 * Class:     ffmpeg4kj_av_Encoder
 * Method:    createEncoder
 * Signature: (Lffmpeg4kj/av/Codec;)Lffmpeg4kj/av/Encoder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Encoder_createEncoder
        (JNIEnv* env, jclass clazz, jobject codec) {

    auto codecNativeObject = get_native_object<CodecNativeObject>(env, codec);

    try {
        auto nativeObject = EncoderNativeObject::createEncoder(codecNativeObject);
        static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
        return env->NewObject(clazz, cstr, make_java_native_object_ptr(nativeObject));
    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return nullptr;
}
