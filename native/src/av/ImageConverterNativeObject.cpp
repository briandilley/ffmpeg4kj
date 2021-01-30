
#include "ImageConverterNativeObject.h"

using namespace ffmpeg4kj::util;

ImageConverterNativeObject::~ImageConverterNativeObject() {

}

ImageConverterNativeObject::ImageConverterNativeObject(SwsContext* context) :
        AbstractNativeObject(ImageConverterNativeObject_JAVA_TYPE_NAME),
        context(context) {
}

ImageConverterNativeObject::ImageConverterNativeObject(const ImageConverterNativeObject& other) :
        AbstractNativeObject(other),
        context(other.context) {

}

ImageConverterNativeObject::ImageConverterNativeObject(ImageConverterNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        context(nullptr) {
    swap(*this, other);
}

ImageConverterNativeObject& ImageConverterNativeObject::operator=(ImageConverterNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(ImageConverterNativeObject& lhs, ImageConverterNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.context, rhs.context);
}

SwsContext* ImageConverterNativeObject::getSwsContext() {
    return this->context;
}

SwsContext* ImageConverterNativeObject::getRequiredSwsContext() {
    if (this->context == nullptr) {
        throw Poco::IllegalStateException("SwsContext is null");
    }
    return this->context;
}

std::shared_ptr<ImageConverterNativeObject> ImageConverterNativeObject::createNew(
        int srcW, int srcH, AVPixelFormat srcFormat,
        int dstW, int dstH, AVPixelFormat dstFormat,
        int flags) {

    SwsContext* context = sws_getContext(
            srcW, srcH, srcFormat,
            dstW, dstH, dstFormat,
            flags, nullptr, nullptr, nullptr);

    if (context == nullptr) {
        throw Poco::RuntimeException("Unable to sws_getContext");
    }

    return std::make_shared<ImageConverterNativeObject>(context);
}

int ImageConverterNativeObject::convert(
        std::shared_ptr<FrameNativeObject> src,
        std::shared_ptr<FrameNativeObject> dst,
        int srcSlice,
        int srcSliceHeight) {

    std::shared_ptr<AVFrame> srcFrame = src->getRequiredFrame();
    std::shared_ptr<AVFrame> dstFrame = dst->getRequiredFrame();

    int ret = sws_scale(this->getRequiredSwsContext(),
                        srcFrame->data, srcFrame->linesize, srcSlice, srcSliceHeight,
                        dstFrame->data, dstFrame->linesize);
    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to sws_scale (" + ffmpeg_error_string(ret) + ")");
    }

    return ret;
}

void ImageConverterNativeObject::free() {
    if (this->context == nullptr) {
        return;
    }
    sws_freeContext(this->context);
    this->context = nullptr;
}
