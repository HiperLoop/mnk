#include <vector>
#include <string>
#include "board.hpp"

using namespace std;

int main() {
    Tiling test1(4, 5);
    test1.PrintData();
    Tiling test2(6, 3);
    test2.PrintData();
    Tiling test3(4, 4);
    test3.PrintData();
    return 0;
}
