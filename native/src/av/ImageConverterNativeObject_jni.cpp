
#include "ffmpeg4kj_av_ImageConverter.h"
#include "JniUtil.h"
#include "ImageConverterNativeObject.h"
#include "FrameNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    convert
 * Signature: (Lffmpeg4kj/av/Frame;Lffmpeg4kj/av/Frame;II)I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_ImageConverter_convert
        (JNIEnv* env, jobject obj, jobject src, jobject dst, jint srcSlice, jint srcSliceHeight) {
    auto nativeObject = get_native_object<ImageConverterNativeObject>(env, obj);
    auto srcNativeObject = get_native_object<FrameNativeObject>(env, src);
    auto dstNativeObject = get_native_object<FrameNativeObject>(env, dst);
    try {
        return nativeObject->convert(srcNativeObject, dstNativeObject, srcSlice, srcSliceHeight);
    } catch (Poco::IllegalStateException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
        return 0;
    } catch (Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_ImageConverter_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ImageConverterNativeObject>(env, obj);
    nativeObject->free();
}

/**
 * Class:     ffmpeg4kj_av_ImageConverter
 * Method:    createImageConverter
 * Signature: (IILffmpeg4kj/av/PixelFormat;IILffmpeg4kj/av/PixelFormat;I)Lffmpeg4kj/av/ImageConverter;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_ImageConverter_createImageConverter
        (JNIEnv* env, jclass clazz,
                jint srcW, jint srcH, jobject srcFormat,
                jint dstW, jint dstH, jobject dstFormat,
                jint flags) {

    try {
        auto nativeObject = ImageConverterNativeObject::createNew(
                srcW, srcH, JavaToAVPixelFormat(env, srcFormat),
                dstW, dstH, JavaToAVPixelFormat(env, dstFormat),
                flags);
        static jclass retClazz = jni_FindClass(env, retClazz, ImageConverterNativeObject_JAVA_TYPE_NAME);
        static jmethodID retCstr = jni_GetMethodId(env, retClazz, retCstr, "<init>", "(J)V");
        return env->NewObject(retClazz, retCstr, make_java_native_object_ptr(nativeObject));
    } catch (Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }

}
