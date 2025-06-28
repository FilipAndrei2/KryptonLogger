//
// Created by filan on 25.06.2025.
//

#pragma once

#include "kr/ISink.hpp"

namespace kr {
    class Logger final {
    public:
        class Builder final {
        public:
            Builder() = default;
            Builder& format(std::string_view fmt) { m_Fmt = fmt; return *this; }
            Builder& addSink(std::unique_ptr<ISink> sink) { m_Sinks.push_back(std::move(sink)); return *this;}
            std::shared_ptr<Logger> build() { return std::make_shared<Logger>(m_Fmt, std::move(m_Sinks)); }
        private:
            std::vector<std::unique_ptr<ISink>> m_Sinks;
            std::string_view m_Fmt;
        };
    public:
        Logger() = delete;
        Logger(std::string_view fmt, std::vector<std::unique_ptr<ISink>>&& sinks);
        ~Logger();
        void setFormat(std::string_view fmt);
        void log(LogLevel level, std::string_view msg);
    private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}