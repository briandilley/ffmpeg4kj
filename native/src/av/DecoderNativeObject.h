
#ifndef FFMPEG4KJ_DECODERNATIVEOBJECT_H
#define FFMPEG4KJ_DECODERNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/dict.h>
}

#include <memory>
#include "CodecContextNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "PacketNativeObject.h"
#include "FrameNativeObject.h"

#define DecoderNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Decoder"

namespace ffmpeg4kj::util {

    class DecoderNativeObject : public CodecContextNativeObject {
    public:
        ~DecoderNativeObject() override;
        explicit DecoderNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context);
        DecoderNativeObject(const DecoderNativeObject& other);
        DecoderNativeObject(DecoderNativeObject&& other) noexcept;
        DecoderNativeObject& operator=(DecoderNativeObject other);
        friend void swap(DecoderNativeObject& lhs, DecoderNativeObject& rhs);

        static std::shared_ptr<DecoderNativeObject> createDecoder(std::shared_ptr<CodecNativeObject> codec);

        bool isEof();
        bool sendPacket(std::shared_ptr<PacketNativeObject> packet);
        bool receiveFrame(std::shared_ptr<FrameNativeObject> frame);
        bool flush();
        void free() override;

    private:
        bool eof;

    };
    void swap(DecoderNativeObject& lhs, DecoderNativeObject& rhs);

}

#endif //FFMPEG4KJ_DECODERNATIVEOBJECT_H
