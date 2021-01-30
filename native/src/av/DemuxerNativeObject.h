
#ifndef FFMPEG4KJ_DEMUXERNATIVEOBJECT_H
#define FFMPEG4KJ_DEMUXERNATIVEOBJECT_H

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

#define DemuxerNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Demuxer"

namespace ffmpeg4kj::util {

    class DemuxerNativeObject : public FormatContextNativeObject {
    public:
        ~DemuxerNativeObject() override;
        explicit DemuxerNativeObject(AVFormatContext* context);
        DemuxerNativeObject(const DemuxerNativeObject& other);
        DemuxerNativeObject(DemuxerNativeObject&& other) noexcept;
        DemuxerNativeObject& operator=(DemuxerNativeObject other);
        friend void swap(DemuxerNativeObject& lhs, DemuxerNativeObject& rhs);

        static std::shared_ptr<DemuxerNativeObject> openInput(
                const std::string& url = "",
                const std::string& options = "",
                std::shared_ptr<IOContextNativeObject> ioContext = nullptr);

        void findStreams(const std::string& options = "");
        int findBestStreamIndex(AVMediaType type, int wantedStreamNumber = -1, int relatedStream = -1, int flags = -1);
        bool readFrame(std::shared_ptr<PacketNativeObject> packet);
        void closeInput();

    };
    void swap(DemuxerNativeObject& lhs, DemuxerNativeObject& rhs);

}

#endif //FFMPEG4KJ_DEMUXERNATIVEOBJECT_H
