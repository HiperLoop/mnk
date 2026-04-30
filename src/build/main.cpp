#include <string>
#include "../numerical_analysis/proof_number_search.hpp"
#include "../background_logic/board.hpp"
#include "../background_logic/game_logic.hpp"
//#include "../solvers/solvers.hpp"


int main() {
    /* Tiling test1(4, 5, 2);
    test1.PrintData();
    test1.PrintTilePositions();
    Tiling test2(6, 3, 2);
    test2.PrintData();
    //test2.PrintTilePositions();
    Tiling test3(4, 4, 3);
    test3.PrintData();
    //test3.PrintTilePositions(); */

    
    // Test tiling for a cube
    Tiling cube(4, 3, 1);
    cube.PrintData();
    Solver* PF = Proof_Number_Search::InitializeSolver(&cube, 2, 100);
    std::cout << "Testing proof number search solver on a cube tiling with win length 2 and max depth 100...\n";
    std::cout << std::format("Does the first player have a winning strategy? {}\n", PF->firstWins() ? "Yes" : "No");
    return 0;
}
