
#include "AbstractNativeObject.h"

using namespace ffmpeg4kj::util;

AbstractNativeObject::~AbstractNativeObject() {
    poco_trace_f1(LOGGER, "Destructing object %s", javaTypeName);
    this->clearReferences();
}

AbstractNativeObject::AbstractNativeObject(const std::string& javaTypeName) :
        AbstractLoggingObject(javaTypeName),
        javaTypeName(javaTypeName),
        references() {
    poco_trace_f1(LOGGER, "Creating object %s", javaTypeName);
}

AbstractNativeObject::AbstractNativeObject(const AbstractNativeObject& other) :
        AbstractLoggingObject(other),
        javaTypeName(other.javaTypeName),
        references(other.references) {
    poco_trace_f1(LOGGER, "Creating copy of object %s", javaTypeName);
}

AbstractNativeObject::AbstractNativeObject(AbstractNativeObject&& other) noexcept :
        AbstractLoggingObject(std::move(other)),
        javaTypeName(nullptr),
        references() {
    swap(*this, other);
    poco_trace_f1(LOGGER, "Creating move of object %s", javaTypeName);
}

AbstractNativeObject& AbstractNativeObject::operator=(AbstractNativeObject other) {
    swap(*this, other);
    return *this;
}


void ffmpeg4kj::util::swap(AbstractNativeObject& lhs, AbstractNativeObject& rhs) {
    std::swap(static_cast<AbstractLoggingObject&>(lhs), static_cast<AbstractLoggingObject&>(rhs));
    std::swap(lhs.javaTypeName, rhs.javaTypeName);
    std::swap(lhs.references, rhs.references);
}

const std::string& AbstractNativeObject::getJavaTypeName() {
    return javaTypeName;
}

bool AbstractNativeObject::hasReference(const std::string& key) {
    return this->references.find(key) != this->references.end();
}

jobject AbstractNativeObject::addReference(const std::string& key, jobject obj) {
    if (obj != nullptr) {
        poco_trace_f1(LOGGER, "Adding reference %s", key);
        jni_WithAttachedEnv(obj = env->NewGlobalRef(obj));
        this->references[key] = obj;
    }
    return obj;
}

jobject AbstractNativeObject::getReference(const std::string& key, std::function<jobject()> func) {

    jobject ret = (jobject)nullptr;

    auto pair = this->references.find(key);
    if (pair != this->references.end()) {
        ret = pair->second;
    }

    if (ret != nullptr) {
        jni_WithAttachedEnv(
            if (env->IsSameObject(ret, nullptr)) {
                ret = (jobject)nullptr;
            });
    }

    if (ret == nullptr && func != nullptr) {
        ret = func();
        ret = this->addReference(key, ret);
    }

    return ret;
}

jobject AbstractNativeObject::updateReference(const std::string& key, jobject value) {
    this->removeReference(key);
    return this->getReference(key, [value]() { return value; });
}

bool AbstractNativeObject::removeReference(const std::string& key) {
    auto pair = this->references.find(key);
    if (pair == this->references.end()) {
        return false;
    }
    this->references.erase(pair);
    poco_trace_f1(LOGGER, "Removing reference %s", key);
    jni_WithAttachedEnv(env->DeleteGlobalRef(pair->second));
    return true;
}

void AbstractNativeObject::clearReferences() {
    for (auto itr = this->references.begin(); itr != this->references.end(); itr++) {
        poco_trace_f1(LOGGER, "Clearing reference %s", itr->first);
        jni_WithAttachedEnv(env->DeleteGlobalRef(itr->second));
    }
    this->references.clear();
}


struct State {
    std::shared_ptr<AbstractNativeObject> ptr;
};

jlong ffmpeg4kj::util::make_java_native_object_ptr(std::shared_ptr<AbstractNativeObject> state) {
    auto* ret = new State();
    ret->ptr = std::move(state);
    return (jlong)ret;
}

std::shared_ptr<AbstractNativeObject> ffmpeg4kj::util::get_abstract_native_object(JNIEnv *env, jobject obj) {
    if (obj == nullptr) {
        return nullptr;
    }
    static jclass clazz = jni_FindClass(env, clazz, AbstractNativeObject_JAVA_TYPE_NAME);
    static jfieldID nativeStatePtr = nullptr;
    if (nativeStatePtr == nullptr) {
        nativeStatePtr = env->GetFieldID(clazz, "nativeStatePtr", "J");
    }
    jlong ptr = env->GetLongField(obj, nativeStatePtr);
    return get_abstract_native_object(ptr);
}

std::shared_ptr<AbstractNativeObject> ffmpeg4kj::util::get_abstract_native_object(jlong ptr) {
    if (ptr == 0) {
        return nullptr;
    }
    auto* state = (State*)ptr;
    return state->ptr;
}

void ffmpeg4kj::util::dispose_java_native_object_ptr(jlong ptr) {
    if (ptr == 0) {
        return;
    }
    auto* state = (State*)ptr;
    state->ptr = nullptr;
    delete state;
}

void ffmpeg4kj::util::set_abstract_native_object(JNIEnv* env, jobject obj, std::shared_ptr<AbstractNativeObject> nativeObject) {
    static jclass clazz = jni_FindClass(env, clazz, AbstractNativeObject_JAVA_TYPE_NAME);
    static jfieldID nativeStatePtr = nullptr;
    if (nativeStatePtr == nullptr) {
        nativeStatePtr = env->GetFieldID(clazz, "nativeStatePtr", "J");
    }

    jlong ptr = env->GetLongField(obj, nativeStatePtr);

    State* state = nullptr;
    if (ptr == 0 && nativeObject == nullptr) {
        return;

    } else if (ptr == 0 && nativeObject != nullptr) {
        state = new State();
        state->ptr = nativeObject;

    } else if (ptr != 0 && nativeObject == nullptr) {
        state = (State*)ptr;
        state->ptr = nullptr;
        delete state;
        state = nullptr;

    } else if (ptr != 0 && nativeObject != nullptr) {
        state = (State*)ptr;
        state->ptr = nativeObject;
    }

    env->SetLongField(obj, nativeStatePtr, (jlong)state);
}
