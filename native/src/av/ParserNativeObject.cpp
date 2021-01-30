
#include "ParserNativeObject.h"

using namespace ffmpeg4kj::util;


std::shared_ptr<ParserNativeObject> ParserNativeObject::createParser(AVCodecID codecId) {
    AVCodecParserContext* parser = av_parser_init(codecId);
    if (parser == nullptr) {
        throw Poco::InvalidArgumentException("Parser not found for codec" + std::to_string(codecId));
    }
    return std::make_shared<ParserNativeObject>(parser);
}

ParserNativeObject::~ParserNativeObject() {
    if (this->context != nullptr) {
        av_parser_close(this->context);
    }
    this->context = nullptr;
    this->buffer.clear();
}

ParserNativeObject::ParserNativeObject(AVCodecParserContext* stream) :
        AbstractNativeObject(ParserNativeObject_JAVA_TYPE_NAME),
        context(stream),
        buffer() {

}

ParserNativeObject::ParserNativeObject(const ParserNativeObject& other) :
        AbstractNativeObject(other),
        context(other.context),
        buffer(other.buffer) {
}

ParserNativeObject::ParserNativeObject(ParserNativeObject&& other) noexcept :
        AbstractNativeObject(std::move(other)),
        context(nullptr),
        buffer() {
    swap(*this, other);
}

ParserNativeObject& ParserNativeObject::operator=(ParserNativeObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(ParserNativeObject& lhs, ParserNativeObject& rhs) {
    std::swap(static_cast<AbstractNativeObject&>(lhs), static_cast<AbstractNativeObject&>(rhs));
    std::swap(lhs.context, rhs.context);
    std::swap(lhs.buffer, rhs.buffer);
}

AVCodecParserContext* ParserNativeObject::getContext() {
    return this->context;
}

AVCodecParserContext* ParserNativeObject::getRequiredContext() {
    if (this->context == nullptr) {
        throw Poco::IllegalStateException("AVCodecParserContext has been freed");
    }
    return this->context;
}


void ParserNativeObject::update(const uint8_t* data, const int size) {
    std::copy(data, data + size, std::back_inserter(buffer));
}

bool ParserNativeObject::parse(
        std::shared_ptr<CodecContextNativeObject> codecContext,
        std::shared_ptr<PacketNativeObject> packet,
        int64_t pts, int64_t dts, int64_t pos) {

    uint8_t* outputBuffer = nullptr;
    int outputSize = 0;

    int read = this->parse(
            codecContext,
            &outputBuffer, &outputSize,
            &this->buffer[0], this->buffer.size(),
            pts, dts, pos);

    if (outputSize > 0) {
        int bufferSize = (outputSize + AV_INPUT_BUFFER_PADDING_SIZE);
        auto packetBuffer = packet->getBuffer();
        if (packetBuffer == nullptr || !packetBuffer->isWritable()) {
            packet->allocateBuffer(bufferSize);
            packetBuffer = packet->getBuffer();
        } else if (packetBuffer->getSize() < bufferSize) {
            packet->growBuffer(bufferSize - packetBuffer->getSize());
            packetBuffer = packet->getBuffer();
        }
        std::memcpy(packet->getPacket()->data, outputBuffer, outputSize);
        packet->getPacket()->size = outputSize;
        packet->getPacket()->buf->size = outputSize;
    }

    if (read > 0) {
        this->buffer.erase(this->buffer.begin(), this->buffer.begin() + read);
    }

    return outputSize > 0;
}

int ParserNativeObject::parse(std::shared_ptr<CodecContextNativeObject> codecContext,
           uint8_t **outputBuffer, int *outputSize,
           uint8_t *inputBuffer, int inputSize,
           int64_t pts, int64_t dts, int64_t pos) {

    int ret = av_parser_parse2(
            this->getRequiredContext(),
            codecContext->getRequiredCodecContext(),
            outputBuffer, outputSize,
            inputBuffer, inputSize,
            pts, dts, pos);

    if (ret < 0) {
        throw Poco::RuntimeException(
                "Unable to av_parser_parse2 (" + ffmpeg_error_string(ret) + ")");
    }

    return ret;
}

void ParserNativeObject::free() {
    this->buffer.clear();
    av_parser_close(this->context);
    this->context = nullptr;
}
