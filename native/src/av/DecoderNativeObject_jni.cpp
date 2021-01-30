
#include "ffmpeg4kj_av_Decoder.h"
#include "JniUtil.h"
#include "DecoderNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "PacketNativeObject.h"
#include "FrameNativeObject.h"
#include "CodecNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    open
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Decoder_open
            (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
    return nativeObject->isOpen();
}

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    eof
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Decoder_eof
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
    return nativeObject->isEof();
}

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    setParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Decoder_setParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
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
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    getParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Decoder_getParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
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
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    sendPacket
 * Signature: (Lffmpeg4kj/av/Packet;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Decoder_sendPacket
        (JNIEnv* env, jobject obj, jobject packet) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
    auto packetNativeObject = get_native_object<PacketNativeObject>(env, packet);
    try {
        return nativeObject->sendPacket(packetNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    receiveFrame
 * Signature: (Lffmpeg4kj/av/Frame;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Decoder_receiveFrame
        (JNIEnv* env, jobject obj, jobject frame) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
    auto frameNativeObject = get_native_object<FrameNativeObject>(env, frame);
    try {
        return nativeObject->receiveFrame(frameNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    flush
 * Signature: ()V
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Decoder_flush
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
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
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Decoder_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<DecoderNativeObject>(env, obj);
    nativeObject->free();
}

/**
 * Class:     ffmpeg4kj_av_Decoder
 * Method:    createDecoder
 * Signature: (Lffmpeg4kj/av/Codec;)Lffmpeg4kj/av/Decoder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Decoder_createDecoder
        (JNIEnv* env, jclass clazz, jobject codec) {

    auto codecNativeObject = get_native_object<CodecNativeObject>(env, codec);

    try {
        auto nativeObject = DecoderNativeObject::createDecoder(codecNativeObject);
        static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
        return env->NewObject(clazz, cstr, make_java_native_object_ptr(nativeObject));
    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return nullptr;
}
