
#ifndef FFMPEG4KJ_PARSERNATIVEOBJECT_H
#define FFMPEG4KJ_PARSERNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "CodecContextNativeObject.h"
#include "PacketNativeObject.h"

#define ParserNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Parser"

namespace ffmpeg4kj::util {

    class ParserNativeObject : public AbstractNativeObject {
    public:
        ~ParserNativeObject() override;
        explicit ParserNativeObject(AVCodecParserContext* context);
        ParserNativeObject(const ParserNativeObject& other);
        ParserNativeObject(ParserNativeObject&& other) noexcept;
        ParserNativeObject& operator=(ParserNativeObject other);
        friend void swap(ParserNativeObject& lhs, ParserNativeObject& rhs);

        static std::shared_ptr<ParserNativeObject> createParser(AVCodecID codecId);

        AVCodecParserContext* getContext();
        AVCodecParserContext* getRequiredContext();

        void update(const uint8_t* data, const int size);

        bool parse(std::shared_ptr<CodecContextNativeObject> codecContext,
                std::shared_ptr<PacketNativeObject> packet,
                int64_t pts = 0, int64_t dts = 0, int64_t pos = AV_NOPTS_VALUE);

        int parse(std::shared_ptr<CodecContextNativeObject> codecContext,
                   uint8_t **outputBuffer, int *outputSize,
                   uint8_t *inputBuffer, int inputSize,
                   int64_t pts = 0, int64_t dts = 0, int64_t pos = AV_NOPTS_VALUE);

        void free();

    private:
        AVCodecParserContext* context;
        std::vector<uint8_t> buffer;

    };
    void swap(ParserNativeObject& lhs, ParserNativeObject& rhs);

}


#endif //FFMPEG4KJ_PARSERNATIVEOBJECT_H
