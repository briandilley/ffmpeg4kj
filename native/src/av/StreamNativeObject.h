
#ifndef FFMPEG4KJ_STREAMNATIVEOBJECT_H
#define FFMPEG4KJ_STREAMNATIVEOBJECT_H

extern "C" {
#include <libavformat/avformat.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "EncoderNativeObject.h"
#include "DecoderNativeObject.h"

#define StreamNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Stream"

namespace ffmpeg4kj::util {

    class StreamNativeObject : public AbstractNativeObject {
    public:
        ~StreamNativeObject() override;
        explicit StreamNativeObject(AVStream* stream);
        StreamNativeObject(const StreamNativeObject& other);
        StreamNativeObject(StreamNativeObject&& other) noexcept;
        StreamNativeObject& operator=(StreamNativeObject other);
        friend void swap(StreamNativeObject& lhs, StreamNativeObject& rhs);

        AVStream* getStream();
        std::shared_ptr<CodecParametersNativeObject> getParameters();
        void setParameters(std::shared_ptr<CodecParametersNativeObject> params);

        std::shared_ptr<EncoderNativeObject> createEncoder();
        std::shared_ptr<DecoderNativeObject> createDecoder();

        std::shared_ptr<CodecNativeObject> getEncoderCodec();
        std::shared_ptr<CodecNativeObject> getDecoderCodec();

    private:
        AVStream* stream;

    };
    void swap(StreamNativeObject& lhs, StreamNativeObject& rhs);

}


#endif //FFMPEG4KJ_STREAMNATIVEOBJECT_H
