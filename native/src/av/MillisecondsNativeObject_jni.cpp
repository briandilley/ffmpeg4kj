
#include "ffmpeg4kj_av_Milliseconds.h"
#include "JniUtil.h"
#include "RationalNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Milliseconds
 * Method:    value
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Milliseconds_value
        (JNIEnv* env, jobject obj) {
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return 0;
    }
    return *value;
}

/**
 * Class:     ffmpeg4kj_av_Milliseconds
 * Method:    set
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Milliseconds_set__J
        (JNIEnv* env, jobject obj, jlong val) {
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return;
    }
    *value = val;
}

/**
 * Class:     ffmpeg4kj_av_Milliseconds
 * Method:    set
 * Signature: (Lffmpeg4kj/av/Rational;J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Milliseconds_set__Lffmpeg4kj_av_Rational_2J
        (JNIEnv* env, jobject obj, jobject rational, jlong val) {
    auto rationalNativeObject = get_native_object<RationalNativeObject>(env, rational);
    auto a = rationalNativeObject->getRational();
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return;
    }
    *value = ((double)val / 1000) * av_q2d(av_inv_q(*a));
}

/**
 * Class:     ffmpeg4kj_av_Milliseconds
 * Method:    get
 * Signature: (Lffmpeg4kj/av/Rational;)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Milliseconds_get
        (JNIEnv* env, jobject obj, jobject rational) {
    auto rationalNativeObject = get_native_object<RationalNativeObject>(env, rational);
    auto a = rationalNativeObject->getRational();
    auto* value = get_native_state_ptr<int64_t>(env, obj);
    if (value == nullptr) {
        THROW_NULL_POINTER_EXCEPTION_JAVA(env, "native value is null");
        return 0;
    }
    return ((*value) * av_q2d(*a)) * 1000;
}
