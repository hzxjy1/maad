#include "Maad.h"
#include <AsstCaller.h>
#include <spdlog/spdlog.h>

enum level { INFO, WARN, ERROR, CRITICAL };

void Logger::toConsole(std::string message) { spdlog::info(message); }

void Logger::toConsole(std::string message, enum level l) {
  switch (l) {
  case INFO:
    spdlog::info(message);
    break;
  case WARN:
    spdlog::warn(message);
    break;
  case ERROR:
    spdlog::error(message);
    break;
  case CRITICAL:
    spdlog::critical(message);
    break;
  default:
    spdlog::warn("Unknown level");
    break;
  }
}

bool Logger::toMaaCore() {
  // AsstLog("const char *level", "const char *message");
  return false;
};

/*  maa log lavel:
static const level debug;
static const level trace;
static const level info;
static const level warn;
static const level error;
*/