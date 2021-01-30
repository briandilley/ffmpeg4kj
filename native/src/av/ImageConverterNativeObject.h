
#ifndef FFMPEG4KJ_IMAGECONVERTERNATIVEOBJECT_H
#define FFMPEG4KJ_IMAGECONVERTERNATIVEOBJECT_H

extern "C" {
#include <libswscale/swscale.h>
}

#include <memory>
#include "AbstractNativeObject.h"
#include "FrameNativeObject.h"

#define ImageConverterNativeObject_JAVA_TYPE_NAME "ffmpeg4kj/av/ImageConverter"

namespace ffmpeg4kj::util {

    class ImageConverterNativeObject : public AbstractNativeObject {
    public:
        ~ImageConverterNativeObject() override;
        ImageConverterNativeObject(SwsContext* context);
        ImageConverterNativeObject(const ImageConverterNativeObject& other);
        ImageConverterNativeObject(ImageConverterNativeObject&& other) noexcept;
        ImageConverterNativeObject& operator=(ImageConverterNativeObject other);
        friend void swap(ImageConverterNativeObject& lhs, ImageConverterNativeObject& rhs);

        static std::shared_ptr<ImageConverterNativeObject> createNew(
                int srcW, int srcH, AVPixelFormat srcFormat,
                int dstW, int dstH, AVPixelFormat dstFormat,
                int flags);

        SwsContext* getSwsContext();
        SwsContext* getRequiredSwsContext();

        int convert(
                std::shared_ptr<FrameNativeObject> src,
                std::shared_ptr<FrameNativeObject> dst,
                int srcSlice,
                int srcSliceHeight);

        void free();

    private:
        SwsContext* context;

    };
    void swap(ImageConverterNativeObject& lhs, ImageConverterNativeObject& rhs);

}

#endif //FFMPEG4KJ_IMAGECONVERTERNATIVEOBJECT_H
