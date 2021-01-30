
#include "PacketNativeObject.h"

using namespace ffmpeg4kj::util;

PacketNativeObject::~PacketNativeObject() {

}

PacketNativeObject::PacketNativeObject() :
    AbstractNativeObject(PacketNativeObject_JAVA_TYPE_NAME),
    packet() {
    av_init_packet(&this->packet);
}

PacketNativeObject::PacketNativeObject(const PacketNativeObject& other) :
    AbstractNativeObject(other),
    packet(other.packet) {

}

PacketNativeObject::PacketNativeObject(PacketNativeObject&& other) noexcept :
    AbstractNativeObject(std::move(other)),
    packet() {
    swap(*this, other);
}

PacketNativeObject& PacketNativeObject::operator=(PacketNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(PacketNativeObject& lhs, PacketNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.packet, rhs.packet);
}

AVPacket* PacketNativeObject::getPacket() {
    return &this->packet;
}

void PacketNativeObject::allocateBuffer(int size) {
    int ret = av_new_packet(&this->packet, size);
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to av_new_packet (" + ffmpeg_error_string(ret) + ")");
    }
}

void PacketNativeObject::shrinkBuffer(int size) {
    av_shrink_packet(&this->packet, size);
}

void PacketNativeObject::growBuffer(int size) {
    int ret = av_grow_packet(&this->packet, size);
    if (ret < 0) {
        throw Poco::RuntimeException("Unable to av_grow_packet (" + ffmpeg_error_string(ret) + ")");
    }
}

std::shared_ptr<PacketNativeObject> PacketNativeObject::ref(std::shared_ptr<PacketNativeObject> dest) {
    if (dest == nullptr) {
        dest = std::make_shared<PacketNativeObject>();
    }
    int ret = av_packet_ref(&dest->packet, &this->packet);
    if (ret != 0) {
        throw Poco::RuntimeException("Unable to av_packet_ref (" + ffmpeg_error_string(ret) + ")");
    }
    return dest;
}

void PacketNativeObject::unref() {
    av_packet_unref(&this->packet);
}

void PacketNativeObject::init() {
    av_init_packet(&this->packet);
}

std::shared_ptr<BufferNativeObject> PacketNativeObject::getBuffer() {
    return this->packet.buf != nullptr
        ? std::make_shared<BufferNativeObject>(this->packet.buf)
        : nullptr;
}

void PacketNativeObject::setBuffer(std::shared_ptr<BufferNativeObject> buffer) {

    auto oldBuffer = this->packet.buf;
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
        this->packet.buf = nullptr;
        this->packet.data = nullptr;
        this->packet.size = 0;

    } else {
        this->packet.buf = newBuffer;
        this->packet.data = newBuffer->data;
        this->packet.size = newBuffer->size;
    }
}

void PacketNativeObject::setData(uint8_t* data, int size) {
    this->packet.data = data;
    this->packet.size = size;
}

void PacketNativeObject::rescale(
        std::shared_ptr<RationalNativeObject> tbSrc,
        std::shared_ptr<RationalNativeObject> tbDst) {
    AVRational src = {
        .num = tbSrc->getRational()->num,
        .den = tbSrc->getRational()->den
    };
    AVRational dst = {
        .num = tbDst->getRational()->num,
        .den = tbDst->getRational()->den
    };
    av_packet_rescale_ts(this->getPacket(), src, dst);
}
