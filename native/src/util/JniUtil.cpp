
#include "JniUtil.h"

#define JVM_VERSION JNI_VERSION_1_8
#define ASSERT_JNI_INITIALIZED \
    if (jvm == nullptr) { \
        poco_fatal(LOGGER(), "Attempting to initialize the JVM subsystem with a nullptr"); \
        throw Poco::Exception("Attempting to initialize the JVM subsystem with a nullptr"); \
    }

using namespace std;
using namespace ffmpeg4kj::util;
using namespace ffmpeg4kj::util;

static Poco::Logger &LOGGER() { return getLogger("JniUtil"); }

static JavaVM* jvm = nullptr;

void ffmpeg4kj::util::init_jni(JavaVM* vm) {
    poco_assert_msg(vm != nullptr,
            "Attempting to initialize the JVM subsystem with a nullptr");
    jvm = vm;
    JNIEnv* env = nullptr;
    if (jvm->GetEnv(reinterpret_cast<void**>(&env), JVM_VERSION) != JNI_OK) {
        poco_assert_msg(vm != nullptr, "Expected JNI_VERSION_1_8");
        jvm = nullptr;
    }
    poco_information(LOGGER(), "JNI subsystem initialized");
}

JavaVM* ffmpeg4kj::util::get_java_vm() {
    ASSERT_JNI_INITIALIZED
    return jvm;
}

JNIEnv* ffmpeg4kj::util::get_java_env() {
    ASSERT_JNI_INITIALIZED
    void* env = nullptr;
    jint status = jvm->GetEnv(&env, JVM_VERSION);
    poco_assert_msg(
            ((env != nullptr) && (status == JNI_OK))
            || ((env == nullptr) && (status == JNI_EDETACHED)),
            "Unexpected GetEnv return");
    return reinterpret_cast<JNIEnv*>(env);
}

JNIEnv* ffmpeg4kj::util::attach_java_env() {
    JNIEnv* env = get_java_env();
    if (env) {
        return env;
    }

    std::string name("Attached Thread");
    JavaVMAttachArgs args;
    args.version = JVM_VERSION;
    args.name = &name[0];
    args.group = nullptr;

    poco_assert_msg(jvm->AttachCurrentThread((void**)&env, &args) == JNI_OK,
            "Failed to attach thread");

    return env;
}

void ffmpeg4kj::util::detach_java_env() {
    if (get_java_env() == nullptr) {
        return;
    }
    poco_assert_msg(jvm->DetachCurrentThread() == JNI_OK, "Failed to detach thread");
    poco_assert_msg(get_java_env() == nullptr, "Detached but can still get a JNIEnv?");
}

bool ffmpeg4kj::util::was_exception_thrown(JNIEnv* env) {
    if (env->ExceptionCheck()) {
        poco_error(LOGGER(), "A Java Exception was thrown in JNI code, description follows");
        env->ExceptionDescribe();
        return true;
    }
    return false;
}

bool ffmpeg4kj::util::is_null(JNIEnv* env, jobject obj) {
    return env->IsSameObject(nullptr, obj);
}

string ffmpeg4kj::util::get_class_name(JNIEnv* env, jobject obj) {
    jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
    jobject clsObj = env->CallObjectMethod(obj, mid);
    env->DeleteLocalRef(cls);
    cls = env->GetObjectClass(clsObj);
    mid = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    env->DeleteLocalRef(cls);
    auto strObj = (jstring)env->CallObjectMethod(clsObj, mid);
    env->DeleteLocalRef(clsObj);
    return get_utf8_string_from_java(env, strObj);
}

jint ffmpeg4kj::util::throw_java_exception(JNIEnv *env, const string& type, const string& message) {
    jclass exClass = env->FindClass(type.c_str());
    if (was_exception_thrown(env)) {
        env->ExceptionClear();
    }
    auto ret = env->ThrowNew(exClass, message.c_str());
    env->DeleteLocalRef(exClass);
    return ret;
}

jint ffmpeg4kj::util::get_int_field_value(JNIEnv* env, jobject obj, const string& fieldName) {
    jclass clazz = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(clazz, fieldName.c_str(), "I");
    env->DeleteLocalRef(clazz);
    return env->GetIntField(obj, fid);
}

jint ffmpeg4kj::util::get_native_ordinal_by_java_enum(
        JNIEnv *env, const string& enumClass, const string& memberMethodName, jobject enumObject) {
    jclass clazz = env->GetObjectClass(enumObject);
    jmethodID mid = env->GetMethodID(clazz, memberMethodName.c_str(), "()I");
    auto ret = env->CallIntMethod(enumObject, mid);
    was_exception_thrown(env);
    env->DeleteLocalRef(clazz);
    return ret;
}

