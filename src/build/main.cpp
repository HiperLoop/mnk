#include <string>
#include "../background_logic/board.hpp"

using namespace std;

int main() {
    Tiling test1(4, 5, 2);
    test1.PrintData();
    test1.PrintTilePositions();
    Tiling test2(6, 3, 2);
    test2.PrintData();
    //test2.PrintTilePositions();
    Tiling test3(4, 4, 3);
    test3.PrintData();
    //test3.PrintTilePositions();
    return 0;
}
