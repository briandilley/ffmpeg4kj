
#include "ffmpeg4kj_av_Codec.h"
#include "JniUtil.h"
#include "CodecNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    id
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_id
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    return AVCodecIDToJava(env, nativeObject->getId());
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    capabilities
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Codec_capabilities
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    return nativeObject->getCapabilities();
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    name
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ffmpeg4kj_av_Codec_name
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    return env->NewStringUTF(nativeObject->getName().c_str());
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    wrapperName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ffmpeg4kj_av_Codec_wrapperName
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    auto ret = nativeObject->getWrapperName();
    if (ret.empty()) {
        return nullptr;
    }
    return env->NewStringUTF(ret.c_str());
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    longName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ffmpeg4kj_av_Codec_longName
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    auto ret = nativeObject->getLongName();
    if (ret.empty()) {
        return nullptr;
    }
    return env->NewStringUTF(ret.c_str());
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    type
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Codec_type
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecNativeObject>(env, obj);
    return nativeObject->getType();
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findEncoderByName
 * Signature: (Ljava/lang/String;)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findEncoderByName
        (JNIEnv* env, jclass clazz, jstring name) {

    auto strName = get_utf8_string_from_java(env, name);
    auto codec = CodecNativeObject::findEncoderByName(strName);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findEncoderById
 * Signature: (I)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findEncoderById__I
        (JNIEnv* env, jclass clazz, jint id) {

    auto codec = CodecNativeObject::findEncoderById((AVCodecID)id);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findEncoderById
 * Signature: (Lffmpeg4kj/av/CodecID;)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findEncoderById__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jclass clazz, jobject codecId) {

    auto avCodecId = JavaToAVCodecID(env, codecId);

    auto codec = CodecNativeObject::findEncoderById(avCodecId);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findDecoderByName
 * Signature: (Ljava/lang/String;)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findDecoderByName
        (JNIEnv* env, jclass clazz, jstring name) {

    auto strName = get_utf8_string_from_java(env, name);
    auto codec = CodecNativeObject::findDecoderByName(strName);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findDecoderById
 * Signature: (I)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findDecoderById__I
        (JNIEnv* env, jclass clazz, jint id) {

    auto codec = CodecNativeObject::findDecoderById((AVCodecID)id);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}

/**
 * Class:     ffmpeg4kj_av_Codec
 * Method:    findDecoderById
 * Signature: (Lffmpeg4kj/av/CodecID;)Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Codec_findDecoderById__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jclass clazz, jobject codecId) {

    auto avCodecId = JavaToAVCodecID(env, codecId);

    auto codec = CodecNativeObject::findDecoderById(avCodecId);
    if (codec == nullptr) {
        return nullptr;
    }

    static jmethodID cstr = jni_GetMethodId(env, clazz, cstr, "<init>", "(J)V");
    return env->NewObject(clazz, cstr, make_java_native_object_ptr(codec));
}
