#include "Maad.h"
#include <AsstCaller.h>
#include <string>

void Maad::version() {
  std::cout << "Version: " << PROJECT_VERSION_MAJOR << "."
            << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH
            << std::endl;
}

int Maad::init(int argc, char *argv[], JSON_ITEM &config) {
#ifdef DEBUG
  spdlog::set_level(spdlog::level::debug); // 设置调试级别
#endif
  STRING_MAP param;
  JSON_ITEM configJson;
  std::string configPath;

  (new Controller::cli(argc, argv, param))->run(configPath); // 获取命令行参数

  Maad::importConfig(configJson, configPath); // 导入外部配置

  for (const auto &pair : param) { // 将命令行参数和外部导入配置参数合并
    if (pair.second.empty()) {
      continue;
    }
    configJson["option"][pair.first] = pair.second;
  }
  config = configJson;
  return 0;
}

int Maad::importConfig(JSON_ITEM &config, std::string configPath) {
  std::string Path1 = configPath;
#ifdef __linux__
  std::string Path2 = "../config.json";
  std::string Path3 = std::string(getenv("HOME")) + "/.config/maad/config.json";
#endif
  if (!JsonHandler::deserializeFile(config, Path1)) {
    return 0;
  } else if (!JsonHandler::deserializeFile(config, Path2)) {
    return 0;
  } else if (!JsonHandler::deserializeFile(config, Path3)) {
    return 0;
  } else {
    Logger::toConsole("Can not find configuration file! Create it?[y/n]",
                      Logger::error);
    return 1;
  }
  return 0;
}

int loadLib() { // 加载核心库
  return 0;
}