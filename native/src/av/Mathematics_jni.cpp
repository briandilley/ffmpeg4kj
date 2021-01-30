
#include "ffmpeg4kj_av_MathematicsKt.h"
#include "JniUtil.h"
#include "RationalNativeObject.h"

extern "C" {
#include <libavutil/rational.h>
#include <libavutil/mathematics.h>
}

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_gcd
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1gcd
        (JNIEnv* env, jclass clazz, jlong a, jlong b) {
    return av_gcd(a, b);
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale
        (JNIEnv* env, jclass clazz, jlong a , jlong b , jlong c) {
    return av_rescale(a, b, c);
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_rnd
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1rnd
        (JNIEnv* env, jclass clazz, jlong a, jlong b, jlong c, jint rnd) {
    return av_rescale_rnd(a, b, c, (AVRounding)rnd);
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_q
 * Signature: (JLffmpeg4kj/av/Rational;Lffmpeg4kj/av/Rational;)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1q
        (JNIEnv* env, jclass clazz, jlong a, jobject bq , jobject cq) {
    auto bqObject = get_native_object<RationalNativeObject>(env, bq);
    auto cqObject = get_native_object<RationalNativeObject>(env, cq);
    return av_rescale_q(a, *bqObject->getRational(), *cqObject->getRational());
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_q_rnd
 * Signature: (JLffmpeg4kj/av/Rational;Lffmpeg4kj/av/Rational;I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1q_1rnd
        (JNIEnv* env, jclass clazz, jlong a, jobject bq, jobject cq, jint rnd) {
    auto bqObject = get_native_object<RationalNativeObject>(env, bq);
    auto cqObject = get_native_object<RationalNativeObject>(env, cq);
    return av_rescale_q_rnd(a, *bqObject->getRational(), *cqObject->getRational(), (AVRounding)rnd);
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_compare_ts
 * Signature: (JLffmpeg4kj/av/Rational;JLffmpeg4kj/av/Rational;)I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1compare_1ts
        (JNIEnv* env, jclass clazz, jlong ts_a, jobject tb_a, jlong ts_b, jobject tb_b) {
    auto tb_aObject = get_native_object<RationalNativeObject>(env, tb_a);
    auto tb_bObject = get_native_object<RationalNativeObject>(env, tb_b);
    return av_compare_ts(ts_a, *tb_aObject->getRational(), ts_b, *tb_bObject->getRational());
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_compare_mod
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1compare_1mod
        (JNIEnv* env, jclass clazz, jlong ua, jlong b, jlong mod) {
    return av_compare_mod(ua, b, mod);
}

/**
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_add_stable
 * Signature: (Lffmpeg4kj/av/Rational;JLffmpeg4kj/av/Rational;J)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1add_1stable
        (JNIEnv* env, jclass clazz, jobject ts_tb, jlong ts, jobject inc_tb, jlong inc) {
    auto tb_aObject = get_native_object<RationalNativeObject>(env, ts_tb);
    auto inc_tbObject = get_native_object<RationalNativeObject>(env, inc_tb);
    return av_add_stable(*tb_aObject->getRational(), ts, *inc_tbObject->getRational(), inc);
}
