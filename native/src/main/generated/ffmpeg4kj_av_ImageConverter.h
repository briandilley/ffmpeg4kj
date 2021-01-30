/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ffmpeg4kj_av_ImageConverter */

#ifndef _Included_ffmpeg4kj_av_ImageConverter
#define _Included_ffmpeg4kj_av_ImageConverter
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    convert
 * Signature: (Lffmpeg4kj/av/Frame;Lffmpeg4kj/av/Frame;II)I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_ImageConverter_convert
  (JNIEnv *, jobject, jobject, jobject, jint, jint);

/*
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_ImageConverter_free
  (JNIEnv *, jobject);

/*
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    createImageConverter
 * Signature: (IILffmpeg4kj/av/PixelFormat;IILffmpeg4kj/av/PixelFormat;I)Lffmpeg4kj/av/ImageConverter;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_ImageConverter_createImageConverter
  (JNIEnv *, jclass, jint, jint, jobject, jint, jint, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
