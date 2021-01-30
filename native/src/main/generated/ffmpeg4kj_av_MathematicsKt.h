/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ffmpeg4kj_av_MathematicsKt */

#ifndef _Included_ffmpeg4kj_av_MathematicsKt
#define _Included_ffmpeg4kj_av_MathematicsKt
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_gcd
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1gcd
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale
  (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_rnd
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1rnd
  (JNIEnv *, jclass, jlong, jlong, jlong, jint);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_q
 * Signature: (JLffmpeg4kj/av/Rational;Lffmpeg4kj/av/Rational;)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1q
  (JNIEnv *, jclass, jlong, jobject, jobject);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_rescale_q_rnd
 * Signature: (JLffmpeg4kj/av/Rational;Lffmpeg4kj/av/Rational;I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1rescale_1q_1rnd
  (JNIEnv *, jclass, jlong, jobject, jobject, jint);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_compare_ts
 * Signature: (JLffmpeg4kj/av/Rational;JLffmpeg4kj/av/Rational;)I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1compare_1ts
  (JNIEnv *, jclass, jlong, jobject, jlong, jobject);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_compare_mod
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1compare_1mod
  (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     ffmpeg4kj_av_MathematicsKt
 * Method:    av_add_stable
 * Signature: (Lffmpeg4kj/av/Rational;JLffmpeg4kj/av/Rational;J)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_MathematicsKt_av_1add_1stable
  (JNIEnv *, jclass, jobject, jlong, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif