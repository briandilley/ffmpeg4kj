
#include "ffmpeg4kj_av_Seconds.h"
#include "JniUtil.h"
#include "RationalNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Seconds
 * Method:    value
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Seconds_value
        (JNIEnv* env, jobject obj) {
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return 0;
    }
    return *value;
}

/**
 * Class:     ffmpeg4kj_av_Seconds
 * Method:    set
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Seconds_set__J
        (JNIEnv* env, jobject obj, jlong val) {
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return;
    }
    *value = (int64_t)val;
}

/**
 * Class:     ffmpeg4kj_av_Seconds
 * Method:    set
 * Signature: (Lffmpeg4kj/av/Rational;D)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Seconds_set__Lffmpeg4kj_av_Rational_2D
        (JNIEnv* env, jobject obj, jobject rational, jdouble val) {
    auto rationalNativeObject = get_native_object<RationalNativeObject>(env, rational);
    auto a = rationalNativeObject->getRational();
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return;
    }
    *value = val * av_q2d(av_inv_q(*a));
}

/**
 * Class:     ffmpeg4kj_av_Seconds
 * Method:    get
 * Signature: (Lffmpeg4kj/av/Rational;)D
 */
JNIEXPORT jdouble JNICALL Java_ffmpeg4kj_av_Seconds_get
        (JNIEnv* env, jobject obj, jobject rational) {
    auto rationalNativeObject = get_native_object<RationalNativeObject>(env, rational);
    auto a = rationalNativeObject->getRational();
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return 0;
    }
    return ((*value) * av_q2d(*a));
}
