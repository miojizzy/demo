#include "enum_bitwise.h"

#include <iostream>

enum class ChangeLevel {
    None = 0,
    Local = 1 << 0,
    Server = 1 << 1,
    All = Local | Server
};

using namespace enum_ops;


int main (){
    ChangeLevel stat = ChangeLevel::None;

    stat |= ChangeLevel::All;

    if ((stat & ChangeLevel::Local) != 0 ) {
        std::cout << "has local" << std::endl;
    }

    if ((stat & ChangeLevel::Local) != 0) {
        std::cout << "has local" << std::endl;
    }


    return 0;
}