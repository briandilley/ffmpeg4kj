
#ifndef FFMPEG4KJ_RATIONALNATIVEOBJECT_H
#define FFMPEG4KJ_RATIONALNATIVEOBJECT_H

extern "C" {
#include <libavutil/rational.h>
}

#include <memory>
#include "AbstractNativeObject.h"

#define RationalNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Rational"

namespace ffmpeg4kj::util {

    class RationalNativeObject : public AbstractNativeObject {
    public:
        ~RationalNativeObject() override;
        RationalNativeObject();
        explicit RationalNativeObject(AVRational* rationalRef);
        RationalNativeObject(const RationalNativeObject& other);
        RationalNativeObject(RationalNativeObject&& other) noexcept;
        RationalNativeObject& operator=(RationalNativeObject other);
        friend void swap(RationalNativeObject& lhs, RationalNativeObject& rhs);

        AVRational* getRational();

    private:
        AVRational* rationalRef;
        AVRational rational;

    };
    void swap(RationalNativeObject& lhs, RationalNativeObject& rhs);

}

#endif //FFMPEG4KJ_RATIONALNATIVEOBJECT_H
