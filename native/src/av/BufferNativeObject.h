#ifndef FFMPEG4KJ_BUFFERNATIVEOBJECT_H
#define FFMPEG4KJ_BUFFERNATIVEOBJECT_H

extern "C" {
#include <libavutil/buffer.h>
#include <libavutil/error.h>
}

#include <memory>
#include "AbstractNativeObject.h"

#define BufferNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Buffer"

namespace ffmpeg4kj::util {

    class BufferNativeObject : public AbstractNativeObject {
    public:
        ~BufferNativeObject() override;
        BufferNativeObject() = delete;
        explicit BufferNativeObject(AVBufferRef* buffer);
        BufferNativeObject(const BufferNativeObject& other);
        BufferNativeObject(BufferNativeObject&& other) noexcept;
        BufferNativeObject& operator=(BufferNativeObject other);
        friend void swap(BufferNativeObject& lhs, BufferNativeObject& rhs);

        static std::shared_ptr<BufferNativeObject> makeNew(int size);

        AVBufferRef* getBuffer();
        int getSize();
        bool isWritable();
        std::shared_ptr<BufferNativeObject> ref();
        void unref();
        void makeWritable();
        int refCount();

    private:
        AVBufferRef* buffer;

    };
    void swap(BufferNativeObject& lhs, BufferNativeObject& rhs);

}

#endif //FFMPEG4KJ_BUFFERNATIVEOBJECT_H
