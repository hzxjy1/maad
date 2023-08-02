#include "Maad.h"
#include <AsstCaller.h>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  try {
    JSON_ITEM *param = new JSON_ITEM;
    std::map<std::string, std::string> params;
    JSON_ITEM *config = new JSON_ITEM;

    Maad::init(config);

    Controller::parser(argc, argv, param);
    if (Controller::analyser(param)) {
      return 0;
    }

    // MAA::MaaItem *maaitem = new MAA::MaaItem(param);
    // maaitem->load();
    // maaitem->start();

    // delete maaitem;
    delete param;
    delete config;
    return 0;
  } catch (std::exception e) {
    std::cout << "Exception caught in main(): " << e.what() << std::endl;
    return 1;
  }
}