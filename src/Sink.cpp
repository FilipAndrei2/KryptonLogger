//
// Created by filan on 25.06.2025.
//
#include "kr/Sink.hpp"
#include <fstream>

class kr::Sink::SinkImpl {
public:
    SinkImpl() = delete;
    SinkImpl(std::ofstream& out, LogLevel level)
        : m_OutStream(out), m_LogLevel(level)
    { }

    virtual ~SinkImpl() {
        if (m_OutStream.is_open()) {
            m_OutStream.close();
        }
    }

public:
    void write(const char* p_Message) {
        m_OutStream << p_Message;
    }

    void flush() {
        m_OutStream << '\n';
        m_OutStream.flush();
    }

    bool checkIfCanWrite(LogLevel level) {
        return m_LogLevel >= level;
    }

public:

    LogLevel getLogLevel() {
        return m_LogLevel;
    }

    void setLogLevel(LogLevel p_LogLevel) {
        m_LogLevel = p_LogLevel;
    }

private: // members
    std::ofstream& m_OutStream;
    LogLevel m_LogLevel;
};


kr::Sink::Sink(std::ofstream &out, LogLevel level)
    : m_Pimpl(std::make_unique<SinkImpl>(out, level))
{ }

kr::LogLevel kr::Sink::getLogLevel() { return m_Pimpl->getLogLevel(); }
void kr::Sink::setLogLevel(LogLevel p_LogLevel) { m_Pimpl->setLogLevel(p_LogLevel); }

void kr::Sink::write(const char *p_Message) {
    m_Pimpl->write(p_Message);
}

void kr::Sink::flush() {
    m_Pimpl->flush();
}

bool kr::Sink::checkIfCanWrite(LogLevel level) {
    return m_Pimpl->checkIfCanWrite(level);
}

kr::Sink::~Sink() {
    m_Pimpl->flush();
}