#include "Maad.h"
using namespace Controller;

int cli::run(std::string &configPath) {
  cli::parser();

  if (!param["version"].empty()) {
    Maad::version();
    return 2;
  }
  if (!param["config"].empty()) {
    configPath = param["config"];
  }
  return 0;
}

int cli::parser() {
  CLI::App app{"App"};
  app.add_option("-d,--device", param["device"], "Android device address");
  app.add_option("-t,--task", param["task"], "Task to execute (e.g. 1-7,prev)");
  app.add_option("-c,--config", param["config"],
                 "Path of the configuration file");
  app.add_flag("-v,--version", param["version"], "Print version");

  CLI11_PARSE(app, argc, argv);
  return 0;
}