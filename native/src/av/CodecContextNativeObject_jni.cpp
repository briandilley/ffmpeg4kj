
#include "ffmpeg4kj_av_CodecContext.h"
#include "JniUtil.h"
#include "CodecParametersNativeObject.h"
#include "RationalNativeObject.h"
#include "CodecContextNativeObject.h"

using namespace ffmpeg4kj::util;

static AVCodecContext* getAVCodecContext(JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredCodecContext();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return nullptr;
    }
}

#define withAVCodecContextReturn(body) \
    AVCodecContext* context = getAVCodecContext(env, obj); \
    if (context == nullptr) { \
        return 0; \
    } \
    body

#define withAVCodecContext(body) \
    AVCodecContext* context = getAVCodecContext(env, obj); \
    if (context == nullptr) { \
        return; \
    } \
    body

#define withAVCodecContextRational(body) \
    withAVCodecContextReturn( \
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(&body); \
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME); \
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V"); \
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject)));

/**
* Class:     ffmpeg4kj_av_CodecContext
* Method:    codec
* Signature: ()Lffmpeg4kj/av/Codec;
*/
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_codec
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    return nativeObject->getReference("codec", [nativeObject, env]() {
        try {
            auto codecNativeObject = nativeObject->getRequiredCodec();
            static jclass returnClazz = jni_FindClass(env, returnClazz, CodecNativeObject_JAVA_TYPE_NAME);
            static jmethodID cstr = jni_GetMethodId(env, returnClazz, cstr, "<init>", "(J)V");
            return env->NewObject(returnClazz, cstr, make_java_native_object_ptr(codecNativeObject));
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        }
        return (jobject)nullptr;
    });
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    isOpen
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_CodecContext_isOpen
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    return nativeObject->isOpen();
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    setParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_setParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
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
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    getParameters
 * Signature: (Lffmpeg4kj/av/CodecParameters;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_getParameters
        (JNIEnv* env, jobject obj, jobject params) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
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
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    open
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_open
        (JNIEnv* env, jobject obj, jstring openOptions) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    auto openOptionsString = openOptions != nullptr
             ? get_utf8_string_from_java(env, openOptions)
             : "";
    try {
        nativeObject->open(openOptionsString);
    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    nativeObject->free();
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    allocateExtraData
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_allocateExtraData
        (JNIEnv* env, jobject obj, jint size) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    try {
        nativeObject->allocateExtraData(size);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    deallocateExtraData
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_deallocateExtraData
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    try {
        nativeObject->deallocateExtraData();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    extradata
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_extradata__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    if (nativeObject->getRequiredCodecContext()->extradata_size <= 0
        || nativeObject->getRequiredCodecContext()->extradata == nullptr) {
        return (jobject)nullptr;
    }
    return env->NewDirectByteBuffer(
            nativeObject->getRequiredCodecContext()->extradata,
            nativeObject->getRequiredCodecContext()->extradata_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    extradata
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_extradata__Ljava_nio_ByteBuffer_2
        (JNIEnv* env, jobject obj, jobject byteBuffer) {
    auto nativeObject = get_native_object<CodecContextNativeObject>(env, obj);
    if (byteBuffer == nullptr) {
        nativeObject->getRequiredCodecContext()->extradata = nullptr;
        nativeObject->getRequiredCodecContext()->extradata_size = 0;
        return;
    }
    void* buff = get_direct_buffer_address_at_position(env, byteBuffer);
    int remaining = get_direct_buffer_remaining(env, byteBuffer);
    nativeObject->getRequiredCodecContext()->extradata = (uint8_t*)buff;
    nativeObject->getRequiredCodecContext()->extradata_size = remaining;
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecType
 * Signature: ()Lffmpeg4kj/av/MediaType;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_codecType__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVMediaTypeToJava(env, context->codec_type));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecType
 * Signature: (Lffmpeg4kj/av/MediaType;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_codecType__Lffmpeg4kj_av_MediaType_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->codec_type = JavaToAVMediaType(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_codecId__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVCodecIDToJava(env, context->codec_id));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_codecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->codec_id = JavaToAVCodecID(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecTag
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_codecTag__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->codec_tag);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codecTag
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_codecTag__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->codec_tag = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitRate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecContext_bitRate__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->bit_rate);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitRate
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bitRate__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVCodecContext(context->bit_rate = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitRateTolerance
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_bitRateTolerance__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->bit_rate_tolerance);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitRateTolerance
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bitRateTolerance__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->bit_rate_tolerance = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    globalQuality
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_globalQuality__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->global_quality);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    globalQuality
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_globalQuality__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->global_quality = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    compressionLevel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_compressionLevel__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->compression_level);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    compressionLevel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_compressionLevel__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->compression_level = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    flags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_flags__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->flags);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    flags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_flags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->flags = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    flags2
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_flags2__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->flags2);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    flags2
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_flags2__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->flags2 = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    timeBase
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_timeBase
        (JNIEnv* env, jobject obj) {
    withAVCodecContextRational(context->time_base);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    ticksPerFrame
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_ticksPerFrame__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->ticks_per_frame);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    ticksPerFrame
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_ticksPerFrame__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->ticks_per_frame = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    delay
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_delay__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->delay);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    delay
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_delay__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->delay = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    width
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_width__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->width);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    width
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_width__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->width = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    height
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_height__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->height);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    height
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_height__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->height = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codedWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_codedWidth__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->coded_width);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codedWidth
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_codedWidth__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->coded_width = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codedHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_codedHeight__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->coded_height);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    codedHeight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_codedHeight__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->coded_height = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    gopSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_gopSize__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->gop_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    gopSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_gopSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->gop_size = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    pixelFormat
 * Signature: ()Lffmpeg4kj/av/PixelFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_pixelFormat__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVPixelFormatToJava(env, context->pix_fmt));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    pixelFormat
 * Signature: (Lffmpeg4kj/av/PixelFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_pixelFormat__Lffmpeg4kj_av_PixelFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->pix_fmt = JavaToAVPixelFormat(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxBFrames
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_maxBFrames__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->max_b_frames);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxBFrames
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_maxBFrames__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->max_b_frames = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    quantFactor
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_bQuantFactor__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->b_quant_factor);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    quantFactor
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bQuantFactor__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->b_quant_factor = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bQuantOffset
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_bQuantOffset__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->b_quant_offset);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bQuantOffset
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bQuantOffset__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->b_quant_offset = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    iQuantFactor
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_iQuantFactor__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->i_quant_factor);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    iQuantFactor
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_iQuantFactor__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->i_quant_factor = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    iQuantOffset
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_iQuantOffset__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->i_quant_offset);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    iQuantOffset
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_iQuantOffset__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->i_quant_offset = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    lumiMasking
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_lumiMasking__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->lumi_masking);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    lumiMasking
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_lumiMasking__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->lumi_masking = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    temporalCplxMasking
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_temporalCplxMasking__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->temporal_cplx_masking);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    temporalCplxMasking
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_temporalCplxMasking__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->temporal_cplx_masking = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    spacialCplxMasking
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_spacialCplxMasking__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->spatial_cplx_masking);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    spacialCplxMasking
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_spacialCplxMasking__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->spatial_cplx_masking = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    pMasking
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_pMasking__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->p_masking);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    pMasking
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_pMasking__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->p_masking = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    darkMasking
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_darkMasking__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->dark_masking);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    darkMasking
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_darkMasking__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->dark_masking = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sliceCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_sliceCount__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->slice_count);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sliceCount
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_sliceCount__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->slice_count = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sampleAspectRatio
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_sampleAspectRatio
        (JNIEnv* env, jobject obj) {
    withAVCodecContextRational(context->sample_aspect_ratio);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meCmp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_meCmp__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->me_cmp);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meCmp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_meCmp__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->me_cmp = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meSubCmp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_meSubCmp__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->me_sub_cmp);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meSubCmp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_meSubCmp__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->me_sub_cmp = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbCmp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mbCmp__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->mb_cmp);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbCmp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mbCmp__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->mb_cmp = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    ildctCmp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_ildctCmp__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->ildct_cmp);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    ildctCmp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_ildctCmp__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->ildct_cmp = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    diaSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_diaSize__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->dia_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    diaSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_diaSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->dia_size = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    lastPredictorCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_lastPredictorCount__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->last_predictor_count);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    lastPredictorCount
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_lastPredictorCount__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->last_predictor_count = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mePreCmp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mePreCmp__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->me_pre_cmp);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mePreCmp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mePreCmp__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->me_pre_cmp = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    preDiaSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_preDiaSize__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->pre_dia_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    preDiaSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_preDiaSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->pre_dia_size = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meSubpelQuality
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_meSubpelQuality__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->me_subpel_quality);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meSubpelQuality
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_meSubpelQuality__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->me_subpel_quality = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meRange
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_meRange__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->me_range);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    meRange
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_meRange__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->me_range = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sliceFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_sliceFlags__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->slice_flags);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sliceFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_sliceFlags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->slice_flags = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbDecision
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mbDecision__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->mb_decision);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbDecision
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mbDecision__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->mb_decision = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    intraDcPrecision
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_intraDcPrecision__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->intra_dc_precision);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    intraDcPrecision
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_intraDcPrecision__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->intra_dc_precision = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipTop
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_skipTop__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->skip_top);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipTop
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipTop__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->skip_top = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipBottom
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_skipBottom__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->skip_bottom);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipBottom
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipBottom__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->skip_bottom = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbLmin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mbLmin__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->mb_lmin);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbLmin
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mbLmin__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->mb_lmin = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbLmax
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mbLmax__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->mb_lmax);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mbLmax
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mbLmax__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->mb_lmax = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bidirRefine
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_bidirRefine__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->bidir_refine);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bidirRefine
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bidirRefine__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->bidir_refine = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    keyintMin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_keyintMin__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->keyint_min);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    keyintMin
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_keyintMin__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->keyint_min = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    refs
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_refs__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->refs);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    refs
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_refs__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->refs = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mv0Threshoold
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_mv0Threshoold__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->mv0_threshold);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    mv0Threshoold
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_mv0Threshoold__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->mv0_threshold = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorPrimaries
 * Signature: ()Lffmpeg4kj/av/ColorPrimaries;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_colorPrimaries__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVColorPrimariesToJava(env, context->color_primaries));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorPrimaries
 * Signature: (Lffmpeg4kj/av/ColorPrimaries;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_colorPrimaries__Lffmpeg4kj_av_ColorPrimaries_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->color_primaries = JavaToAVColorPrimaries(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorTrc
 * Signature: ()Lffmpeg4kj/av/ColorTransferCharacteristic;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_colorTrc__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVColorTransferCharacteristicToJava(env, context->color_trc));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorTrc
 * Signature: (Lffmpeg4kj/av/ColorTransferCharacteristic;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_colorTrc__Lffmpeg4kj_av_ColorTransferCharacteristic_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->color_trc = JavaToAVColorTransferCharacteristic(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorSpace
 * Signature: ()Lffmpeg4kj/av/ColorSpace;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_colorSpace__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVColorSpaceToJava(env, context->colorspace));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorSpace
 * Signature: (Lffmpeg4kj/av/ColorSpace;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_colorSpace__Lffmpeg4kj_av_ColorSpace_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->colorspace = JavaToAVColorSpace(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorRange
 * Signature: ()Lffmpeg4kj/av/ColorRange;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_colorRange__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVColorRangeToJava(env, context->color_range));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    colorRange
 * Signature: (Lffmpeg4kj/av/ColorRange;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_colorRange__Lffmpeg4kj_av_ColorRange_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->color_range = JavaToAVColorRange(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    chromaSampleLocation
 * Signature: ()Lffmpeg4kj/av/ChromaLocation;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_chromaSampleLocation__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVChromaLocationToJava(env, context->chroma_sample_location));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    chromaSampleLocation
 * Signature: (Lffmpeg4kj/av/ChromaLocation;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_chromaSampleLocation__Lffmpeg4kj_av_ChromaLocation_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->chroma_sample_location = JavaToAVChromaLocation(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    slices
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_slices__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->slices);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    slices
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_slices__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->slices = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    fieldOrder
 * Signature: ()Lffmpeg4kj/av/FieldOrder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_fieldOrder__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVFieldOrderToJava(env, context->field_order));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    fieldOrder
 * Signature: (Lffmpeg4kj/av/FieldOrder;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_fieldOrder__Lffmpeg4kj_av_FieldOrder_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->field_order = JavaToAVFieldOrder(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sampleRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_sampleRate__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->sample_rate);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sampleRate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_sampleRate__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->sample_rate = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    channels
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_channels__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->channels);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    channels
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_channels__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->channels = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sampleFmt
 * Signature: ()Lffmpeg4kj/av/SampleFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_sampleFmt__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVSampleFormatToJava(env, context->sample_fmt));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    sampleFmt
 * Signature: (Lffmpeg4kj/av/SampleFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_sampleFmt__Lffmpeg4kj_av_SampleFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->sample_fmt = JavaToAVSampleFormat(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    frameSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_frameSize
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->frame_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    frameNumber
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_frameNumber
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->frame_number);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    cutoff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_cutoff__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->cutoff);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    cutoff
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_cutoff__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->cutoff = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    blockAlign
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_blockAlign__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->block_align);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    blockAlign
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_blockAlign__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->block_align = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    channelLayout
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecContext_channelLayout__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->channel_layout);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    channelLayout
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_channelLayout__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVCodecContext(context->channel_layout = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    requestChannelLayout
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecContext_requestChannelLayout__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->request_channel_layout);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    requestChannelLayout
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_requestChannelLayout__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVCodecContext(context->request_channel_layout = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    requestSampleFormat
 * Signature: ()Lffmpeg4kj/av/SampleFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_requestSampleFormat__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVSampleFormatToJava(env, context->request_sample_fmt));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    requestSampleFormat
 * Signature: (Lffmpeg4kj/av/SampleFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_requestSampleFormat__Lffmpeg4kj_av_SampleFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->request_sample_fmt = JavaToAVSampleFormat(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qCompress
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_qCompress__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->qcompress);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qCompress
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_qCompress__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->qcompress = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qBlur
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_qBlur__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->qblur);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qBlur
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_qBlur__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->qblur = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qMin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_qMin__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->qmin);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qMin
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_qMin__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->qmin = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qMax
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_qMax__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->qmax);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    qMax
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_qMax__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->qmax = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxQDiff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_maxQDiff__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->max_qdiff);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxQDiff
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_maxQDiff__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->max_qdiff = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcBufferSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_rcBufferSize__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_buffer_size);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcBufferSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcBufferSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->rc_buffer_size = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMaxRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_rcMaxRate__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_max_rate);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMaxRate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcMaxRate__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->rc_max_rate = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMinRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_rcMinRate__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_min_rate);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMinRate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcMinRate__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->rc_min_rate = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMaxAvailableVbvUse
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_rcMaxAvailableVbvUse__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_max_available_vbv_use);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMaxAvailableVbvUse
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcMaxAvailableVbvUse__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->rc_max_available_vbv_use = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMinVbvOverflowUse
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_ffmpeg4kj_av_CodecContext_rcMinVbvOverflowUse__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_min_vbv_overflow_use);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcMinVbvOverflowUse
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcMinVbvOverflowUse__F
        (JNIEnv* env, jobject obj, jfloat value) {
    withAVCodecContext(context->rc_min_vbv_overflow_use = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcInitialBufferOccupancy
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_rcInitialBufferOccupancy__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->rc_initial_buffer_occupancy);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    rcInitialBufferOccupancy
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_rcInitialBufferOccupancy__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->rc_initial_buffer_occupancy = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    trellis
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_trellis__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->trellis);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    trellis
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_trellis__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->trellis = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    workaroundBugs
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_workaroundBugs__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->workaround_bugs);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    workaroundBugs
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_workaroundBugs__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->workaround_bugs = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    strictStdCompliance
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_strictStdCompliance__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->strict_std_compliance);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    strictStdCompliance
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_strictStdCompliance__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->strict_std_compliance = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    errorConcealment
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_errorConcealment__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->error_concealment);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    errorConcealment
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_errorConcealment__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->error_concealment = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    debug
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_debug__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->debug);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    debug
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_debug__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->debug = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    errRecognition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_errRecognition__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->err_recognition);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    errRecognition
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_errRecognition__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->err_recognition = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    reorderedOpaque
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecContext_reorderedOpaque__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->reordered_opaque);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    reorderedOpaque
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_reorderedOpaque__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVCodecContext(context->reordered_opaque = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    dctAlgo
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_dctAlgo__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->dct_algo);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    dctAlgo
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_dctAlgo__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->dct_algo = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    idctAlgo
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_idctAlgo__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->idct_algo);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    idctAlgo
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_idctAlgo__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->idct_algo = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitsPerCodedSample
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_bitsPerCodedSample__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->bits_per_coded_sample);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitsPerCodedSample
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bitsPerCodedSample__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->bits_per_coded_sample = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitsPerRawSample
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_bitsPerRawSample__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->bits_per_raw_sample);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    bitsPerRawSample
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_bitsPerRawSample__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->bits_per_raw_sample = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    threadCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_threadCount__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->thread_count);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    threadCount
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_threadCount__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->thread_count = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    threadType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_threadType__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->thread_type);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    threadType
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_threadType__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->thread_type = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    activeThreadType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_activeThreadType
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->active_thread_type);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    nsseWeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_nsseWeight__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->nsse_weight);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    nsseWeight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_nsseWeight__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->nsse_weight = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    profile
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_profile__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->profile);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    profile
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_profile__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->profile = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    level
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_level__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->level);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    level
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_level__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->level = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipLoopFilter
 * Signature: ()Lffmpeg4kj/av/Discard;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_skipLoopFilter__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVDiscardToJava(env, context->skip_loop_filter));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipLoopFilter
 * Signature: (Lffmpeg4kj/av/Discard;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipLoopFilter__Lffmpeg4kj_av_Discard_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->skip_loop_filter = JavaToAVDiscard(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipIdct
 * Signature: ()Lffmpeg4kj/av/Discard;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_skipIdct__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVDiscardToJava(env, context->skip_idct));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipIdct
 * Signature: (Lffmpeg4kj/av/Discard;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipIdct__Lffmpeg4kj_av_Discard_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->skip_idct = JavaToAVDiscard(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipFrame
 * Signature: ()Lffmpeg4kj/av/Discard;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_skipFrame__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVDiscardToJava(env, context->skip_frame));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipFrame
 * Signature: (Lffmpeg4kj/av/Discard;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipFrame__Lffmpeg4kj_av_Discard_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->skip_frame = JavaToAVDiscard(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    initialPadding
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_initialPadding__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->initial_padding);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    initialPadding
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_initialPadding__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->initial_padding = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    frameRate
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_frameRate
        (JNIEnv* env, jobject obj) {
    withAVCodecContextRational(context->framerate);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    swPixFmt
 * Signature: ()Lffmpeg4kj/av/PixelFormat;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_swPixFmt__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return AVPixelFormatToJava(env, context->sw_pix_fmt));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    swPixFmt
 * Signature: (Lffmpeg4kj/av/PixelFormat;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_swPixFmt__Lffmpeg4kj_av_PixelFormat_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVCodecContext(context->sw_pix_fmt = JavaToAVPixelFormat(env, value));
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    pktTimeBase
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_CodecContext_pktTimeBase
        (JNIEnv* env, jobject obj) {
    withAVCodecContextRational(context->pkt_timebase);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipAlpha
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_skipAlpha__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->skip_alpha);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    skipAlpha
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_skipAlpha__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->skip_alpha = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    seekPreroll
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_seekPreroll__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->seek_preroll);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    seekPreroll
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_seekPreroll__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->seek_preroll = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    trailingPadding
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_trailingPadding__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->trailing_padding);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    trailingPadding
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_trailingPadding__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->trailing_padding = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxPixels
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_CodecContext_maxPixels__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->max_pixels);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    maxPixels
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_maxPixels__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVCodecContext(context->max_pixels = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    hwAccelFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_hwAccelFlags__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->hwaccel_flags);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    hwAccelFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_hwAccelFlags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->hwaccel_flags = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    applyCropping
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_applyCropping__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->apply_cropping);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    applyCropping
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_applyCropping__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->apply_cropping = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    extraHwFrames
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_extraHwFrames__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->extra_hw_frames);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    extraHwFrames
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_extraHwFrames__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->extra_hw_frames = value);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    discardDamagedPercentage
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_CodecContext_discardDamagedPercentage__
        (JNIEnv* env, jobject obj) {
    withAVCodecContextReturn(return context->initial_padding);
}

/**
 * Class:     ffmpeg4kj_av_CodecContext
 * Method:    discardDamagedPercentage
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_CodecContext_discardDamagedPercentage__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVCodecContext(context->initial_padding = value);
}
