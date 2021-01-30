/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ffmpeg4kj_av_Buffer */

#ifndef _Included_ffmpeg4kj_av_Buffer
#define _Included_ffmpeg4kj_av_Buffer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    buffer
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Buffer_buffer
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Buffer_size
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    writable
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Buffer_writable
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    makeWritable
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Buffer_makeWritable
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    ref
 * Signature: ()Lffmpeg4kj/av/Buffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Buffer_ref
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    unref
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Buffer_unref
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    refCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Buffer_refCount
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_Buffer
 * Method:    new
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Buffer_new
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
