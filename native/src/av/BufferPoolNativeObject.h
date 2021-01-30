#ifndef FFMPEG4KJ_BUFFERPOOLNATIVEOBJECT_H
#define FFMPEG4KJ_BUFFERPOOLNATIVEOBJECT_H

extern "C" {
#include <libavutil/buffer.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "BufferNativeObject.h"

#define BufferPoolNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/BufferPool"

namespace ffmpeg4kj::util {

    class BufferPoolNativeObject : public AbstractNativeObject {
    public:
        ~BufferPoolNativeObject() override;
        BufferPoolNativeObject() = delete;
        explicit BufferPoolNativeObject(AVBufferPool* buffer);
        BufferPoolNativeObject(const BufferPoolNativeObject& other);
        BufferPoolNativeObject(BufferPoolNativeObject&& other) noexcept;
        BufferPoolNativeObject& operator=(BufferPoolNativeObject other);
        friend void swap(BufferPoolNativeObject& lhs, BufferPoolNativeObject& rhs);

        static std::shared_ptr<BufferPoolNativeObject> makeNew(int size);

        AVBufferPool* getPool();
        std::shared_ptr<BufferNativeObject> getBuffer();
        void unInit();

    private:
        AVBufferPool* pool;

    };
    void swap(BufferPoolNativeObject& lhs, BufferPoolNativeObject& rhs);

}


#endif //FFMPEG4KJ_BUFFERPOOLNATIVEOBJECT_H
