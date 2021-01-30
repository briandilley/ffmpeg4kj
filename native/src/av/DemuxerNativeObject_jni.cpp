
#include "ffmpeg4kj_av_Demuxer.h"
#include "JniUtil.h"
#include "DemuxerNativeObject.h"

using namespace ffmpeg4kj::util;

/**
 * Class:     ffmpeg4kj_av_Demuxer
 * Method:    findStreams
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Demuxer_findStreams
        (JNIEnv* env, jobject obj, jstring options) {
    try {
        std::string optionsString = options == nullptr
            ? ""
            : get_utf8_string_from_java(env, options);
        auto nativeObject = get_native_object<DemuxerNativeObject>(env, obj);
        nativeObject->findStreams(optionsString);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Demuxer
 * Method:    findBestStreamIndex
 * Signature: (Lffmpeg4kj/av/MediaType;III)Ljava/lang/Integer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Demuxer_findBestStreamIndex
        (JNIEnv* env, jobject obj, jobject type, jint wantedStreamNumber, jint relatedStream, jint flags) {
    try {
        auto nativeObject = get_native_object<DemuxerNativeObject>(env, obj);
        auto index = nativeObject->findBestStreamIndex(
                JavaToAVMediaType(env, type),
                wantedStreamNumber,
                relatedStream,
                flags);
        if (index < 0) {
            return nullptr;
        }
        static jclass retClazz = jni_FindClass(env, retClazz, "java/lang/Integer");
        static jmethodID retConstructor = jni_GetMethodId(env, retClazz, retConstructor, "<init>", "(I)V");
        return env->NewObject(retClazz, retConstructor, index);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Demuxer
 * Method:    readFrame
 * Signature: (Lffmpeg4kj/av/Packet;)Z
 */
JNIEXPORT jboolean JNICALL Java_ffmpeg4kj_av_Demuxer_readFrame
        (JNIEnv* env, jobject obj, jobject packet) {
    try {
        auto nativeObject = get_native_object<DemuxerNativeObject>(env, obj);
        auto packetNativeObject = get_native_object<PacketNativeObject>(env, packet);
        return nativeObject->readFrame(packetNativeObject);
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}

/**
 * Class:     ffmpeg4kj_av_Demuxer
 * Method:    closeInput
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_av_Demuxer_closeInput
        (JNIEnv* env, jobject obj) {
    try {
        auto nativeObject = get_native_object<DemuxerNativeObject>(env, obj);
        nativeObject->closeInput();
    } catch(Poco::IllegalStateException& e) {
        THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
}

/**
 * Class:     ffmpeg4kj_av_Demuxer
 * Method:    openInput
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lffmpeg4kj/av/IOContext;)Lffmpeg4kj/av/Demuxer;
 */
JNIEXPORT jobject JNICALL Java_ffmpeg4kj_av_Demuxer_openInput
        (JNIEnv* env, jclass obj, jstring url, jstring options, jobject ioContext) {

    std::string urlString = url == nullptr
            ? ""
            : get_utf8_string_from_java(env, url);

    std::string optionsString = options == nullptr
            ? ""
            : get_utf8_string_from_java(env, options);

    auto ioContextNativeObject = ioContext != nullptr
            ? get_native_object<IOContextNativeObject>(env, ioContext)
            : nullptr;

    try {
        auto nativeObject = DemuxerNativeObject::openInput(urlString, optionsString, ioContextNativeObject);
        if (ioContextNativeObject != nullptr) {
            nativeObject->addReference("ioContext", ioContext);
        }
        static jclass muxerClazz = jni_FindClass(env, muxerClazz, DemuxerNativeObject_JAVA_TYPE_NAME);
        static jmethodID cstr = jni_GetMethodId(env, muxerClazz, cstr, "<init>", "(J)V");
        return env->NewObject(muxerClazz, cstr, make_java_native_object_ptr(nativeObject));
    } catch(Poco::InvalidArgumentException& e) {
        THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, e.message());
    } catch(Poco::RuntimeException& e) {
        THROW_RUNTIME_EXCEPTION_JAVA(env, e.message());
    }
    return 0;
}
