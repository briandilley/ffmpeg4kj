
#ifndef FFMPEG4KJ_ENCODERNATIVEOBJECT_H
#define FFMPEG4KJ_ENCODERNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/dict.h>
}

#include <memory>
#include "CodecContextNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "PacketNativeObject.h"
#include "FrameNativeObject.h"

#define EncoderNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Encoder"

namespace ffmpeg4kj::util {

    class EncoderNativeObject : public CodecContextNativeObject {
    public:
        ~EncoderNativeObject() override;
        explicit EncoderNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context);
        EncoderNativeObject(const EncoderNativeObject& other);
        EncoderNativeObject(EncoderNativeObject&& other) noexcept;
        EncoderNativeObject& operator=(EncoderNativeObject other);
        friend void swap(EncoderNativeObject& lhs, EncoderNativeObject& rhs);

        static std::shared_ptr<EncoderNativeObject> createEncoder(std::shared_ptr<CodecNativeObject> codec);

        bool isEof();
        bool sendFrame(std::shared_ptr<FrameNativeObject> frame);
        bool receivePacket(std::shared_ptr<PacketNativeObject> packet);
        bool flush();
        void free() override;

    private:
        bool eof;

    };
    void swap(EncoderNativeObject& lhs, EncoderNativeObject& rhs);

}

#endif //FFMPEG4KJ_ENCODERNATIVEOBJECT_H
