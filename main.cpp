#include "Maad.h"
#include <iostream>
#include <iterator>
#include <json/config.h>
#include <ostream>

int main(int argc, char *argv[]) {
  try {
    JSON_ITEM *param = new JSON_ITEM;
    Controller::parser(argc, argv, param);
    if (Controller::analyser(param)) {
      return 0;
    }

    MAA::MaaItem *maaitem = new MAA::MaaItem(param);
    maaitem->load();
    maaitem->start();

    delete maaitem;
    delete param;
    return 0;
  } catch (std::exception e) {
    std::cout << "Exception caught in main(): " << e.what() << std::endl;
    return 1;
  }
}