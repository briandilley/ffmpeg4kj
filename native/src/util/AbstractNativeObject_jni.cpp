
#include "AbstractNativeObject.h"
#include "JniUtil.h"
#include "ffmpeg4kj_util_AbstractNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_util_AbstractNativeObject
 * Method:    referenceCount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_util_AbstractNativeObject_referenceCount
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_abstract_native_object(env, obj);
    return nativeObject == nullptr ? 0 : nativeObject.use_count();
}

/**
 * Class:     ffmpeg4kj_util_AbstractNativeObject
 * Method:    dispose$streamhub_native
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_util_AbstractNativeObject_dispose_00024streamhub_1native
        (JNIEnv* env, jclass clazz, jlong value) {

    if (value == 0) {
        poco_warning(getLogger(AbstractNativeObject_JAVA_TYPE_NAME),
                "avoiding disposing an object with a null native pointer");
        return;
    }

    try {
        poco_trace(getLogger(AbstractNativeObject_JAVA_TYPE_NAME), "disposing object");
        dispose_java_native_object_ptr(value);

    } catch(...) {
        string className = get_class_name(env, clazz);
        THROW_RUNTIME_EXCEPTION_JAVA(env, "Unable to dispose of a " + className);
        return;
    }
}
