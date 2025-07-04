//
// Created by filan on 28.06.2025.
//

#pragma once

#include <memory>

#include "kr/ISink.hpp"


namespace kr {
    class FileSink : public kr::ISink {
    public:
        FileSink(const char* filePath, LogLevel LogLevel);
        FileSink(std::string& filePath, LogLevel LogLevel);
        FileSink(std::string_view filePath, LogLevel LogLevel);

        ~FileSink() override;

        void write(const char *message) override;

        void flush() override;

        bool checkIfCanWrite(LogLevel level) override;

        LogLevel getLogLevel() override;

        void setLogLevel(LogLevel p_LogLevel) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_PImpl;
    };
}

