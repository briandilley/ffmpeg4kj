
#ifndef FFMPEG4KJ_FORMATCONTEXTNATIVEOBJECT_H
#define FFMPEG4KJ_FORMATCONTEXTNATIVEOBJECT_H

extern "C" {
#include <libavformat/avformat.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "StreamNativeObject.h"
#include "IOContextNativeObject.h"

#define FormatContextNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/Muxer"

namespace ffmpeg4kj::util {

    typedef void (*AVFormatContextFreePtr)(AVFormatContext**);
    typedef void (*AVFormatContextFree)(AVFormatContext*);

    class FormatContextNativeObject : public AbstractNativeObject {
    public:
        ~FormatContextNativeObject() override;
        FormatContextNativeObject();
        explicit FormatContextNativeObject(AVFormatContext* context);
        FormatContextNativeObject(const FormatContextNativeObject& other);
        FormatContextNativeObject(FormatContextNativeObject&& other) noexcept;
        FormatContextNativeObject& operator=(FormatContextNativeObject other);
        friend void swap(FormatContextNativeObject& lhs, FormatContextNativeObject& rhs);

        virtual AVFormatContext* getFormatContext();
        virtual AVFormatContext* getRequiredFormatContext();

        virtual int getStreamCount();
        virtual std::shared_ptr<StreamNativeObject> getStream(int index);
        virtual void free(AVFormatContextFreePtr free);
        virtual void free(AVFormatContextFree free);
        virtual void dump(bool isOutput);

    private:
        AVFormatContext* context;

    };
    void swap(FormatContextNativeObject& lhs, FormatContextNativeObject& rhs);

}

#endif //FFMPEG4KJ_FORMATCONTEXTNATIVEOBJECT_H
