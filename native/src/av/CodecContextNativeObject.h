
#ifndef FFMPEG4KJ_CODECCONTEXTNATIVEOBJECT_H
#define FFMPEG4KJ_CODECCONTEXTNATIVEOBJECT_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/dict.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "CodecParametersNativeObject.h"
#include "CodecNativeObject.h"

#define CodecContextNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/CodecContext"

namespace ffmpeg4kj::util {

    class CodecContextNativeObject : public AbstractNativeObject {
    public:
        ~CodecContextNativeObject() override;
        explicit CodecContextNativeObject(std::shared_ptr<CodecNativeObject> codec, AVCodecContext* context);
        CodecContextNativeObject(const CodecContextNativeObject& other);
        CodecContextNativeObject(CodecContextNativeObject&& other) noexcept;
        CodecContextNativeObject& operator=(CodecContextNativeObject other);
        friend void swap(CodecContextNativeObject& lhs, CodecContextNativeObject& rhs);

        virtual std::shared_ptr<CodecNativeObject> getCodec();
        virtual AVCodecContext* getCodecContext();

        virtual std::shared_ptr<CodecNativeObject> getRequiredCodec();
        virtual AVCodecContext* getRequiredCodecContext();

        virtual void open(const std::string& openOptions = "");
        virtual bool isOpen();
        virtual void setParameters(std::shared_ptr<CodecParametersNativeObject> params);
        virtual void getParameters(std::shared_ptr<CodecParametersNativeObject> params);
        virtual void free();
        virtual void allocateExtraData(int size);
        virtual void deallocateExtraData();

    private:
        std::shared_ptr<CodecNativeObject> codec;
        AVCodecContext* context;
        bool _open;
        bool selfAllocatedExtraData = false;

    };
    void swap(CodecContextNativeObject& lhs, CodecContextNativeObject& rhs);

}

#endif //FFMPEG4KJ_CODECCONTEXTNATIVEOBJECT_H
