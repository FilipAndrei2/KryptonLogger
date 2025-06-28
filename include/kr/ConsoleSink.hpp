//
// Created by filan on 28.06.2025.
//

#pragma once
#include <memory>

#include "kr/ISink.hpp"

namespace kr {
    class ConsoleSink : public ISink {
    public:
        ConsoleSink(std::ostream& ostream, LogLevel LogLevel);

        ~ConsoleSink() override = default;

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