jobject ffmpeg4kj::util::get_java_enum_by_native_ordinal(
        JNIEnv* env, const string& enumClass, const string& staticMethodName, jint ordinal) {
    jclass clazz = env->FindClass(enumClass.c_str());
    string sig = "(I)L" + string(enumClass) + ";";
    jmethodID mid = env->GetStaticMethodID(clazz, staticMethodName.c_str(), sig.c_str());
    auto ret = env->CallStaticObjectMethod(clazz, mid, ordinal);
    was_exception_thrown(env);
    env->DeleteLocalRef(clazz);
    return ret;
}

float ffmpeg4kj::util::unbox_float(JNIEnv *env, jobject value) {
    jclass floatClass = jni_GetObjectClass(env, floatClass, value);
    jmethodID floatValueMethod = jni_GetMethodId(env, floatClass, floatValueMethod, "floatValue", "()F");
    auto ret = env->CallFloatMethod(value, floatValueMethod);
    was_exception_thrown(env);
    return ret;
}

jlong ffmpeg4kj::util::get_native_state_pointer(JNIEnv *env, jobject obj) {
    if (obj == nullptr) {
        return 0;
    }
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        clazz = env->GetObjectClass(obj);
        clazz = (jclass)env->NewGlobalRef(clazz);
    }
    static jfieldID nativeStatePtr = nullptr;
    if (nativeStatePtr == nullptr) {
        nativeStatePtr = env->GetFieldID(clazz, "nativeStatePtr", "J");
    }
    return env->GetLongField(obj, nativeStatePtr);
}

void ffmpeg4kj::util::set_native_state_pointer(JNIEnv* env, jobject obj, void* ptr) {
    jclass clazz = env->GetObjectClass(obj);
    static jfieldID nativeStatePtr = env->GetFieldID(clazz, "nativeStatePtr", "J");
    env->SetLongField(obj, nativeStatePtr, (jlong)ptr);
    env->DeleteLocalRef(clazz);
}

int ffmpeg4kj::util::get_direct_buffer_capacity(JNIEnv *env, jobject buffer) {
    return env->GetDirectBufferCapacity(buffer);
}

int ffmpeg4kj::util::get_direct_buffer_position(JNIEnv *env, jobject buffer) {
    static jclass byteBufferClazz = jni_FindClass(env, byteBufferClazz, "java/nio/ByteBuffer");
    static jmethodID method = jni_GetMethodId(env, byteBufferClazz, method, "position", "()I");
    return env->CallIntMethod(buffer, method);
}

void* ffmpeg4kj::util::get_direct_buffer_address_at_position(JNIEnv *env, jobject buffer) {
    char* ret = (char*)env->GetDirectBufferAddress(buffer);
    ret += get_direct_buffer_position(env, buffer);
    return ret;
}

int ffmpeg4kj::util::get_direct_buffer_remaining(JNIEnv *env, jobject buffer) {
    static jclass byteBufferClazz = jni_FindClass(env, byteBufferClazz, "java/nio/ByteBuffer");
    static jmethodID method = jni_GetMethodId(env, byteBufferClazz, method, "remaining", "()I");
    return env->CallIntMethod(buffer, method);
}


int ffmpeg4kj::util::get_direct_buffer_limit(JNIEnv *env, jobject buffer) {
    static jclass byteBufferClazz = jni_FindClass(env, byteBufferClazz, "java/nio/ByteBuffer");
    static jmethodID method = jni_GetMethodId(env, byteBufferClazz, method, "limit", "()I");
    return env->CallIntMethod(buffer, method);
}

jobject ffmpeg4kj::util::set_direct_buffer_position(JNIEnv *env, jobject buffer, int position) {
    static jclass byteBufferClazz = jni_FindClass(env, byteBufferClazz, "java/nio/ByteBuffer");
    static jmethodID method = jni_GetMethodId(env, byteBufferClazz, method, "position", "(I)Ljava/nio/ByteBuffer;");
    return env->CallObjectMethod(buffer, method, position);
}

jobject ffmpeg4kj::util::set_direct_buffer_limit(JNIEnv *env, jobject buffer, int limit) {
    static jclass byteBufferClazz = jni_FindClass(env, byteBufferClazz, "java/nio/ByteBuffer");
    static jmethodID method = jni_GetMethodId(env, byteBufferClazz, method, "limit", "(I)Ljava/nio/ByteBuffer;");
    return env->CallObjectMethod(buffer, method, limit);
}
