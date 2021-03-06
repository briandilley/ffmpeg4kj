
#include "ffmpeg4kj_av_CodecParameters.h"
#include "JniUtil.h"
#include "CodecParametersNativeObject.h"
#include "RationalNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    copyFrom
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_copyFrom
        (JNIEnv* env, jobject obj, jobject other) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto otherNativeObject = get_native_object<CodecParametersNativeObject>(env, other);
    try {
        nativeObject->copyFrom(otherNativeObject);
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecType
 * Signature: ()Lffmpeg4kj/av/MediaType;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_codecType__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->codec_type;
    return AVMediaTypeToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecType
 * Signature: (Lffmpeg4kj/av/MediaType;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_codecType__Lffmpeg4kj_av_MediaType_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->codec_type = JavaToAVMediaType(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_codecId__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->codec_id;
    return AVCodecIDToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_codecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->codec_id = JavaToAVCodecID(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecTag
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecParameters_codecTag__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->codec_tag;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    codecTag
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_codecTag__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->codec_tag = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    pixelFormat
 * Signature: ()Lffmpeg4kj/av/PixelFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_pixelFormat__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->format;
    return AVPixelFormatToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    pixelFormat
 * Signature: (Lffmpeg4kj/av/PixelFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_pixelFormat__Lffmpeg4kj_av_PixelFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->format = JavaToAVPixelFormat(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    sampleFormat
 * Signature: ()Lffmpeg4kj/av/SampleFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_sampleFormat__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->format;
    return AVSampleFormatToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    sampleFormat
 * Signature: (Lffmpeg4kj/av/SampleFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_sampleFormat__Lffmpeg4kj_av_SampleFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->format = JavaToAVSampleFormat(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitRate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecParameters_bitRate__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->bit_rate;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitRate
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_bitRate__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->bit_rate = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitsPerCodedSample
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_bitsPerCodedSample__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->bits_per_coded_sample;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitsPerCodedSample
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_bitsPerCodedSample__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->bits_per_coded_sample = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitsPerRawSample
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_bitsPerRawSample__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->bits_per_raw_sample;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    bitsPerRawSample
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_bitsPerRawSample__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->bits_per_raw_sample = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    profile
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_profile__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->profile;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    profile
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_profile__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->profile = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    level
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_level__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->level;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    level
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_level__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->level = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    width
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_width__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->width;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    width
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_width__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->width = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    height
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_height__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->height;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    height
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_height__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->height = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    sampleAspectRatio
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_sampleAspectRatio
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);

    return nativeObject->getReference("sampleAspectRatio", [nativeObject, env]() {
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(
                &nativeObject->getCodecParameters()->sample_aspect_ratio);
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V");
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    fieldOrder
 * Signature: ()Lffmpeg4kj/av/FieldOrder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_fieldOrder__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->field_order;
    return AVFieldOrderToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    fieldOrder
 * Signature: (Lffmpeg4kj/av/FieldOrder;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_fieldOrder__Lffmpeg4kj_av_FieldOrder_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->field_order = JavaToAVFieldOrder(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorRange
 * Signature: ()Lffmpeg4kj/av/ColorRange;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_colorRange__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->color_range;
    return AVColorRangeToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorRange
 * Signature: (Lffmpeg4kj/av/ColorRange;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_colorRange__Lffmpeg4kj_av_ColorRange_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->color_range = JavaToAVColorRange(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorPrimaries
 * Signature: ()Lffmpeg4kj/av/ColorPrimaries;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_colorPrimaries__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->color_primaries;
    return AVColorPrimariesToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorPrimaries
 * Signature: (Lffmpeg4kj/av/ColorPrimaries;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_colorPrimaries__Lffmpeg4kj_av_ColorPrimaries_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->color_primaries = JavaToAVColorPrimaries(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorTransferCharacteristic
 * Signature: ()Lffmpeg4kj/av/ColorTransferCharacteristic;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_colorTransferCharacteristic__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->color_trc;
    return AVColorTransferCharacteristicToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorTransferCharacteristic
 * Signature: (Lffmpeg4kj/av/ColorTransferCharacteristic;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_colorTransferCharacteristic__Lffmpeg4kj_av_ColorTransferCharacteristic_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->color_trc = JavaToAVColorTransferCharacteristic(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorSpace
 * Signature: ()Lffmpeg4kj/av/ColorSpace;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_colorSpace__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->color_space;
    return AVColorSpaceToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    colorSpace
 * Signature: (Lffmpeg4kj/av/ColorSpace;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_colorSpace__Lffmpeg4kj_av_ColorSpace_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->color_space = JavaToAVColorSpace(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    chromaLocation
 * Signature: ()Lffmpeg4kj/av/ChromaLocation;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecParameters_chromaLocation__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    auto ret = nativeObject->getCodecParameters()->chroma_location;
    return AVChromaLocationToJava(env, ret);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    chromaLocation
 * Signature: (Lffmpeg4kj/av/ChromaLocation;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_chromaLocation__Lffmpeg4kj_av_ChromaLocation_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->chroma_location = JavaToAVChromaLocation(env, value);
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    videoDelay
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_videoDelay__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->video_delay;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    videoDelay
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_videoDelay__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->video_delay = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    channelLayout
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecParameters_channelLayout__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->channel_layout;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    channelLayout
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_channelLayout__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->channel_layout = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    channels
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_channels__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->channels;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    channels
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_channels__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->channels = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    sampleRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_sampleRate__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->sample_rate;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    sampleRate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_sampleRate__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->sample_rate = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    blockAlign
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_blockAlign__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->block_align;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    blockAlign
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_blockAlign__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->block_align = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    initialPadding
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_initialPadding__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->initial_padding;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    initialPadding
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_initialPadding__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->initial_padding = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    trailingPadding
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_trailingPadding__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->trailing_padding;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    trailingPadding
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_trailingPadding__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->trailing_padding = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    seekPreRoll
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecParameters_seekPreRoll__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    return nativeObject->getCodecParameters()->seek_preroll;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    seekPreRoll
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecParameters_seekPreRoll__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<CodecParametersNativeObject>(env, obj);
    nativeObject->getCodecParameters()->seek_preroll = value;
}

/**
 * Class:     ffmpeg4kj_av_CodecParameters
 * Method:    new
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecParameters_new
        (JNIEnv* env, jclass obj) {
    auto nativeObject = std::make_shared<CodecParametersNativeObject>();
    return make_java_native_object_ptr(nativeObject);
}
