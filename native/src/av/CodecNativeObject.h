
#ifndef FFMPEG4KJ_CODECNATIVEOBJECT_H
#define FFMPEG4KJ_CODECNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <memory>
#include "AbstractNativeObject.h"

#define CodecNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Codec"

namespace ffmpeg4kj::util {

    class CodecNativeObject : public AbstractNativeObject {
    public:
        ~CodecNativeObject() override;
        explicit CodecNativeObject(AVCodec* codec);
        CodecNativeObject(const CodecNativeObject& other);
        CodecNativeObject(CodecNativeObject&& other) noexcept;
        CodecNativeObject& operator=(CodecNativeObject other);
        friend void swap(CodecNativeObject& lhs, CodecNativeObject& rhs);

        static std::shared_ptr<CodecNativeObject> findEncoderByName(std::string& name);
        static std::shared_ptr<CodecNativeObject> findEncoderById(AVCodecID id);

        static std::shared_ptr<CodecNativeObject> findDecoderByName(std::string& name);
        static std::shared_ptr<CodecNativeObject> findDecoderById(AVCodecID id);

        AVCodec* getCodec();
        AVCodec* getRequiredCodec();

        AVCodecID getId();
        int getType();
        int getCapabilities();
        std::string getName();
        std::string getWrapperName();
        std::string getLongName();

    private:
        AVCodec* codec;

    };
    void swap(CodecNativeObject& lhs, CodecNativeObject& rhs);

}

#endif //FFMPEG4KJ_CODECNATIVEOBJECT_H
