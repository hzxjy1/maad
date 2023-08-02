#include "Maad.h"

int Controller::parser(int argc, char *argv[], JSON_ITEM *ret) {
  CLI::App app{"App"};
  app.add_option("-d,--device", (*ret)["device"], "Android device address");
  app.add_option("-t,--task", (*ret)["task"], "Task to execute (e.g. 1-7,prev)");
  app.add_option("-c,--config", "Path of the configuration file");
  app.add_flag("-v,--version", (*ret)["version"], "Print version");

  CLI11_PARSE(app, argc, argv);
  return 0;
}

int Controller::analyser(Json::Value *param) {
  Json::String v = JsonHandler::returnValue(param, "version");

  if (!v.empty()) {
    Maad::version();
    return 1;
  }

  if (JsonHandler::isRealEmpty(param)) {
    Logger::toConsole(
        "Without any parameters! Run with --help for more information.",
        Logger::WARN);
    return 1;
  }
  return 0;
}