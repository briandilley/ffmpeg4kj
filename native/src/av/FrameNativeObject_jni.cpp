
#include "ffmpeg4kj_av_Frame.h"
#include "JniUtil.h"
#include "FrameNativeObject.h"
#include "BufferNativeObject.h"
#include "TimeNativeObjects.h"

using namespace ffmpeg4kj::util;

/*
 * Class:     ffmpeg4kj_av_Frame
 * Method:    allocateBuffers
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_allocateBuffers
        (JNIEnv* env, jobject obj, jint align) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->allocateBuffers(align);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    setBuffer
 * Signature: (ILffmpeg4kj/av/Buffer;I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_setBuffer
        (JNIEnv* env, jobject obj, jint index, jobject buffer, jint lineSize) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    auto bufferNativeObject = get_native_object<BufferNativeObject>(env, buffer);
    try {
        nativeObject->setBuffer(index, bufferNativeObject, lineSize);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    getBuffer
 * Signature: (I)Lffmpeg4kj/av/Buffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_getBuffer
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        auto bufferNativeObject = nativeObject->getBuffer(index);
        if (bufferNativeObject == nullptr) {
            return (jobject)nullptr;
        }

        static jclass clazz = jni_FindClass(env, clazz, BufferNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");

        return env->NewObject(clazz, ctr, make_java_native_object_ptr(bufferNativeObject));
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    setData
 * Signature: (ILjava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_setData
        (JNIEnv* env, jobject obj, jint index, jobject byteBuffer, jint lineSize) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        if (byteBuffer == nullptr) {
            nativeObject->setData(index, nullptr, lineSize);
            return;
        }
        void* buf = get_direct_buffer_address_at_position(env, byteBuffer);
        nativeObject->setData(index, (uint8_t*)buf, lineSize);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    getData
 * Signature: (I)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_getData
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        if (nativeObject->getData(index) == nullptr) {
            return (jobject)nullptr;
        } else if (nativeObject->getRequiredFrame()->linesize[index] <= 0) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, "Line size for the given index is <= 0");
            return (jobject)nullptr;
        } else if (nativeObject->getRequiredFrame()->height <= 0) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, "Height <= 0");
            return (jobject)nullptr;
        }
        return env->NewDirectByteBuffer(
                nativeObject->getData(index),
                nativeObject->getRequiredFrame()->linesize[index] * nativeObject->getRequiredFrame()->height);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    getLineSize
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_getLineSize
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->linesize[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    format
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_format__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->format = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    format
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_format__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->format;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    pts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_pts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getRequiredFrame()->pts;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    pts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_pts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    nativeObject->getRequiredFrame()->pts = value;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_packetDts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getRequiredFrame()->pkt_dts;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_packetDts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    nativeObject->getRequiredFrame()->pkt_dts = value;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDuration
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_packetDuration__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getRequiredFrame()->pkt_duration;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDuration
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_packetDuration__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    nativeObject->getRequiredFrame()->pkt_duration = value;
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    ptsSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_ptsSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("ptsSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong)&nativeObject->getRequiredFrame()->pts);
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDtsSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_packetDtsSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("packetDtsSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getRequiredFrame()->pkt_dts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDurationSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_packetDurationSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("packetDurationSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getRequiredFrame()->pkt_duration);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    ptsMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_ptsMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("ptsMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getRequiredFrame()->pts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDtsMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_packetDtsMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("packetDtsMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getRequiredFrame()->pkt_dts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetDurationMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_packetDurationMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    return nativeObject->getReference("packetDurationMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getRequiredFrame()->pkt_duration);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    flags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_flags__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->flags = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    flags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_flags__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->flags;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetPos
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_packetPos__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->pkt_pos = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetPos
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_packetPos__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->pkt_pos;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_packetSize__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->pkt_size = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    packetSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_packetSize__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->pkt_size;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    ref
 * Signature: (Lffmpeg4kj/av/Frame;)Lffmpeg4kj/av/Frame;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Frame_ref
        (JNIEnv* env, jobject obj, jobject frame) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    auto frameObject = get_native_object<FrameNativeObject>(env, frame);

    try {
        frameObject = nativeObject->ref(frameObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }

    static jclass clazz = jni_FindClass(env, clazz, FrameNativeObject_JAVA_TYPE_NAME);
    static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");

    return env->NewObject(clazz, ctr, make_java_native_object_ptr(frameObject));
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    unref
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_unref
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->unref();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->free();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    width
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_width__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->width = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    width
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_width__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->width;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    height
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_height__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->height = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    height
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_height__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->height;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    keyFrame
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_keyFrame__Z
        (JNIEnv* env, jobject obj, jboolean value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->key_frame = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    keyFrame
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Frame_keyFrame__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->key_frame;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return false;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    pictureType
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_pictureType__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->pict_type = (AVPictureType)value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    pictureType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_pictureType__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->pict_type;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    quality
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_quality__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->quality = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    quality
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_quality__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->quality;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropTop
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_cropTop__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->crop_top = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropTop
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_cropTop__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->crop_top;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropLeft
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_cropLeft__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->crop_left = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropLeft
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_cropLeft__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->crop_left;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropRight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_cropRight__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->crop_right = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropRight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_cropRight__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->crop_right;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropBottom
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_cropBottom__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->crop_bottom = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    cropBottom
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_cropBottom__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->crop_bottom;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    numberOfSamples
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_numberOfSamples__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->nb_samples = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    numberOfSamples
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_numberOfSamples__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->nb_samples;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    sampleRate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_sampleRate__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->sample_rate = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    sampleRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_sampleRate__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->sample_rate;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    channelLayout
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_channelLayout__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->channel_layout = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    channelLayout
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_channelLayout__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->channel_layout;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    numberOfChannels
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Frame_numberOfChannels__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        nativeObject->getRequiredFrame()->channels = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    numberOfChannels
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Frame_numberOfChannels__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FrameNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFrame()->channels;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Frame
 * Method:    new
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Frame_new
        (JNIEnv* env, jclass obj) {
    return make_java_native_object_ptr(FrameNativeObject::makeNew());
}
