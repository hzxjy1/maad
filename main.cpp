#include "Maad.h"

int main(int argc, char *argv[]) {
  try {
    JSON_ITEM config;
    Maad::init(argc, argv, config);

    STRING_MAP st;
    st["Fight"] = R"({{"stage": "{}"}})";
    st["Recruit"] =
        R"({"refresh":true,"select":[4],"confirm":[3,4],"times":4})";
    st["Infrast"] =
        R"({"facility": ["Mfg", "Trade", "Power", "Control", "Reception",
      "Office", "Dorm"],"drones": "Money"})";
    st["Mall"] =
        R"({"shopping":true,"buy_first":["许可"],"black_list":["家具","碳"]})";

    MAA::MaaItem *maaitem = new MAA::MaaItem(config, st);
    if (maaitem->load()) {
      return 1;
    }
    maaitem->start();

    delete maaitem;
    return 0;
  } catch (std::exception e) {
    std::cout << "Exception caught in main(): " << e.what() << std::endl;
    return 1;
  }
}