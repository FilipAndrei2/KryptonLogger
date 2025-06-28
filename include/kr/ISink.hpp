//
// Created by filan on 25.06.2025.
//
#pragma once

#include "kr/LogLevel.hpp"

namespace kr {
    class ISink {
    public:

        virtual ~ISink() = default;
    public:
        /**
         * Writes the message, without \n
         */
        virtual void write(const char* message) = 0;

        /**
         * \n's the stream and flushes it's content
         */
        virtual void flush() = 0;

        /**
         *
         * @param level
         * @return sink.level >= level
         */
        virtual bool checkIfCanWrite(LogLevel level) = 0;

        virtual LogLevel getLogLevel() = 0;

        virtual void setLogLevel(LogLevel p_LogLevel) = 0;
    };
}

