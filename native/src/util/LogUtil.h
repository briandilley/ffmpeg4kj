
#ifndef STREAMHUB_LOGUTIL_H
#define STREAMHUB_LOGUTIL_H

#include <memory>
#include <utility>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/AutoPtr.h>

#ifdef _DEBUG
#define POCO_LOG_LEVEL Poco::Message::PRIO_TRACE
#else
#define POCO_LOG_LEVEL Poco::Message::PRIO_INFORMATION
#endif

#define LOG_ASSERT(logger, condition) \
    if (!(condition)) { \
        logger.critical("Assertion failed: %[0]s", std::string(""#condition"")); \
        poco_assert(condition); \
    }

namespace ffmpeg4kj::util {

    void initializeLogging();

    Poco::Logger& getLogger(const std::string& name);

    /**
     * Just a simple class that can be subclassed by other objects that
     * want to have logging functionality
     */
    class AbstractLoggingObject {
    public:
        virtual ~AbstractLoggingObject() = default;
        AbstractLoggingObject() = delete;
        explicit AbstractLoggingObject(const std::string& loggerName);
        AbstractLoggingObject(const AbstractLoggingObject& other);
        AbstractLoggingObject(AbstractLoggingObject&& other) noexcept;
        AbstractLoggingObject& operator=(AbstractLoggingObject other);
        friend void swap(AbstractLoggingObject& lhs, AbstractLoggingObject& rhs);
        Poco::Logger& getLogger();
    protected:
        Poco::Logger& LOGGER;
    };
    void swap(AbstractLoggingObject& lhs, AbstractLoggingObject& rhs);

}

#endif //STREAMHUB_LOGUTIL_H
