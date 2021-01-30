
#include "RationalNativeObject.h"

using namespace ffmpeg4kj::util;

RationalNativeObject::~RationalNativeObject() {
    this->rationalRef = nullptr;
    this->rational.den = -1;
    this->rational.num = -1;
}

RationalNativeObject::RationalNativeObject() :
        AbstractNativeObject(RationalNativeObject_JAVA_TYPE_NAME),
        rationalRef(nullptr),
        rational({0, 0}) {

}

RationalNativeObject::RationalNativeObject(AVRational* rationalRef) :
        AbstractNativeObject(RationalNativeObject_JAVA_TYPE_NAME),
        rationalRef(rationalRef),
        rational({0, 0}) {

}

RationalNativeObject::RationalNativeObject(const RationalNativeObject& other) :
        AbstractNativeObject(other),
        rationalRef(other.rationalRef),
        rational(other.rational) {
}

RationalNativeObject::RationalNativeObject(RationalNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        rationalRef(nullptr),
        rational({0,0}) {
    swap(*this, other);
}

RationalNativeObject& RationalNativeObject::operator=(RationalNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(RationalNativeObject& lhs, RationalNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.rationalRef, rhs.rationalRef);
    std::swap(lhs.rational, rhs.rational);
}

AVRational* RationalNativeObject::getRational() {
    return this->rationalRef != nullptr
        ? this->rationalRef
        : &this->rational;
}
