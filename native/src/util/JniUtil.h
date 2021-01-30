#ifndef FFMPEG4KJ_JNIUTIL_H
#define FFMPEG4KJ_JNIUTIL_H

#include <jni.h>
#include <string>
#include <utf8.h>
#include <cassert>
#include <Poco/Logger.h>

#include "LogUtil.h"

extern "C" {
#include <libavutil/dict.h>
#include <libavutil/error.h>
}

#ifndef JNI_VERSION_1_8
#define JNI_VERSION_1_8 0x00010008
#endif

using namespace std;
using namespace ffmpeg4kj::util;

#define PictureStructure_JAVA_TYPE_NAME "ffmpeg4kj/av/PictureStructure"
#define Rounding_JAVA_TYPE_NAME "ffmpeg4kj/av/Rounding"
#define Discard_JAVA_TYPE_NAME "ffmpeg4kj/av/Discard"
#define ChromaLocation_JAVA_TYPE_NAME "ffmpeg4kj/av/ChromaLocation"
#define ColorSpace_JAVA_TYPE_NAME "ffmpeg4kj/av/ColorSpace"
#define ColorTransferCharacteristic_JAVA_TYPE_NAME "ffmpeg4kj/av/ColorTransferCharacteristic"
#define ColorPrimaries_JAVA_TYPE_NAME "ffmpeg4kj/av/ColorPrimaries"
#define ColorRange_JAVA_TYPE_NAME "ffmpeg4kj/av/ColorRange"
#define FieldOrder_JAVA_TYPE_NAME "ffmpeg4kj/av/FieldOrder"
#define SampleFormat_JAVA_TYPE_NAME "ffmpeg4kj/av/SampleFormat"
#define PixelFormat_JAVA_TYPE_NAME "ffmpeg4kj/av/PixelFormat"
#define MediaType_JAVA_TYPE_NAME "ffmpeg4kj/av/MediaType"
#define CodecID_JAVA_TYPE_NAME "ffmpeg4kj/av/CodecID"
#define ColorType_JAVA_TYPE_NAME "ffmpeg4kj/av/ColorType"
#define AlphaType_JAVA_TYPE_NAME "ffmpeg4kj/av/AlphaType"
#define BlendMode_JAVA_TYPE_NAME "ffmpeg4kj/av/BlendMode"
#define Cap_JAVA_TYPE_NAME "ffmpeg4kj/av/Cap"
#define FilterQuality_JAVA_TYPE_NAME "ffmpeg4kj/av/FilterQuality"
#define Join_JAVA_TYPE_NAME "ffmpeg4kj/av/Join"
#define Style_JAVA_TYPE_NAME "ffmpeg4kj/av/Style"
#define Color_JAVA_TYPE_NAME "ffmpeg4kj/av/Color"
#define FontWeight_JAVA_TYPE_NAME "ffmpeg4kj/av/FontWeight"
#define FontWidth_JAVA_TYPE_NAME "ffmpeg4kj/av/FontWidth"
#define FontSlant_JAVA_TYPE_NAME "ffmpeg4kj/av/FontSlant"
#define EncodedImageFormat_JAVA_TYPE_NAME "ffmpeg4kj/av/EncodedImageFormat"

#define THROW_RUNTIME_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/lang/RuntimeException", message)
#define THROW_TIMEOUT_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/util/concurrent/TimeoutException", message)
#define THROW_ILLEGAL_STATE_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/lang/IllegalStateException", message)
#define THROW_OUT_OF_MEMORY_ERROR_JAVA(env, message) throw_java_exception(env, "java/lang/OutOfMemoryError", message)
#define THROW_NULL_POINTER_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/lang/NullPointerException", message)
#define THROW_FILE_NOT_FOUND_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/io/FileNotFoundException", message)
#define THROW_ILLEGAL_ARGUMENT_EXCEPTION_JAVA(env, message) throw_java_exception(env, "java/lang/IllegalArgumentException", message);
#define THROW_GPU_EXCEPTION_JAVA(env, message) \
            const char* error; \
            glfwGetError(&error); \
            if (error == nullptr) { error = "Unknown"; } \
            throw_java_exception(env, "java/lang/IllegalStateException", (string(message) + ", GPU Error: " + error).c_str())

