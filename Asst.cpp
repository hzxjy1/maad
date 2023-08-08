#include "Maad.h"
#include <AsstCaller.h>
#include <fmt/core.h>
#include <thread>

void maaCallback(AsstMsgId msg, const char *details_json, void *custom_arg) {
#ifdef DEBUG
  // printf("callback:%d,%s\n", msg, details_json);
  std::cout << "MSG:" << msg << ",JSON:" << details_json
            << ",ARGS:" << custom_arg << std::endl;
#endif
}

class MAA::MaaItem::MaaItemImpl {
public:
  MaaItemImpl(JSON_ITEM *param);
  ~MaaItemImpl();
  AsstId getId();
  AsstBool load();
  AsstBool AppendTask(AsstHandle handle, const char *type, const char *params);
  AsstBool start();
  AsstBool start(void (*func)(), int second);
  AsstBool quit();
  AsstBool quit(void (*func)());

private:
  AsstId id = -1;
  AsstBool init();
  AsstHandle *asst;
  JSON_ITEM *param;

  std::string fightTemplate = R"({{"stage": "{}"}})";
  std::string recruitTemplate = R"({"select":[4],"confirm":[3,4],"times":4})";
  std::string infrastTemplate =
      R"({"facility": ["Mfg", "Trade", "Power", "Control", "Reception", "Office", "Dorm"],"drones": "Money"})";
  std::string mailTemplate =
      R"({"shopping":true,"buy_first":["许可"],"black_list":["家具","碳"]})";
};

MAA::MaaItem::MaaItemImpl::MaaItemImpl(JSON_ITEM *param) {
  int seed;
  seed = time(0);
  srand(seed);
  id = rand() % 10000 + 1;
#ifdef DEBUG
  std::cout << "MAAID:" << id << std::endl;
#endif
  asst = new AsstHandle();
  this->param = param;
  this->init();
}

MAA::MaaItem::MaaItemImpl::~MaaItemImpl() { delete asst; }

AsstId MAA::MaaItem::MaaItemImpl::getId() { return id; }

AsstBool MAA::MaaItem::MaaItemImpl::init() {
  try {
    AsstBool status = 1;
    Logger::toConsole("MaaCore Init");
    std::string Path =
        "/usr/share/maa-assistant-arknights-bin"; // 0.1.1请在此填写资源路径
    AsstSetUserDir(".");
    status = AsstLoadResource(Path.c_str());
    if (!status) {
      return status;
    }
    *asst = AsstCreateEx(
        maaCallback, reinterpret_cast<void *>(MAA::MaaItem::MaaItemImpl::id));
    if (asst == nullptr) {
      Logger::toConsole("Create Asst instance failed", Logger::CRITICAL);
      return status;
    }
    return 0;
  } catch (std::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
    return 1;
  }
}

AsstBool MAA::MaaItem::MaaItemImpl::load() {
  if (!AsstSetInstanceOption(*asst, 2, "maatouch")) {
    Logger::toConsole("Set maatouch failed", Logger::WARN);
    return 1;
  }
  AsstConnect(*asst, "adb", JsonHandler::returnValue(param, "device").c_str(),
              "General");
  if (!AsstConnected(*asst)) {
    Logger::toConsole("connect failed", Logger::CRITICAL);
    return 1;
  }
  AsstAppendTask(*asst, "StartUp", NULL);
  
  // Fight
  std::string task = JsonHandler::returnValue(param, "task");
  if (task == "prev") {
    task = "";
  }
  std::string Template = fmt::format(fightTemplate, task);
#ifdef DEBUG
  Logger::toConsole(Template, Logger::WARN);
#endif
  AsstAppendTask(*asst, "Fight", Template.c_str());
  
  // Recruit
  AsstAppendTask(*asst, "Recruit", recruitTemplate.c_str());
  // Infrast
  AsstAppendTask(*asst, "Infrast", infrastTemplate.c_str());
  // Mail
  AsstAppendTask(*asst, "Mall", mailTemplate.c_str());
  // Award
  AsstAppendTask(*asst, "Award", "");
  return 0;
}

AsstBool MAA::MaaItem::MaaItemImpl::AppendTask(AsstHandle handle,
                                               const char *type,
                                               const char *params) {
  return AppendTask(handle, type, params);
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

MAA::MaaItem::MaaItem(JSON_ITEM *param) { pimpl = new MaaItemImpl(param); }

MAA::MaaItem::~MaaItem() { delete pimpl; }

AsstId MAA::MaaItem::MaaItem::gerId() { return pimpl->getId(); }

AsstBool MAA::MaaItem::load() { return pimpl->load(); }

AsstBool MAA::MaaItem::AppendTask(AsstHandle handle, const char *type,
                                  const char *params) {
  return pimpl->AppendTask(handle, type, params);
}

AsstBool MAA::MaaItem::start() { return pimpl->start(); }

AsstBool MAA::MaaItem::start(void (*func)(), int second) {
  return pimpl->start(func, second);
}

AsstBool MAA::MaaItem::quit() { return pimpl->quit(); }

AsstBool MAA::MaaItem::quit(void (*func)()) { return pimpl->quit(func); }