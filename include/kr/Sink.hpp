//
// Created by filan on 25.06.2025.
//
#pragma once

#include <iosfwd>
#include <memory>

#include "kr/LogLevel.hpp"

namespace kr {
    class Sink {
    public:
        Sink() = delete;
        Sink(std::ofstream& out, LogLevel level);
        Sink(const char* filePath, LogLevel level);

        virtual ~Sink();
    public:
        /**
         * Writes the message, without \n
         */
        void write(const char* message);

        /**
         * \n's the stream and flushes it's content
         */
        void flush();

        /**
         *
         * @param level
         * @return sink.level >= level
         */
        bool checkIfCanWrite(LogLevel level);
    public:
        LogLevel getLogLevel();
        void setLogLevel(LogLevel p_LogLevel);

    private:
        class SinkImpl;
        std::unique_ptr<SinkImpl> m_Pimpl;
    };
}

