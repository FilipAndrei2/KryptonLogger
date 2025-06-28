#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <string_view>

#include "kr/LogLevel.hpp"
#include "kr/Logger.hpp"

// #define KR_DISABLE_LOGGING
#ifdef KR_DISABLE_LOGGING
#include <string>

#include "LogLevel.hpp"

namespace kr {
    inline constexpr void log(LogLevel level, const char* msg) { }
    inline constexpr void log(LogLevel level, const std::string& msg) { }
    inline constexpr void log(LogLevel level, std::string_view msg) { }

    inline constexpr void logTrace(const char* msg) { }
    inline constexpr void logTrace(const std::string& msg) { }
    inline constexpr void logTrace(std::string_view msg) { }

    inline constexpr void logDebug(const char* msg) { }
    inline constexpr void logDebug(const std::string& msg) { }
    inline constexpr void logDebug(std::string_view msg) { }

    inline constexpr void logInfo(const char* msg) { }
    inline constexpr void logInfo(const std::string& msg) { }
    inline constexpr void logInfo(std::string_view msg) { }

    inline constexpr void logWarning(const char* msg) { }
    inline constexpr void logWarning(const std::string& msg) { }
    inline constexpr void logWarning(std::string_view msg) { }

    inline constexpr void logError(const char* msg) { }
    inline constexpr void logError(const std::string& msg) { }
    inline constexpr void logError(std::string_view msg) { }

    inline constexpr void logFatal(const char* msg) { }
    inline constexpr void logFatal(const std::string& msg) { }
    inline constexpr void logFatal(std::string_view msg) { }
}

#else
namespace kr {
    namespace _internal {
        inline std::mutex g_LoggerMutex;
        inline std::unique_ptr<Logger> g_Logger = nullptr;
    }

    inline constexpr void changeLogger(Logger& logger) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger = std::make_unique<Logger>(logger);
    }

    inline constexpr void log(LogLevel level, const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(level, msg);
    }

    inline constexpr void log(LogLevel level, const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(level, msg);
    }

    inline constexpr void log(LogLevel level, std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(level, msg);
    }

    inline constexpr void logTrace(const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Trace, msg);
    }

    inline constexpr void logTrace(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Trace, msg);
    }

    inline constexpr void logTrace(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Trace, msg);
    }

    inline constexpr void logDebug(const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Debug, msg);
    }

    inline constexpr void logDebug(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Trace, msg);
    }

    inline constexpr void logDebug(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Trace, msg);
    }

    inline constexpr void logInfo(const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Info, msg);
    }

    inline constexpr void logInfo(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Info, msg);
    }

    inline constexpr void logInfo(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Info, msg);
    }

    inline constexpr void logWarning(const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Warning, msg);
    }

    inline constexpr void logWarning(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Warning, msg);
    }

    inline constexpr void logWarning(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Warning, msg);
    }

    inline constexpr void logError(const char* msg)  {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Error, msg);
    }
    inline constexpr void logError(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Error, msg);
    }
    inline constexpr void logError(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Error, msg);
    }

    inline constexpr void logFatal(const char* msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Fatal, msg);
    }

    inline constexpr void logFatal(const std::string& msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Fatal, msg);
    }

    inline constexpr void logFatal(std::string_view msg) {
        using namespace _internal;
        std::lock_guard lock(g_LoggerMutex);
        g_Logger->log(LogLevel::Fatal, msg);
    }
}
#endif