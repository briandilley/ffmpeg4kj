
#ifndef FFMPEG4KJ_PACKETNATIVEOBJECT_H
#define FFMPEG4KJ_PACKETNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "BufferNativeObject.h"
#include "RationalNativeObject.h"

#define PacketNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Packet"

namespace ffmpeg4kj::util {

    class PacketNativeObject : public AbstractNativeObject {
    public:
        ~PacketNativeObject() override;
        PacketNativeObject();
        PacketNativeObject(const PacketNativeObject& other);
        PacketNativeObject(PacketNativeObject&& other) noexcept;
        PacketNativeObject& operator=(PacketNativeObject other);
        friend void swap(PacketNativeObject& lhs, PacketNativeObject& rhs);

        AVPacket* getPacket();

        void rescale(std::shared_ptr<RationalNativeObject> tbSrc, std::shared_ptr<RationalNativeObject> tbDst);
        void allocateBuffer(int size);
        void shrinkBuffer(int size);
        void growBuffer(int size);
        std::shared_ptr<PacketNativeObject> ref(std::shared_ptr<PacketNativeObject> dest);
        void unref();
        void init();
        std::shared_ptr<BufferNativeObject> getBuffer();
        void setBuffer(std::shared_ptr<BufferNativeObject> buffer);
        void setData(uint8_t* data, int size);

    private:
        AVPacket packet;

    };
    void swap(PacketNativeObject& lhs, PacketNativeObject& rhs);

}

#endif //FFMPEG4KJ_PACKETNATIVEOBJECT_H
