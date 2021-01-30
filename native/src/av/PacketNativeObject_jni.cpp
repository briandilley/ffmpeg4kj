
#include "ffmpeg4kj_av_Packet.h"
#include "JniUtil.h"
#include "PacketNativeObject.h"
#include "BufferNativeObject.h"
#include "TimeNativeObjects.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    rescaleTs
 * Signature: (Lffmpeg4kj/av/Rational;Lffmpeg4kj/av/Rational;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_rescaleTs
        (JNIEnv* env, jobject obj, jobject tbSrc, jobject tbDst) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    auto tbSrcNativeObject = get_native_object<RationalNativeObject>(env, obj);
    auto tbDstNativeObject = get_native_object<RationalNativeObject>(env, obj);
    nativeObject->rescale(tbDstNativeObject, tbDstNativeObject);
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    allocateBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_allocateBuffer
        (JNIEnv* env, jobject obj, jint size) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->allocateBuffer(size);
    } catch(Poco::RuntimeException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    shrinkBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_shrinkBuffer
        (JNIEnv* env, jobject obj, jint size) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->shrinkBuffer(size);
    } catch(Poco::RuntimeException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    growBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_growBuffer
        (JNIEnv* env, jobject obj, jint size) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->growBuffer(size);
    } catch(Poco::RuntimeException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    buffer
 * Signature: (Lffmpeg4kj/av/Buffer;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_buffer__Lffmpeg4kj_av_Buffer_2
        (JNIEnv* env, jobject obj, jobject buffer) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    auto bufferNativeObject = get_native_object<BufferNativeObject>(env, buffer);
    try {
        nativeObject->setBuffer(bufferNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    buffer
 * Signature: ()Lffmpeg4kj/av/Buffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_buffer__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        auto bufferNativeObject = nativeObject->getBuffer();
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
 * Class:     ffmpeg4kj_av_Packet
 * Method:    pts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_pts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    nativeObject->getPacket()->pts = value;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    pts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Packet_pts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    return nativeObject->getPacket()->pts;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    dts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_dts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    nativeObject->getPacket()->dts = value;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    dts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Packet_dts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    return nativeObject->getPacket()->dts;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    duration
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_duration__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    nativeObject->getPacket()->duration = value;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    duration
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Packet_duration__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    return nativeObject->getPacket()->duration;
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    ptsSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_ptsSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    return nativeObject->getReference("ptsSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong)&nativeObject->getPacket()->pts);
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject)nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    dtsSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_dtsSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);

    return nativeObject->getReference("dtsSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getPacket()->dts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    durationSeconds
 * Signature: ()Lffmpeg4kj/av/Seconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_durationSeconds
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);

    return nativeObject->getReference("durationSeconds", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, SecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");

        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getPacket()->duration);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    ptsMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_ptsMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);

    return nativeObject->getReference("ptsMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getPacket()->pts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    dtsMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_dtsMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);

    return nativeObject->getReference("dtsMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getPacket()->dts);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    durationMillis
 * Signature: ()Lffmpeg4kj/av/Milliseconds;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_durationMillis
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);

    return nativeObject->getReference("durationMillis", [nativeObject, env]() {
        static jclass clazz = jni_FindClass(env, clazz, MillisecondsNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        try {
            return env->NewObject(clazz, ctr, (jlong) &nativeObject->getPacket()->duration);
        } catch (Poco::IllegalStateException &e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
            return (jobject) nullptr;
        }
    });
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    ref
 * Signature: (Lffmpeg4kj/av/Packet;)Lffmpeg4kj/av/Packet;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_ref
        (JNIEnv* env, jobject obj, jobject packet) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    auto packetObject = get_native_object<PacketNativeObject>(env, packet);

    try {
        packetObject = nativeObject->ref(packetObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }

    static jclass clazz = jni_FindClass(env, clazz, PacketNativeObject_JAVA_TYPE_NAME);
    static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");

    return env->NewObject(clazz, ctr, make_java_native_object_ptr(packetObject));
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    unref
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_unref
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->unref();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_init
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->init();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    data
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_data__Ljava_nio_ByteBuffer_2
        (JNIEnv* env, jobject obj, jobject byteBuffer) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        if (byteBuffer == nullptr) {
            nativeObject->setData(nullptr, 0);
            return;
        }
        void* buf = get_direct_buffer_address_at_position(env, byteBuffer);
        int remaining = get_direct_buffer_remaining(env, byteBuffer);
        nativeObject->setData((uint8_t*)buf, remaining);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    data
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Packet_data__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        if (nativeObject->getPacket()->data == nullptr) {
            return (jobject)nullptr;
        }
        return env->NewDirectByteBuffer(
                nativeObject->getPacket()->data,
                nativeObject->getPacket()->size);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return (jobject)nullptr;
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Packet_dataSize
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        return nativeObject->getPacket()->size;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    streamIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_streamIndex__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->getPacket()->stream_index = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    streamIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Packet_streamIndex__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        return nativeObject->getPacket()->stream_index;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    flags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_flags__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->getPacket()->flags = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    flags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Packet_flags__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        return nativeObject->getPacket()->flags;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    pos
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Packet_pos__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        nativeObject->getPacket()->pos = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    pos
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Packet_pos__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<PacketNativeObject>(env, obj);
    try {
        return nativeObject->getPacket()->pos;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_Packet
 * Method:    newEmpty
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Packet_newEmpty
        (JNIEnv* env, jclass obj) {
    return make_java_native_object_ptr(std::make_shared<PacketNativeObject>());
}
