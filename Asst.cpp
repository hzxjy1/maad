#include "Maad.h"
#include <AsstCaller.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

void maaCallback(AsstMsgId msg, const char *details_json, void *custom_arg) {
  // #ifdef DEBUG
  //   std::cout << "MSG:" << msg << ",JSON:" << details_json
  //             << ",ARGS:" << custom_arg << std::endl;
  // #endif
}

class MAA::MaaItem::MaaItemImpl {
public:
  MaaItemImpl(JSON_ITEM &config, STRING_MAP st);
  ~MaaItemImpl();
  AsstId getId();
  AsstBool load();
  AsstBool AppendTask(std::string type, std::string params);
  AsstBool start();
  AsstBool start(void (*func)(), int second);
  AsstBool quit();
  AsstBool quit(void (*func)());

private:
  AsstId id = -1;
  AsstBool init();
  AsstHandle *asst;
  JSON_ITEM config;
  STRING_MAP st;
};

MAA::MaaItem::MaaItemImpl::MaaItemImpl(JSON_ITEM &config, STRING_MAP st) {
  // 设置id
  int seed;
  seed = time(0);
  srand(seed);
  id = rand() % 10000 + 1;
  Logger::toConsole("maaid:" + fmt::to_string(id), Logger::debug);

  this->config = config;
  this->st = st;
  asst = new AsstHandle();
  this->init();
}

MAA::MaaItem::MaaItemImpl::~MaaItemImpl() { delete asst; }

AsstId MAA::MaaItem::MaaItemImpl::getId() { return id; }

AsstBool MAA::MaaItem::MaaItemImpl::init() {
  const AsstBool status = 1;
  Logger::toConsole("MaaCore Init");

  std::string Resource =
      config["option"]["Resource"].asString(); // 资源文件路径
  std::string UserDir =
      config["option"]["UserDir"].asString(); // 日志文件输出路径
  Logger::toConsole("resource:" + Resource, Logger::debug);
  Logger::toConsole("userdir:" + UserDir, Logger::debug);

  if (!AsstSetUserDir(UserDir.c_str())) {
    return status;
  }
  if (!AsstLoadResource(Resource.c_str())) {
    Logger::toConsole("Can not load resource files!", Logger::error);
    return status;
  }
  *asst = AsstCreateEx(maaCallback,
                       reinterpret_cast<void *>(MAA::MaaItem::MaaItemImpl::id));
  if (asst == nullptr || id == -1) {
    Logger::toConsole("Create Asst instance failed", Logger::critical);
    return status;
  }
  return 0;
}

AsstBool MAA::MaaItem::MaaItemImpl::load() {
  const AsstBool status = 1;
  if (!AsstSetInstanceOption(*asst, 2, "maatouch")) { // linux需要设置为maatouch
    Logger::toConsole("Set maatouch failed", Logger::warn);
    return status;
  }
  std::string deviceAddr = config["option"]["device"].asString();
  Logger::toConsole("Try to connect Android device " + deviceAddr,
                    Logger::info);
  AsstConnect(*asst, "adb", deviceAddr.c_str(), "General");
  if (!AsstConnected(*asst)) {
    Logger::toConsole("Connect failed", Logger::critical);
    return status;
  }

  JSON_ITEM j = config["switch"];
  Logger::toConsole(j, Logger::debug);
  for (const Json::Value &element : j) { // 添加AppendTask
    std::string intent = element.asString();
    if (intent == "Fight") {
      // 将关卡名注入到AppendTask的json文件中
      st[intent] = fmt::format(st[intent], config["option"]["task"].asString());
    }
    if (AppendTask(intent, st[intent]) == 0) {
      Logger::toConsole("Append a task " + intent + " failed", Logger::error);
    }
    // Logger::toConsole(intent, Logger::debug);
    // Logger::toConsole(st[intent], Logger::debug);
    // Logger::toConsole(i, Logger::debug);
  }
  return 0;
}

AsstBool MAA::MaaItem::MaaItemImpl::AppendTask(std::string type,
                                               std::string params) {
  return AsstAppendTask(*this->asst, type.c_str(), params.c_str());
}

AsstBool MAA::MaaItem::MaaItemImpl::start() {
  Logger::toConsole("MaaCore Start");
  AsstStart(*asst);
  while (AsstRunning(*asst)) {
    std::this_thread::yield();
  }
  return 0;
}

AsstBool MAA::MaaItem::MaaItemImpl::start(void (*func)(),
                                          int second) { // 以后再说
  start();
  return 0;
}

AsstBool MAA::MaaItem::MaaItemImpl::quit() { return 0; }

AsstBool MAA::MaaItem::MaaItemImpl::quit(void (*func)()) { return 0; }

/*——————原函数实现——————*/

MAA::MaaItem::MaaItem(JSON_ITEM &config, STRING_MAP st) {
  pimpl = new MaaItemImpl(config, st);
}

MAA::MaaItem::~MaaItem() { delete pimpl; }

AsstId MAA::MaaItem::MaaItem::gerId() { return pimpl->getId(); }

AsstBool MAA::MaaItem::load() { return pimpl->load(); }

AsstBool MAA::MaaItem::AppendTask(std::string type, std::string params) {
  return pimpl->AppendTask(type, params);
}

AsstBool MAA::MaaItem::start() { return pimpl->start(); }

AsstBool MAA::MaaItem::start(void (*func)(), int second) {
  return pimpl->start(func, second);
}

AsstBool MAA::MaaItem::quit() { return pimpl->quit(); }

AsstBool MAA::MaaItem::quit(void (*func)()) { return pimpl->quit(func); }