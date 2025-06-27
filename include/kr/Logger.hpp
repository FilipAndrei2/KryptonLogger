//
// Created by filan on 25.06.2025.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "kr/Sink.hpp"

namespace kr {

    class Logger final {
    public:
        Logger(std::string_view fmt, std::initializer_list<Sink&> sinks);
        ~Logger();

    public:
        void setFormat(std::string_view fmt);

        void log(LogLevel level, std::string_view msg);

    private:
        class Impl;
        Impl* m_Impl;
    };
}

#endif //LOGGER_HPP
