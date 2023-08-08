#include "Maad.h"
#include <AsstCaller.h>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  try {
    JSON_ITEM config;
    Maad::init(argc, argv, config);

    // MAA::MaaItem *maaitem = new MAA::MaaItem(param);
    // maaitem->load();
    // maaitem->start();

    // delete maaitem;
    return 0;
  } catch (std::exception e) {
    std::cout << "Exception caught in main(): " << e.what() << std::endl;
    return 1;
  }
}