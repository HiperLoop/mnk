#ifndef SOLVERS
#define SOLVERS

#include "board.hpp"
#include "game_logic.hpp"

class Solver {
public:
    Tiling* tiling;
    int win_length = 0;
    bool is_maker_maker = false;
    bool is_two_player = true;
    double (*move_eval_function)(Tile& target) = nullptr;
    std::vector<Tile*> (*move_selection_function)(Tiling* tiling) = nullptr;
    int max_depth = 0;

    // Constructor
    Solver(Tiling* tiling, int win_length, bool is_maker_maker, bool is_two_player, double (*move_eval_function)(Tile&), std::vector<Tile*> (*move_selection_function)(Tiling* tiling), int max_depth) {}

    // Destructor
    ~Solver() {}

private:
    Tile* selectBestMove(Tiling * tiling) {}

    bool performPly(int playerId) {}

    bool firstWins() {}
};

#endif