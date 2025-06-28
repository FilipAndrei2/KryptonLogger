//
// Created by filan on 28.06.2025.
//


#include "kr/FileSink.hpp"

#include <fstream>

using namespace kr;

class FileSink::Impl {
public:
  Impl(const char* filePath, LogLevel LogLevel)
    : m_FileStream(filePath), m_LogLevel(LogLevel)
  {
     if (!m_FileStream.is_open()) {
       throw std::runtime_error("Could not open file " + std::string(filePath));
     }
  }

  Impl(std::string& filePath, LogLevel LogLevel)
    : m_FileStream(filePath), m_LogLevel(LogLevel)
  {
    if (!m_FileStream.is_open()) {
      throw std::runtime_error("Could not open file " + std::string(filePath));
    }
  }

  Impl(std::string_view filePath, LogLevel LogLevel)
    : m_FileStream(filePath.data()), m_LogLevel(LogLevel)
  {
    if (!m_FileStream.is_open()) {
      throw std::runtime_error("Could not open file " + std::string(filePath));
    }
  }

  void write(const char *message) {
    m_FileStream << message;
  }

  void flush() {
    m_FileStream << '\n';
    m_FileStream.flush();
  }

  ~Impl() {
    if (m_FileStream.is_open()) {
      m_FileStream.close();
    }
  }

  bool checkIfCanWrite(LogLevel level) {
    return m_LogLevel >= level;
  }

  LogLevel getLogLevel() { return m_LogLevel; }

  void setLogLevel(LogLevel p_LogLevel) { m_LogLevel = p_LogLevel; }

private:
  std::ofstream m_FileStream;
  LogLevel m_LogLevel;
};

FileSink::FileSink(const char *filePath, LogLevel LogLevel) {
  m_PImpl = std::make_unique<Impl>(filePath, LogLevel);
}

FileSink::FileSink(std::string &filePath, LogLevel LogLevel) {
  m_PImpl = std::make_unique<Impl>(filePath, LogLevel);
}

FileSink::FileSink(std::string_view filePath, LogLevel LogLevel) {
  m_PImpl = std::make_unique<Impl>(filePath, LogLevel);
}

bool FileSink::checkIfCanWrite(LogLevel level) {
  return m_PImpl->checkIfCanWrite(level);
}

void FileSink::flush() {
  m_PImpl->flush();
}

LogLevel FileSink::getLogLevel() {
  return m_PImpl->getLogLevel();
}

void FileSink::setLogLevel(LogLevel p_LogLevel) {
  m_PImpl->setLogLevel(p_LogLevel);
}

void FileSink::write(const char *message) {
  m_PImpl->write(message);
}