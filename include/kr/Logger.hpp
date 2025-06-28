//
// Created by filan on 25.06.2025.
//

#pragma once

#include "kr/ISink.hpp"

namespace kr {

    class Logger final {
    public:
        Logger() = delete;
        Logger(std::string_view fmt, std::vector<std::unique_ptr<ISink>>&& sinks);
        ~Logger() = default;

    public:
        void setFormat(std::string_view fmt);

        void log(LogLevel level, std::string_view msg);

    private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}