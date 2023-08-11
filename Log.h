#include <AsstCaller.h>
#include <json/value.h>
#include <json/writer.h>
#include <spdlog/spdlog.h>
#include <string>

// 模板，debug模式

namespace Logger {
enum level { info, warn, error, critical, debug };

template <typename T> void toConsole(T message, enum level l) {
  switch (l) {
  case info:
    spdlog::info(message);
    break;
  case warn:
    spdlog::warn(message);
    break;
  case error:
    spdlog::error(message);
    break;
  case critical:
    spdlog::critical(message);
    break;
  case debug:
    spdlog::debug(message);
    break;
  default:
    spdlog::warn("Unknown level");
    break;
  }
};

template <> inline void toConsole(Json::Value message, enum level l) {
  Json::StreamWriterBuilder writer;
  std::string msg = Json::writeString(writer, message);
  switch (l) {
  case info:
    spdlog::info(msg);
    break;
  case warn:
    spdlog::warn(msg);
    break;
  case error:
    spdlog::error(msg);
    break;
  case critical:
    spdlog::critical(msg);
    break;
  case debug:
    spdlog::debug(msg);
    break;
  default:
    spdlog::warn("Unknown level");
    break;
  }
};

template <typename T> void toConsole(T message) { spdlog::info(message); };

template <> inline void toConsole(Json::Value message) { // 提供日志打印json支持
  Json::StreamWriterBuilder writer;
  std::string msg = Json::writeString(writer, message);
  spdlog::info(msg);
}

template <typename T> AsstBool toMaaCore(T message, std::string level) {
  auto cStr = std::to_string(message).c_str();
  return AsstLog(level.c_str(), cStr);
};
} // namespace Logger

// maa log lavel: debug,trace,info,warn,error.