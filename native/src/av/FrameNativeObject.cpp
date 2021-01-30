
#include "FrameNativeObject.h"

using namespace ffmpeg4kj::util;

static void free_frame(AVFrame* frame) {
    av_frame_free(&frame);
}

static std::shared_ptr<AVFrame> alloc_frame() {
    std::shared_ptr<AVFrame> frame(av_frame_alloc(), free_frame);
    return frame;
}

#define ASSERT_FRAME_NOT_NULL \
    if (this->frame == nullptr) { \
        throw Poco::IllegalStateException("Frame was freed"); \
    }


std::shared_ptr<FrameNativeObject> FrameNativeObject::makeNew() {
    return std::make_shared<FrameNativeObject>(alloc_frame());
}

FrameNativeObject::~FrameNativeObject() {
    this->frame = nullptr;
}

FrameNativeObject::FrameNativeObject(std::shared_ptr<AVFrame> frame) :
        AbstractNativeObject(FrameNativeObject_JAVA_TYPE_NAME),
        frame(frame) {
    if (frame == nullptr) {
        throw Poco::NullPointerException("frame is null");
    }
}

FrameNativeObject::FrameNativeObject(const FrameNativeObject& other) :
        AbstractNativeObject(other),
        frame(other.frame) {
}

FrameNativeObject::FrameNativeObject(FrameNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        frame(nullptr) {
    swap(*this, other);
}

FrameNativeObject& FrameNativeObject::operator=(FrameNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(FrameNativeObject& lhs, FrameNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.frame, rhs.frame);
}

std::shared_ptr<AVFrame> FrameNativeObject::getFrame() {
    return this->frame;
}

std::shared_ptr<AVFrame> FrameNativeObject::getRequiredFrame() {
    ASSERT_FRAME_NOT_NULL
    return this->frame;
}

void FrameNativeObject::allocateBuffers(int align) {
    auto f = this->getRequiredFrame();
    int ret = av_frame_get_buffer(f.get(), align);
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to av_frame_get_buffer (" + ffmpeg_error_string(ret) + ")");
    }
}

std::shared_ptr<FrameNativeObject> FrameNativeObject::ref(std::shared_ptr<FrameNativeObject> dest) {
    ASSERT_FRAME_NOT_NULL
    if (dest == nullptr) {
        dest = std::make_shared<FrameNativeObject>(alloc_frame());
    } else if (dest->frame == nullptr) {
        throw Poco::IllegalStateException("Destination frame is null");
    }

    int ret = av_frame_ref(dest->frame.get(), this->frame.get());
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to av_frame_ref (" + ffmpeg_error_string(ret) + ")");
    }
    return dest;
}

void FrameNativeObject::unref() {
    ASSERT_FRAME_NOT_NULL
    av_frame_unref(this->frame.get());
}

void FrameNativeObject::free() {
    this->frame = nullptr;
}

std::shared_ptr<BufferNativeObject> FrameNativeObject::getBuffer(int index) {
    ASSERT_FRAME_NOT_NULL
    return this->frame->buf[index] != nullptr
           ? std::make_shared<BufferNativeObject>(this->frame->buf[index])
           : nullptr;
}

void FrameNativeObject::setBuffer(int index, std::shared_ptr<BufferNativeObject> buffer, int lineSize) {
    ASSERT_FRAME_NOT_NULL

    auto oldBuffer = this->frame->buf[index];
    auto newBuffer = (buffer != nullptr) ? buffer->getBuffer() : nullptr;

    if (oldBuffer == newBuffer) {
        return;
    }

    if (oldBuffer != nullptr) {
        av_buffer_unref(&oldBuffer);
    }

    if (newBuffer != nullptr) {
        av_buffer_ref(newBuffer);
    }

    if (newBuffer == nullptr) {
        this->frame->buf[index] = nullptr;
        this->frame->data[index] = nullptr;
        this->frame->linesize[index] = lineSize;

    } else {
        this->frame->buf[index] = newBuffer;
        this->frame->data[index] = newBuffer->data;
        this->frame->linesize[index] = lineSize;
    }
}

uint8_t* FrameNativeObject::getData(int index) {
    ASSERT_FRAME_NOT_NULL
    return this->frame->data[index];
}

void FrameNativeObject::setData(int index, uint8_t* data, int lineSize) {
    ASSERT_FRAME_NOT_NULL
    this->frame->data[index] = data;
    this->frame->linesize[index] = lineSize;
}
