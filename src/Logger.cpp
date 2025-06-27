//
// Created by filan on 25.06.2025.
//

#include "kr/Logger.hpp"

#include <iomanip>

#include "kr/Sink.hpp"

#include <list>

using namespace  kr;

class Logger::Impl {
public:
    Impl(std::string_view fmt, std::vector<std::unique_ptr<Sink>>&& sinks)
        : m_FormatedMsgBuff(), m_TimestampStrBuff(), m_Format(fmt), m_Sinks(std::move(sinks)) {
        m_FormatedMsgBuff.reserve(1024);
        m_TimestampStrBuff.reserve(128);
        m_Sinks.reserve(sinks.size());
    }

    void setFormat(std::string_view fmt) { m_Format = fmt; }

    void log(LogLevel p_Level, std::string_view p_Msg) {
        time_t logTime = time(nullptr);
        if (!needsToWrite(p_Level)) {
            return;
        }

        createFormmatedMsgBuff(logTime, p_Msg, p_Level);

        sendFormmatedMsg();
    }
private:
    std::string m_TimestampStrBuff;
    std::ostringstream m_Oss;
    constexpr std::string timestampToString(time_t p_time) {
        m_Oss.clear();
        std::tm tm = *std::localtime(&p_time);

        m_Oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return m_Oss.str();
    }


    static constexpr std::string_view c_TraceStr   = "[TRACE]";
    static constexpr std::string_view c_DebugStr   = "[DEBUG]";
    static constexpr std::string_view c_InfoStr    = "[INFO]";
    static constexpr std::string_view c_WarningStr = "[WARNING]";
    static constexpr std::string_view c_ErrorStr   = "[ERROR]";
    static constexpr std::string_view c_FatalStr   = "[FATAL]";
    static constexpr std::string_view c_UnknownStr = "[LOG]";

    constexpr std::string_view logLevelToString(LogLevel p_Level) {
        switch (p_Level) {
            case LogLevel::Trace:
                return c_TraceStr;
            case LogLevel::Debug:
                return c_DebugStr;
            case LogLevel::Info:
                return c_InfoStr;
            case LogLevel::Warning:
                return c_WarningStr;
            case LogLevel::Error:
                return c_ErrorStr;
            case LogLevel::Fatal:
                return c_FatalStr;
            default:
                return c_UnknownStr;
        }
    }

    constexpr void createFormmatedMsgBuff(time_t p_LogTime, std::string_view p_Msg, LogLevel p_Level) {
        m_FormatedMsgBuff.clear();
        for (auto i = m_Format.begin(); i != m_Format.end(); ++i) {
            if (*i != '%') {
                m_FormatedMsgBuff += *i;
                continue;
            }

            ++i;
            switch (*i) {
                case 't':
                case 'T':
                    m_FormatedMsgBuff += timestampToString(p_LogTime);
                    break;

                case 'l':
                case 'L':
                    m_FormatedMsgBuff += logLevelToString(p_Level);
                    break;

                case 'm':
                case 'M':
                    m_FormatedMsgBuff += p_Msg;
                    break;
                default:
                    m_FormatedMsgBuff += '%';
                    m_FormatedMsgBuff += *i;
            }
        }
    }

    /**
     * Checks if you have atleast 1 sink that cand receive the message
     * @param p_Level
     * @return
     */
    constexpr bool needsToWrite(LogLevel p_Level) {
        for (auto& sink : m_Sinks) {
            if (sink->checkIfCanWrite(p_Level)) {
                return true;
            }
        }
        return false;
    }

    constexpr void sendFormmatedMsg() {
        const char* ptrToMsg = m_FormatedMsgBuff.c_str();
        for (auto& sink : m_Sinks) {
            sink->write(ptrToMsg);
            sink->flush();
        }
    }

private:
    std::string m_FormatedMsgBuff;
    std::vector<std::unique_ptr<Sink>> m_Sinks;
    std::string m_Format;
};