#include <AsstCaller.h>
#include <CLI/CLI.hpp>
#include <json/json.h>
#include <string>

#ifndef VERSION_H
#define VERSION_H

#define PROJECT_VERSION_MAJOR 0
#define PROJECT_VERSION_MINOR 1
#define PROJECT_VERSION_PATCH 2

#endif

#define DEBUG

#define JSON_ITEM Json::Value

namespace MAA {
class MaaItem {
public:
  MaaItem(JSON_ITEM *param);
  ~MaaItem();
  AsstId gerId();
  AsstBool load();
  AsstBool AppendTask(AsstHandle handle, const char *type, const char *params);
  AsstBool start();
  AsstBool start(void (*func)(), int second); // 连带启动模拟器
  AsstBool quit();
  AsstBool quit(void (*func)()); // 连带关闭模拟器

private:
  class MaaItemImpl;
  MaaItemImpl *pimpl;
};
} // namespace MAA

namespace Maad {
void version();
AsstBool init(JSON_ITEM *config);
} // namespace Maad

namespace Controller {
int parser(int argc, char *argv[], JSON_ITEM *ret);
int analyser(JSON_ITEM *param); // 判断各种输入情况
} //  namespace Controller

namespace JsonHandler {
JSON_ITEM deserialize(std::string);
AsstBool deserializeFile(JSON_ITEM *json,
                         std::string path); // 将json文件转换为json对象
std::string serialize(JSON_ITEM);
AsstBool serializeFile(JSON_ITEM, std::string path); // 将json对象转换为json文件
AsstBool addKV(JSON_ITEM *json, std::string key, std::string value);
std::string returnValue(JSON_ITEM *json, std::string key);
bool isRealEmpty(JSON_ITEM *json); // 判断json数据内所有值均为null的情况
};                                 // namespace JsonHandler

namespace Logger {
enum level { INFO, WARN, ERROR, CRITICAL };

void toConsole(std::string message, enum level l);
void toConsole(std::string message);
bool toMaaCore();
} // namespace Logger