#define AVPictureStructureToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, PictureStructure_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVRoundingToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, Rounding_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVDiscardToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, Discard_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVChromaLocationToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, ChromaLocation_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVColorSpaceToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, ColorSpace_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVColorTransferCharacteristicToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, ColorTransferCharacteristic_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVColorPrimariesToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, ColorPrimaries_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVColorRangeToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, ColorRange_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVFieldOrderToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, FieldOrder_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVSampleFormatToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, SampleFormat_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVPixelFormatToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, PixelFormat_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVMediaTypeToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, MediaType_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)
#define AVCodecIDToJava(env, ordinal) \
            get_java_enum_by_native_ordinal(env, CodecID_JAVA_TYPE_NAME, "forNativeEnumValue", ordinal)

#define JavaToAVPictureStructure(env, enumObject) \
            (AVPictureStructure)get_native_ordinal_by_java_enum(env, PictureStructure_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVRounding(env, enumObject) \
            (AVRounding)get_native_ordinal_by_java_enum(env, Rounding_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVDiscard(env, enumObject) \
            (AVDiscard)get_native_ordinal_by_java_enum(env, Discard_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVChromaLocation(env, enumObject) \
            (AVChromaLocation)get_native_ordinal_by_java_enum(env, ChromaLocation_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVColorSpace(env, enumObject) \
            (AVColorSpace)get_native_ordinal_by_java_enum(env, ColorSpace_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVColorTransferCharacteristic(env, enumObject) \
            (AVColorTransferCharacteristic)get_native_ordinal_by_java_enum(env, ColorTransferCharacteristic_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVColorPrimaries(env, enumObject) \
            (AVColorPrimaries)get_native_ordinal_by_java_enum(env, ColorPrimaries_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVColorRange(env, enumObject) \
            (AVColorRange)get_native_ordinal_by_java_enum(env, ColorRange_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVFieldOrder(env, enumObject) \
            (AVFieldOrder)get_native_ordinal_by_java_enum(env, FieldOrder_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVSampleFormat(env, enumObject) \
            (AVSampleFormat)get_native_ordinal_by_java_enum(env, SampleFormat_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVPixelFormat(env, enumObject) \
            (AVPixelFormat)get_native_ordinal_by_java_enum(env, PixelFormat_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVMediaType(env, enumObject) \
            (AVMediaType)get_native_ordinal_by_java_enum(env, MediaType_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)
#define JavaToAVCodecID(env, enumObject) \
            (AVCodecID)get_native_ordinal_by_java_enum(env, CodecID_JAVA_TYPE_NAME, "getNativeEnumValue", enumObject)

#define jni_GetObjectClass(env, variableName, obj) nullptr; \
    if (variableName == nullptr || is_null(env, variableName)) { \
        if (variableName != nullptr) { \
            env->DeleteWeakGlobalRef(variableName); \
            variableName = nullptr; \
        } \
        variableName = env->GetObjectClass(obj); \
        variableName = (jclass)env->NewWeakGlobalRef(variableName); \
    }

#define jni_FindClass(env, variableName, className) nullptr; \
    if (variableName == nullptr || is_null(env, variableName)) { \
        if (variableName != nullptr) { \
            env->DeleteWeakGlobalRef(variableName); \
            variableName = nullptr; \
        } \
        variableName = env->FindClass(className); \
        if (was_exception_thrown(env)) { \
            variableName = nullptr; \
        } \
        variableName = (jclass)env->NewWeakGlobalRef(variableName); \
    }

#define jni_GetMethodId(env, classVariableName, variableName, name, sig) nullptr; \
    if (variableName == nullptr) { \
         variableName = env->GetMethodID(classVariableName, name, sig); \
    }

#define jni_WithAttachedEnv(body) \
    JNIEnv* env = get_java_env(); \
    bool __detach = env == nullptr; \
    if (__detach) { \
        env = attach_java_env(); \
    } \
    body ;\
    if (__detach) { \
        detach_java_env(); \
    }

namespace ffmpeg4kj::util {

    inline std::u16string get_utf16_string_from_java(JNIEnv* env, jstring string) {
        auto len = env->GetStringLength(string);
        auto* stringChars = env->GetStringChars(string, nullptr);
        std::u16string stringString;
        stringString.assign(stringChars, stringChars + len);
        env->ReleaseStringChars(string, stringChars);
        return stringString;
    }

    inline std::string get_utf8_string_from_java(JNIEnv* env, jstring string) {
        auto len = env->GetStringLength(string);
        auto* utf16 = env->GetStringChars(string, nullptr);
        try {
            vector<unsigned char> utf8result;
            utf8::utf16to8(utf16, utf16 + len, std::back_inserter(utf8result));
            env->ReleaseStringChars(string, utf16);
            return std::string(utf8result.begin(), utf8result.end());
        } catch(utf8::invalid_utf16& e) {
            std::string ret(utf16, utf16 + env->GetStringUTFLength(string));
            poco_warning_f1(getLogger("JniUtil"), "Invalid UTF16 string found, assuming that it is utf8: %[0]s", ret);
            env->ReleaseStringChars(string, utf16);
            return ret;
        }
    }

    inline std::string ffmpeg_error_string(int code) {
        char errStr[AV_ERROR_MAX_STRING_SIZE];
        av_strerror(code, &errStr[0], AV_ERROR_MAX_STRING_SIZE);
        return "AVError " + std::to_string(code) + ": " + std::string(errStr);
    }

    inline AVDictionary* string_to_av_dict(const std::string& str = "", int flags = 0) {
        AVDictionary* dict = nullptr;
        if (!str.empty()) {
            int ret = av_dict_parse_string(&dict, str.c_str(), "=", " ,", flags);
            if (ret < 0) {
                throw Poco::InvalidArgumentException(
                        "Unable to av_dict_parse_string ( " + ffmpeg_error_string(ret) + "): " + str);
            }
        }
        return dict;
    }

    int get_direct_buffer_capacity(JNIEnv *env, jobject buffer);
    int get_direct_buffer_position(JNIEnv *env, jobject buffer);
    void* get_direct_buffer_address_at_position(JNIEnv *env, jobject buffer);
    int get_direct_buffer_remaining(JNIEnv *env, jobject buffer);
    int get_direct_buffer_limit(JNIEnv *env, jobject buffer);
    jobject set_direct_buffer_position(JNIEnv *env, jobject buffer, int position);
    jobject set_direct_buffer_limit(JNIEnv *env, jobject buffer, int limit);

    jlong get_native_state_pointer(JNIEnv *env, jobject obj);

    template<typename T>
    T* get_native_state_ptr(JNIEnv* env, jobject obj) {
        jlong ret = get_native_state_pointer(env, obj);
        return (T*)ret;
    }

    void set_native_state_pointer(JNIEnv* env, jobject obj, void* ptr);

    void init_jni(JavaVM* vm);

    JNIEnv* get_java_env();

    JavaVM* get_java_vm();

    JNIEnv* attach_java_env();

    void detach_java_env();

    bool was_exception_thrown(JNIEnv* env);

    bool is_null(JNIEnv* env, jobject obj);

    float unbox_float(JNIEnv* env, jobject value);

    string get_class_name(JNIEnv *env, jobject obj);

    jint throw_java_exception(JNIEnv *env, const string& type, const string& message);

    jint get_native_ordinal_by_java_enum(JNIEnv *env, const string& enumClass, const string& memberMethodName, jobject enumObject);

    jobject get_java_enum_by_native_ordinal(JNIEnv *env, const string& enumClass, const string& staticMethodName, jint ordinal);

    jint get_int_field_value(JNIEnv *env, jobject obj, const string& fieldName);

}
#endif
