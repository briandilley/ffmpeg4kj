
#include "ffmpeg4kj_av_FormatContext.h"
#include "JniUtil.h"
#include "FormatContextNativeObject.h"
#include "RationalNativeObject.h"
#include "StreamNativeObject.h"
#include "CodecNativeObject.h"
#include "IOContextNativeObject.h"

using namespace ffmpeg4kj::util;

static AVFormatContext* getAVFormatContext(JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FormatContextNativeObject>(env, obj);
    try {
        return nativeObject->getRequiredFormatContext();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return nullptr;
    }
}

#define withAVFormatContextReturn(body) \
    AVFormatContext* context = getAVFormatContext(env, obj); \
    if (context == nullptr) { \
        return 0; \
    } \
    body

#define withAVFormatContext(body) \
    AVFormatContext* context = getAVFormatContext(env, obj); \
    if (context == nullptr) { \
        return; \
    } \
    body

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    streamCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_streamCount
        (JNIEnv* env, jobject obj) {
    auto nativeObject = get_native_object<FormatContextNativeObject>(env, obj);
    try {
        return nativeObject->getStreamCount();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        return 0;
    }
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    getStream
 * Signature: (I)Lffmpeg4kj/av/Stream;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_getStream
        (JNIEnv* env, jobject obj, jint index) {
    auto nativeObject = get_native_object<FormatContextNativeObject>(env, obj);
    return nativeObject->getReference("getStream_" + std::to_string(index), [nativeObject, env, index]() {
        try {
            std::shared_ptr<StreamNativeObject> stream = nativeObject->getStream(index);
            static jclass streamClazz = jni_FindClass(env, streamClazz, StreamNativeObject_JAVA_TYPE_NAME);
            static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
            return env->NewObject(streamClazz, cstr, make_java_native_object_ptr(stream));
        } catch(Poco::IllegalStateException& e) {
            THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
        } catch(Poco::RuntimeException& e) {
            THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
        }
        return (jobject)nullptr;
    });
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    dump
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_dump
        (JNIEnv* env, jobject obj, jboolean isOutput) {
    auto nativeObject = get_native_object<FormatContextNativeObject>(env, obj);
    nativeObject->dump(isOutput);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    ctxFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_ctxFlags__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->ctx_flags);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    ctxFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_ctxFlags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->ctx_flags = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    url
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ffmpeg4kj_av_FormatContext_url__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(
            if (context->url == nullptr) {
                return nullptr;
            }
            return env->NewStringUTF(context->url));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    url
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_url__Ljava_lang_String_2
        (JNIEnv* env, jobject obj, jstring value) {
    withAVFormatContext(
            if (value == nullptr) {
                context->url = nullptr;
            }
            std::string str = get_utf8_string_from_java(env, value);
            context->url = (char*)str.c_str());
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    startTime
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_startTime
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->start_time);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    duration
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_duration__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->duration);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    duration
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_duration__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->duration = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    bitRate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_bitRate__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->bit_rate);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    bitRate
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_bitRate__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->bit_rate = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxDelay
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxDelay__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_delay);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxDelay
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxDelay__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_delay = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    flags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_flags__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->flags);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    flags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_flags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->flags = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    probeSize
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_probeSize__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->probesize);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    probeSize
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_probeSize__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->probesize = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxAnalyzeDuration
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_maxAnalyzeDuration__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_analyze_duration);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxAnalyzeDuration
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxAnalyzeDuration__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->max_analyze_duration = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    videoCodecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_videoCodecId__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return AVCodecIDToJava(env, context->video_codec_id));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    videoCodecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_videoCodecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(context->video_codec_id = JavaToAVCodecID(env, value));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioCodecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_audioCodecId__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return AVCodecIDToJava(env, context->audio_codec_id));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioCodecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_audioCodecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(context->audio_codec_id = JavaToAVCodecID(env, value));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    subtitleCodecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_subtitleCodecId__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return AVCodecIDToJava(env, context->subtitle_codec_id));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    subtitleCodecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_subtitleCodecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(context->subtitle_codec_id = JavaToAVCodecID(env, value));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxIndexSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxIndexSize__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_index_size);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxIndexSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxIndexSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_index_size = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxPictureBuffer
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxPictureBuffer__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_picture_buffer);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxPictureBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxPictureBuffer__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_picture_buffer = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    startTimeRealtime
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_startTimeRealtime__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->start_time_realtime);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    startTimeRealtime
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_startTimeRealtime__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->start_time_realtime = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    fpsProbeSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_fpsProbeSize__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->fps_probe_size);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    fpsProbeSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_fpsProbeSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->fps_probe_size = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    errorRecognition
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_errorRecognition__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->error_recognition);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    errorRecognition
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_errorRecognition__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->error_recognition = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    debug
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_debug__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->debug);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    debug
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_debug__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->debug = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxInterleaveDelta
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_maxInterleaveDelta__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_interleave_delta);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxInterleaveDelta
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxInterleaveDelta__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->max_interleave_delta = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    strictStdCompliance
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_strictStdCompliance__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->strict_std_compliance);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    strictStdCompliance
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_strictStdCompliance__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->strict_std_compliance = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    eventFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_eventFlags__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->event_flags);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    eventFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_eventFlags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->event_flags = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxTsProbe
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxTsProbe__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_ts_probe);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxTsProbe
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxTsProbe__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_ts_probe = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    avoidNegativeTs
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_avoidNegativeTs__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->avoid_negative_ts);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    avoidNegativeTs
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_avoidNegativeTs__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->avoid_negative_ts = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioPreload
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_audioPreload__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->audio_preload);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioPreload
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_audioPreload__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->audio_preload = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxChunkDuration
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxChunkDuration__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_chunk_duration);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxChunkDuration
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxChunkDuration__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_chunk_duration = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxChunkSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxChunkSize__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_chunk_size);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxChunkSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxChunkSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_chunk_size = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    useWallClockAsTimestamps
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_useWallClockAsTimestamps__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->use_wallclock_as_timestamps);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    useWallClockAsTimestamps
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_useWallClockAsTimestamps__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->use_wallclock_as_timestamps = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    avioFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_avioFlags__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->avio_flags);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    avioFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_avioFlags__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->avio_flags = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    skipInitialBytes
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_skipInitialBytes__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->skip_initial_bytes);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    skipInitialBytes
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_skipInitialBytes__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->skip_initial_bytes = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    correctTsOverflow
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_correctTsOverflow__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->correct_ts_overflow);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    correctTsOverflow
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_correctTsOverflow__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->correct_ts_overflow = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    seek2any
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_seek2any__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->seek2any);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    seek2any
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_seek2any__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->seek2any = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    flushPackets
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_flushPackets__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->flush_packets);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    flushPackets
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_flushPackets__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->flush_packets = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    propbeScore
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_propbeScore__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->probe_score);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    propbeScore
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_propbeScore__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->probe_score = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    formatProbeSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_formatProbeSize__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->format_probesize);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    formatProbeSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_formatProbeSize__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->format_probesize = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    videoCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_videoCodec__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(
            if (context->video_codec == nullptr) {
                return nullptr;
            }
            try {
                auto codecNativeObject = std::make_shared<CodecNativeObject>(context->video_codec);
                static jclass streamClazz = jni_FindClass(env, streamClazz, CodecNativeObject_JAVA_TYPE_NAME);
                static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
                return env->NewObject(streamClazz, cstr, make_java_native_object_ptr(codecNativeObject));
            } catch(Poco::IllegalStateException& e) {
                THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
                return 0;
            });
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    videoCodec
 * Signature: (Lffmpeg4kj/av/Codec;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_videoCodec__Lffmpeg4kj_av_Codec_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(
            if (value == nullptr) {
                context->video_codec = nullptr;
                return;
            }
            auto codecNativeObject = get_native_object<CodecNativeObject>(env, value);
            context->video_codec = codecNativeObject->getCodec());
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_audioCodec__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(
            if (context->audio_codec == nullptr) {
                return nullptr;
            }
            try {
                auto codecNativeObject = std::make_shared<CodecNativeObject>(context->audio_codec);
                static jclass streamClazz = jni_FindClass(env, streamClazz, CodecNativeObject_JAVA_TYPE_NAME);
                static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
                return env->NewObject(streamClazz, cstr, make_java_native_object_ptr(codecNativeObject));
            } catch(Poco::IllegalStateException& e) {
                THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
                return 0;
            });
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    audioCodec
 * Signature: (Lffmpeg4kj/av/Codec;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_audioCodec__Lffmpeg4kj_av_Codec_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(
            if (value == nullptr) {
                context->audio_codec = nullptr;
                return;
            }
            auto codecNativeObject = get_native_object<CodecNativeObject>(env, value);
            context->audio_codec = codecNativeObject->getCodec());
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    subtitleCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_subtitleCodec__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(
            if (context->subtitle_codec == nullptr) {
                return nullptr;
            }
            try {
                auto codecNativeObject = std::make_shared<CodecNativeObject>(context->subtitle_codec);
                static jclass streamClazz = jni_FindClass(env, streamClazz, CodecNativeObject_JAVA_TYPE_NAME);
                static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
                return env->NewObject(streamClazz, cstr, make_java_native_object_ptr(codecNativeObject));
            } catch(Poco::IllegalStateException& e) {
                THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
                return 0;
            });
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    subtitleCodec
 * Signature: (Lffmpeg4kj/av/Codec;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_subtitleCodec__Lffmpeg4kj_av_Codec_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(
            if (value == nullptr) {
                context->subtitle_codec = nullptr;
                return;
            }
            auto codecNativeObject = get_native_object<CodecNativeObject>(env, value);
            context->subtitle_codec = codecNativeObject->getCodec());
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    dataCodec
 * Signature: ()Lffmpeg4kj/av/Codec;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_dataCodec__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(
            if (context->data_codec == nullptr) {
                return nullptr;
            }
            try {
                auto codecNativeObject = std::make_shared<CodecNativeObject>(context->data_codec);
                static jclass streamClazz = jni_FindClass(env, streamClazz, CodecNativeObject_JAVA_TYPE_NAME);
                static jmethodID cstr = jni_GetMethodId(env, streamClazz, cstr, "<init>", "(J)V");
                return env->NewObject(streamClazz, cstr, make_java_native_object_ptr(codecNativeObject));
            } catch(Poco::IllegalStateException& e) {
                THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
                return 0;
            });
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    dataCodec
 * Signature: (Lffmpeg4kj/av/Codec;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_dataCodec__Lffmpeg4kj_av_Codec_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(
            if (value == nullptr) {
                context->data_codec = nullptr;
                return;
            }
            auto codecNativeObject = get_native_object<CodecNativeObject>(env, value);
            context->data_codec = codecNativeObject->getCodec());
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    metadataHeaderPadding
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_metadataHeaderPadding__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->metadata_header_padding);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    metadataHeaderPadding
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_metadataHeaderPadding__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->metadata_header_padding = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    outputTsOffset
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ffmpeg4kj_av_FormatContext_outputTsOffset__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->output_ts_offset);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    outputTsOffset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_outputTsOffset__J
        (JNIEnv* env, jobject obj, jlong value) {
    withAVFormatContext(context->output_ts_offset = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    dataCodecId
 * Signature: ()Lffmpeg4kj/av/CodecID;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_FormatContext_dataCodecId__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return AVCodecIDToJava(env, context->data_codec_id));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    dataCodecId
 * Signature: (Lffmpeg4kj/av/CodecID;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_dataCodecId__Lffmpeg4kj_av_CodecID_2
        (JNIEnv* env, jobject obj, jobject value) {
    withAVFormatContext(context->data_codec_id = JavaToAVCodecID(env, value));
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxStreams
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_maxStreams__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->max_streams);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    maxStreams
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_maxStreams__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->max_streams = value);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    skipEstimateDurationFromPts
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ffmpeg4kj_av_FormatContext_skipEstimateDurationFromPts__
        (JNIEnv* env, jobject obj) {
    withAVFormatContextReturn(return context->skip_estimate_duration_from_pts);
}

/**
 * Class:     ffmpeg4kj_av_FormatContext
 * Method:    skipEstimateDurationFromPts
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_FormatContext_skipEstimateDurationFromPts__I
        (JNIEnv* env, jobject obj, jint value) {
    withAVFormatContext(context->skip_estimate_duration_from_pts = value);
}
