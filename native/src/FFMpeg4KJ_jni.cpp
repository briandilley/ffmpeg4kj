
#include "JniUtil.h"
#include "ffmpeg4kj_FFMpeg4KJ.h"

using namespace ffmpeg4kj::util;

extern "C" {
#include <libavformat/avformat.h>
};

/**
 * Class:     ffmpeg4kj_FFMpeg4KJ
 * Method:    configureNativeLibraries
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ffmpeg4kj_SFFMpeg4KJ_configureNativeLibraries
        (JNIEnv* env, jclass clazz) {
    initializeLogging();
    // av_register_all();
    JavaVM* vm = nullptr;
    env->GetJavaVM(&vm);
    init_jni(vm);

}
