
#ifndef FFMPEG4KJ_IOCONTEXTNATIVEOBJECT_H
#define FFMPEG4KJ_IOCONTEXTNATIVEOBJECT_H

extern "C" {
#include <libavformat/avio.h>
}

#include <memory>
#include <functional>
#include "AbstractNativeObject.h"
#include "CodecContextNativeObject.h"
#include "PacketNativeObject.h"

#define IOContextNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/IOContext"
#define ReadFunction_JAVA_TYPE_NAME "ffmpeg4kj/av/ReadFunction"
#define WriteFunction_JAVA_TYPE_NAME "ffmpeg4kj/av/WriteFunction"
#define SeekFunction_JAVA_TYPE_NAME "ffmpeg4kj/av/SeekFunction"

namespace ffmpeg4kj::util {

    class IOContextNativeObject : public AbstractNativeObject {
    public:
        ~IOContextNativeObject() override;
        IOContextNativeObject(
                int bufferSize,
                std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> read = nullptr,
                std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> write = nullptr,
                std::function<int64_t(IOContextNativeObject* obj, int64_t offset, int whence)> seek = nullptr);
        IOContextNativeObject(const IOContextNativeObject &other);
        IOContextNativeObject(IOContextNativeObject &&other) noexcept;
        IOContextNativeObject &operator=(IOContextNativeObject other);
        friend void swap(IOContextNativeObject &lhs, IOContextNativeObject &rhs);

        AVIOContext *getContext();
        AVIOContext *getRequiredContext();

        void close();

    private:
        AVIOContext *context;
        std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> read;
        std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> write;
        std::function<int64_t(IOContextNativeObject* obj, int64_t offset, int whence)> seek;

        static int readCallback(void* opaque, uint8_t *buf, int buf_size);
        static int writeCallback(void* opaque, uint8_t *buf, int buf_size);
        static int64_t seekCallback(void* opaque, int64_t offset, int whence);

    };

    void swap(IOContextNativeObject &lhs, IOContextNativeObject &rhs);

    std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> create_read_function_for_java(const std::string& refName);
    std::function<int(IOContextNativeObject* obj, uint8_t *buf, int buf_size)> create_write_function_for_java(const std::string& refName);
    std::function<int64_t(IOContextNativeObject* obj, int64_t offset, int whence)> create_seek_function_for_java(const std::string& refName);

}

#endif //FFMPEG4KJ_IOCONTEXTNATIVEOBJECT_H
