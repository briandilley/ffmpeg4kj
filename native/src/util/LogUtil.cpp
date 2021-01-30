
#include "LogUtil.h"

using namespace ffmpeg4kj::util;

AbstractLoggingObject::AbstractLoggingObject(const std::string &loggerName) :
        LOGGER(ffmpeg4kj::util::getLogger(loggerName)) {
}

AbstractLoggingObject::AbstractLoggingObject(const AbstractLoggingObject &other) :
        LOGGER(other.LOGGER) {
}

AbstractLoggingObject::AbstractLoggingObject(AbstractLoggingObject &&other) noexcept :
        LOGGER(std::move(other).LOGGER) {
    swap(*this, other);
}

AbstractLoggingObject& AbstractLoggingObject::operator=(AbstractLoggingObject other) {
    swap(*this, other);
    return *this;
}

void ffmpeg4kj::util::swap(AbstractLoggingObject& lhs, AbstractLoggingObject& rhs) {
    // no-op
}

Poco::Logger& AbstractLoggingObject::getLogger() {
    return LOGGER;
}

void ffmpeg4kj::util::initializeLogging() {
    auto* formatter = new Poco::PatternFormatter();
    formatter->setProperty("pattern", "[%Y-%m-%d %H:%M:%S %q] [%v[30]] %t");
    auto* channel = new Poco::FormattingChannel(formatter, new Poco::ConsoleChannel());
    Poco::Logger& LOGGER = Poco::Logger::root();
    LOGGER.setChannel(channel);
    LOGGER.setLevel(POCO_LOG_LEVEL);
}

Poco::Logger& ffmpeg4kj::util::getLogger(const std::string &name) {
    static bool loggingInitialized = false;
    if (!loggingInitialized) {
        initializeLogging();
        loggingInitialized = true;
    }
    return Poco::Logger::get(name);
}
