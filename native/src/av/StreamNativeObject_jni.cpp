
#include "ffmpeg4kj_av_Stream.h"
#include "JniUtil.h"
#include "StreamNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "CodecNativeObject.h"
#include "EncoderNativeObject.h"
#include "DecoderNativeObject.h"
#include "RationalNativeObject.h"
#include "TimeNativeObjects.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    getEncoderCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_getEncoderCodec
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("getEncoderCodec", [nativeObject, env]() {
        try {
            auto retObject = nativeObject->getEncoderCodec();
            static jclass retClazz = jni_FindClass(env, retClazz, CodecNativeObject_JAVA_TYPE_NAME);
            static jmethodID retConstructor = jni_GetMethodId(env, retClazz, retConstructor, "<init>", "(J)V");
            return env->NewObject(retClazz, retConstructor, make_java_native_object_ptr(retObject));
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        } catch(Poco::RuntimeException& e) {
            THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    getDecoderCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_getDecoderCodec
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("getDecoderCodec", [nativeObject, env]() {
        try {
            auto retObject = nativeObject->getDecoderCodec();
            static jclass retClazz = jni_FindClass(env, retClazz, CodecNativeObject_JAVA_TYPE_NAME);
            static jmethodID retConstructor = jni_GetMethodId(env, retClazz, retConstructor, "<init>", "(J)V");
            return env->NewObject(retClazz, retConstructor, make_java_native_object_ptr(retObject));
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        } catch(Poco::RuntimeException& e) {
            THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    createEncoder
 * Signature: ()Lffmpeg4kj/av/Encoder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_createEncoder
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    try {
        auto retObject = nativeObject->createEncoder();
        static jclass retClazz = jni_FindClass(env, retClazz, EncoderNativeObject_JAVA_TYPE_NAME);
        static jmethodID retConstructor = jni_GetMethodId(env, retClazz, retConstructor, "<init>", "(J)V");
        return env->NewObject(retClazz, retConstructor, make_java_native_object_ptr(retObject));
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    createDecoder
 * Signature: ()Lffmpeg4kj/av/Decoder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_createDecoder
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    try {
        auto retObject = nativeObject->createDecoder();
        static jclass retClazz = jni_FindClass(env, retClazz, DecoderNativeObject_JAVA_TYPE_NAME);
        static jmethodID retConstructor = jni_GetMethodId(env, retClazz, retConstructor, "<init>", "(J)V");
        return env->NewObject(retClazz, retConstructor, make_java_native_object_ptr(retObject));
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    id
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Stream_id
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->id;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    index
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Stream_index
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->index;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    codecParameters
 * Signature: ()Lffmpeg4kj/av/CodecParameters;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_codecParameters
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getReference("codecParameters", [nativeObject, env]() {
        auto codecParametersNativeObject = nativeObject->getParameters();
        static jclass paramsClazz = jni_FindClass(env, paramsClazz, CodecParametersNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, paramsClazz, cstr, "<init>", "(J)V");
        return env->NewObject(paramsClazz, cstr, make_java_native_object_ptr(codecParametersNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    timeBase
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_timeBase
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("timeBase", [nativeObject, env]() {
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(
                &nativeObject->getStream()->time_base);
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V");
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    numberOfFrames
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Stream_numberOfFrames__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->nb_frames;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    numberOfFrames
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Stream_numberOfFrames__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    nativeObject->getStream()->nb_frames = value;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    disposition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Stream_disposition__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->disposition;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    disposition
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Stream_disposition__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    nativeObject->getStream()->disposition = value;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    discard
 * Signature: ()Lffmpeg4kj/av/Discard;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_discard__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return AVDiscardToJava(env, nativeObject->getStream()->discard);
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    discard
 * Signature: (Lffmpeg4kj/av/Discard;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Stream_discard__Lffmpeg4kj_av_Discard_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    nativeObject->getStream()->discard = JavaToAVDiscard(env, value);
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    sampleAspectRatio
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_sampleAspectRatio
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("sampleAspectRatio", [nativeObject, env]() {
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(
                &nativeObject->getStream()->sample_aspect_ratio);
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V");
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    averageFrameRate
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_averageFrameRate
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("averageFrameRate", [nativeObject, env]() {
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(
                &nativeObject->getStream()->avg_frame_rate);
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V");
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    realFrameRate
 * Signature: ()Lffmpeg4kj/av/Rational;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_realFrameRate
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);

    return nativeObject->getReference("realFrameRate", [nativeObject, env]() {
        auto rationalNativeObject = std::make_shared<RationalNativeObject>(
                &nativeObject->getStream()->r_frame_rate);
        static jclass rationalClazz = jni_FindClass(env, rationalClazz, RationalNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, rationalClazz, cstr, "<init>", "(J)V");
        return env->NewObject(rationalClazz, cstr, make_java_native_object_ptr(rationalNativeObject));
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    startTime
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Stream_startTime__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->start_time;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    startTime
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Stream_startTime__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    nativeObject->getStream()->start_time = value;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    duration
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Stream_duration__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getStream()->duration;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    duration
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Stream_duration__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    nativeObject->getStream()->duration = value;
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    startTimeSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_startTimeSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getReference("startTimeSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong)&nativeObject->getStream()->start_time);
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    startTimeMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_startTimeMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getReference("startTimeMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong)&nativeObject->getStream()->start_time);
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    durationSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_durationSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getReference("durationSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");

        try {
            return env->NewObject(clazz, ctr, (jlong)&nativeObject->getStream()->duration);
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Stream
 * Method:    durationMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Stream_durationMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<StreamNativeObject>(env, obj);
    return nativeObject->getReference("durationMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getStream()->duration);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}
