
#ifndef FFMPEG4KJ_CODECPARAMETERSNATIVEOBJECT_H
#define FFMPEG4KJ_CODECPARAMETERSNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <memory>
#include "AbstractNativeObject.h"

#define CodecParametersNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/CodecParameters"

namespace ffmpeg4kj::util {

    class CodecParametersNativeObject : public AbstractNativeObject {
    public:
        ~CodecParametersNativeObject() override;
        CodecParametersNativeObject();
        explicit CodecParametersNativeObject(AVCodecParameters* paramsRef);
        CodecParametersNativeObject(const CodecParametersNativeObject& other);
        CodecParametersNativeObject(CodecParametersNativeObject&& other) noexcept;
        CodecParametersNativeObject& operator=(CodecParametersNativeObject other);
        friend void swap(CodecParametersNativeObject& lhs, CodecParametersNativeObject& rhs);

        AVCodecParameters* getCodecParameters();

        void copyFrom(std::shared_ptr<CodecParametersNativeObject> other);

    private:
        AVCodecParameters* paramsRef;
        std::shared_ptr<AVCodecParameters> params;

    };
    void swap(CodecParametersNativeObject& lhs, CodecParametersNativeObject& rhs);

}


#endif //FFMPEG4KJ_CODECPARAMETERSNATIVEOBJECT_H
