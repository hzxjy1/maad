#include "Maad.h"
#include <AsstCaller.h>

void Maad::version() {
  std::cout << "Version: " << PROJECT_VERSION_MAJOR << "."
            << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH
            << std::endl;
}

AsstBool Maad::init(JSON_ITEM *config) {
// 导入配置文件
#ifdef __linux__
  std::string Path1 = "../config.json";
  std::string Path2 = std::string(getenv("HOME")) + "/.config/maad/config.json";
#endif
  AsstBool i = JsonHandler::deserializeFile(config, Path1);
  AsstBool j = 1;
  if (i) {
    j = JsonHandler::deserializeFile(config, Path2);
    if (j) {
      Logger::toConsole("Can not find configuration file! Create it?[y/n]",
                        Logger::ERROR);
      return 1;
    }
  }
  std::cout << (*config)["switch"] << std::endl;
  // 检查动态链接库
  return 0;
}