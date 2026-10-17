#include "gonpiecetable/_.hpp"
#include <iostream>
int main() {
    std::string ahaha = "ahaha";
    gonpiecetable n(ahaha);
    n += "awawa";
    std::string bbbn = "iogsan";
    n.insert(2, bbbn);
    std::string gbb = "iozon";
    n.insert(0, gbb);
    for (const auto& e : n) {
        std::cout << e << std::endl;
    }

    return 0;
}