
#ifndef FFMPEG4KJ_MUXERNATIVEOBJECT_H
#define FFMPEG4KJ_MUXERNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/dict.h>
}

#include <memory>
#include "FormatContextNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "PacketNativeObject.h"
#include "FrameNativeObject.h"
#include "CodecNativeObject.h"
#include "StreamNativeObject.h"
#include "IOContextNativeObject.h"

#define MuxerNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Muxer"

namespace ffmpeg4kj::util {

    class MuxerNativeObject : public FormatContextNativeObject {
    public:
        ~MuxerNativeObject() override;
        explicit MuxerNativeObject(AVFormatContext* context);
        MuxerNativeObject(const MuxerNativeObject& other);
        MuxerNativeObject(MuxerNativeObject&& other) noexcept;
        MuxerNativeObject& operator=(MuxerNativeObject other);
        friend void swap(MuxerNativeObject& lhs, MuxerNativeObject& rhs);

        static std::shared_ptr<MuxerNativeObject> openOutput(
                const std::string& format = "",
                const std::string& filename = "",
                std::shared_ptr<IOContextNativeObject> ioContext = nullptr);

        std::shared_ptr<StreamNativeObject> addStream(std::shared_ptr<CodecNativeObject> codec);
        bool writeHeader(const std::string& options = "");
        void writeFrame(std::shared_ptr<PacketNativeObject> packet);
        bool flushFrames();
        void writeInterleavedFrame(std::shared_ptr<PacketNativeObject> packet);
        void flushInterleavedFrames();
        void writeTrailer();
        void closeOutput();

    private:

    };
    void swap(MuxerNativeObject& lhs, MuxerNativeObject& rhs);

}

#endif //FFMPEG4KJ_MUXERNATIVEOBJECT_H
