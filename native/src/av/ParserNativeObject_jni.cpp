
#include "ffmpeg4kj_av_Parser.h"
#include "JniUtil.h"
#include "ParserNativeObject.h"
#include "CodecContextNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    update
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_update
        (JNIEnv* env, jobject obj, jobject inputBuffer) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    void* buff = get_direct_buffer_address_at_position(env, inputBuffer);
    int remaining = get_direct_buffer_remaining(env, inputBuffer);
    nativeObject->update((uint8_t*)buff, remaining);
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    parse
 * Signature: (Lffmpeg4kj/av/CodecContext;Lffmpeg4kj/av/Packet;JJJ)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Parser_parse__Lffmpeg4kj_av_CodecContext_2Lffmpeg4kj_av_Packet_2JJJ
        (JNIEnv* env, jobject obj, jobject codecContext, jobject packet, jlong pts, jlong dts, jlong pos) {

    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    auto codecContextObject = get_native_object<CodecContextNativeObject>(env, codecContext);
    auto packetObject = get_native_object<PacketNativeObject>(env, packet);

    try {
        return nativeObject->parse(codecContextObject, packetObject, pts, dts, pos);
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return false;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    parse
 * Signature: (Lffmpeg4kj/av/CodecContext;Ljava/nio/ByteBuffer;JJJ)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Parser_parse__Lffmpeg4kj_av_CodecContext_2Ljava_nio_ByteBuffer_2JJJ
        (JNIEnv* env, jobject obj, jobject codecContext, jobject inputBuffer, jlong pts, jlong dts, jlong pos) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    auto codecContextObject = get_native_object<CodecContextNativeObject>(env, codecContext);

    try {
        uint8_t* outputBuffer = nullptr;
        int outputSize = 0;

        void* buff = get_direct_buffer_address_at_position(env, inputBuffer);
        int remaining = get_direct_buffer_remaining(env, inputBuffer);

        nativeObject->parse(
                codecContextObject,
                &outputBuffer, &outputSize,
                (uint8_t*)buff, remaining,
                pts, dts, pos);

        if (outputSize <= 0) {
            return (jobject)nullptr;
        }

        return env->NewDirectByteBuffer(outputBuffer, outputSize);

    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return (jobject)nullptr;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_free
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    nativeObject->free();
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    frameOffset
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_frameOffset__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->frame_offset;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    frameOffset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_frameOffset__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->frame_offset = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    curOffset
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_curOffset__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_offset;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    curOffset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_curOffset__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_offset = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    nextFrameOffset
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_nextFrameOffset__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->next_frame_offset;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    nextFrameOffset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_nextFrameOffset__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->next_frame_offset = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pictType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_pictType__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->pict_type;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pictType
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_pictType__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->pict_type = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    repeatPict
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_repeatPict__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->repeat_pict;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    repeatPict
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_repeatPict__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->repeat_pict = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_pts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->pts;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_pts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->pts = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_dts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->dts;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_dts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->dts = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastPts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_lastPts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->last_pts;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastPts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_lastPts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->last_pts = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastDts
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_lastDts__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->last_dts;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastDts
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_lastDts__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->last_dts = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    fetchTimestamp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_fetchTimestamp__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->fetch_timestamp;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    fetchTimestamp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_fetchTimestamp__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->fetch_timestamp = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    currentFrameStartIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_currentFrameStartIndex__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_start_index;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    currentFrameStartIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_currentFrameStartIndex__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_start_index = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    getCurrentFrameOffset
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_getCurrentFrameOffset
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_offset[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    setCurrentFrameOffset
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_setCurrentFrameOffset
        (JNIEnv* env, jobject obj, jint index, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_offset[index] = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    getCurrentFramePts
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_getCurrentFramePts
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_pts[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    setCurrentFramePts
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_setCurrentFramePts
        (JNIEnv* env, jobject obj, jint index, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_pts[index] = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    getCurrentFrameDts
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_getCurrentFrameDts
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_dts[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    setCurrentFrameDts
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_setCurrentFrameDts
        (JNIEnv* env, jobject obj, jint index, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_dts[index] = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    flags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_flags__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->flags;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    flags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_flags__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->flags = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    offset
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_offset__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->offset;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    offset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_offset__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->offset = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    getCurrentFrameEnd
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_getCurrentFrameEnd
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_end[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    setCurrentFrameEnd
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_setCurrentFrameEnd
        (JNIEnv* env, jobject obj, jint index, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_end[index] = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    keyFrame
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_keyFrame__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->key_frame;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    keyFrame
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_keyFrame__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->key_frame = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dtsSyncPoint
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_dtsSyncPoint__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->dts_sync_point;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dtsSyncPoint
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_dtsSyncPoint__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->dts_sync_point = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dtsRefDtsDelta
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_dtsRefDtsDelta__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->dts_ref_dts_delta;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    dtsRefDtsDelta
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_dtsRefDtsDelta__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->dts_ref_dts_delta = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    ptsDtsDelta
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_ptsDtsDelta__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->pts_dts_delta;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    ptsDtsDelta
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_ptsDtsDelta__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->pts_dts_delta = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    getCurrentFramePos
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_getCurrentFramePos
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->cur_frame_pts[index];
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    setCurrentFramePos
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_setCurrentFramePos
        (JNIEnv* env, jobject obj, jint index, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->cur_frame_pos[index] = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pos
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_pos__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->pos;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pos
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_pos__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->pos = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastPos
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_Parser_lastPos__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->last_pos;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    lastPos
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_lastPos__J
        (JNIEnv* env, jobject obj, jlong value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->last_pos = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    duration
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_duration__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->duration;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    duration
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_duration__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->duration = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    fieldOrder
 * Signature: ()Lffmpeg4kj/av/FieldOrder;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Parser_fieldOrder__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return AVFieldOrderToJava(env, nativeObject->getRequiredContext()->field_order);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    fieldOrder
 * Signature: (Lffmpeg4kj/av/FieldOrder;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_fieldOrder__Lffmpeg4kj_av_FieldOrder_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->field_order = JavaToAVFieldOrder(env, value);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pictureStructure
 * Signature: ()Lffmpeg4kj/av/PictureStructure;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Parser_pictureStructure__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return AVPictureStructureToJava(env, nativeObject->getRequiredContext()->picture_structure);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    pictureStructure
 * Signature: (Lffmpeg4kj/av/PictureStructure;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_pictureStructure__Lffmpeg4kj_av_PictureStructure_2
        (JNIEnv* env, jobject obj, jobject value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->frame_offset = JavaToAVPictureStructure(env, value);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    outputPictureNumber
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_outputPictureNumber__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->output_picture_number;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    outputPictureNumber
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_outputPictureNumber__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->output_picture_number = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    width
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_width__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->width;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    width
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_width__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->width = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    height
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_height__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->height;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    height
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_height__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->height = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    codedWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_codedWidth__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->coded_width;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    codedWidth
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_codedWidth__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->coded_width = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    codedHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_codedHeight__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->coded_height;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    codedHeight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_codedHeight__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->coded_height = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    format
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_Parser_format__
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredContext()->format;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    format
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Parser_format__I
        (JNIEnv* env, jobject obj, jint value) {
    auto nativeObject = get_native_object<ParserNativeObject>(env, obj);
    try {
        nativeObject->getRequiredContext()->format = value;
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Parser
 * Method:    createParser
 * Signature: (Lffmpeg4kj/av/CodecID;)Lffmpeg4kj/av/Parser;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Parser_createParser
        (JNIEnv* env, jclass obj, jobject value) {
    try {
        auto codecId = JavaToAVCodecID(env, value);
        auto nativeObject = ParserNativeObject::createParser(codecId);

        static jclass clazz = jni_FindClass(env, clazz, ParserNativeObject_JAVA_TYPE_NAME);
        static jmethodID ctr = jni_GetMethodId(env, clazz, ctr, "<init>", "(J)V");
        return env->NewObject(clazz, ctr, make_java_native_object_ptr(nativeObject));

    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    }
    return (jobject)nullptr;
}
