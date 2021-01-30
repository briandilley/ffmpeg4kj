#ifndef FFMPEG4KJ_FRAMENATIVEOBJECT_H
#define FFMPEG4KJ_FRAMENATIVEOBJECT_H


extern "C" {
#include <libavcodec/avcodec.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "BufferNativeObject.h"
#include "RationalNativeObject.h"

#define FrameNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Frame"

namespace ffmpeg4kj::util {

    class FrameNativeObject : public AbstractNativeObject {
    public:
        ~FrameNativeObject() override;
        explicit FrameNativeObject(std::shared_ptr<AVFrame> frame);
        FrameNativeObject(const FrameNativeObject& other);
        FrameNativeObject(FrameNativeObject&& other) noexcept;
        FrameNativeObject& operator=(FrameNativeObject other);
        friend void swap(FrameNativeObject& lhs, FrameNativeObject& rhs);

        static std::shared_ptr<FrameNativeObject> makeNew();

        std::shared_ptr<AVFrame> getFrame();
        std::shared_ptr<AVFrame> getRequiredFrame();

        void allocateBuffers(int align = 0);
        std::shared_ptr<FrameNativeObject> ref(std::shared_ptr<FrameNativeObject> dest);
        void unref();
        void free();

        std::shared_ptr<BufferNativeObject> getBuffer(int index);
        void setBuffer(int index, std::shared_ptr<BufferNativeObject> buffer, int lineSize);

        uint8_t* getData(int index);
        void setData(int index, uint8_t* data, int lineSize);

    private:
        std::shared_ptr<AVFrame> frame;

    };
    void swap(FrameNativeObject& lhs, FrameNativeObject& rhs);

}


#endif //FFMPEG4KJ_FRAMENATIVEOBJECT_H
