//
// Created by filan on 28.06.2025.
//

#include "kr/ConsoleSink.hpp"

using namespace kr;

class ConsoleSink::Impl {
public:
    Impl(std::ostream& ostream, LogLevel LogLevel) : m_Ostream(ostream), m_LogLevel(LogLevel) { }
    ~Impl();

    void write(const char *message) {
        m_Ostream << message;
    }

    void flush() {
        m_Ostream << '\n';
        m_Ostream.flush();
    }

    bool checkIfCanWrite(LogLevel level) {
        return m_LogLevel >= level;
    }

    LogLevel getLogLevel() {
        return m_LogLevel;
    }

    void setLogLevel(LogLevel p_LogLevel) {
        m_LogLevel = p_LogLevel;
    }

private:
    std::ostream& m_Ostream;
    LogLevel m_LogLevel;
};

ConsoleSink::ConsoleSink(std::ostream &ostream, LogLevel logLevel) {
    m_PImpl = std::make_unique<Impl>(ostream, logLevel);
}

void ConsoleSink::write(const char *message) {
    m_PImpl->write(message);
}

void ConsoleSink::flush() {
    m_PImpl->flush();
}

bool ConsoleSink::checkIfCanWrite(LogLevel level) {
    return m_PImpl->checkIfCanWrite(level);
}

LogLevel ConsoleSink::getLogLevel() {
    return m_PImpl->getLogLevel();
}

void ConsoleSink::setLogLevel(LogLevel p_LogLevel) {
    m_PImpl->setLogLevel(p_LogLevel);
}