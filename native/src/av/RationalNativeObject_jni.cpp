
#include "ffmpeg4kj_av_Rational.h"
#include "JniUtil.h"
#include "RationalNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Rational
 * Method:    num
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Rational_num__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<RationalNativeObject>(env, obj);
    return nativeObject->getRational()->num;
}

/**
 * Class:     ffmpeg4kj_av_Rational
 * Method:    num
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Rational_num__I
        (JNIEnv* env, jobject obj, jint num) {
    auto nativeObject = get_native_object<RationalNativeObject>(env, obj);
    nativeObject->getRational()->num = num;
}

/**
 * Class:     ffmpeg4kj_av_Rational
 * Method:    den
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Rational_den__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<RationalNativeObject>(env, obj);
    return nativeObject->getRational()->den;
}

/**
 * Class:     ffmpeg4kj_av_Rational
 * Method:    den
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Rational_den__I
        (JNIEnv* env, jobject obj, jint den) {
    auto nativeObject = get_native_object<RationalNativeObject>(env, obj);
    nativeObject->getRational()->den = den;
}

/**
 * Class:     ffmpeg4kj_av_Rational
 * Method:    new
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Rational_new
        (JNIEnv* env, jclass obj, jint num, jint den) {
    auto nativeObject = std::make_shared<RationalNativeObject>();
    nativeObject->getRational()->num = num;
    nativeObject->getRational()->den = den;
    return make_java_native_object_ptr(nativeObject);
}
