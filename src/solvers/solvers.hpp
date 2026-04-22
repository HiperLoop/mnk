#ifndef SOLVERS
#define SOLVERS

#include "board.hpp"
#include "game_logic.hpp"

class Solver {
public:
    Tiling* tiling; // Pointer to the tiling being solved
    int win_length = 0; // Length of line required to win (k in m,n,k)
    bool is_maker_maker = false; // Whether the solver is for a maker-maker game (as opposed to maker-breaker)
    bool is_two_player = true; // Whether the solver is for a two player game (as opposed to a one player puzzle)
    double (*move_eval_function)(Tile& target) = nullptr; // Function pointer for the move evaluation function that evalueates the score of the given target tile
    std::vector<Tile*> (*move_selection_function)(Tiling* tiling) = nullptr; // Function pointer for the move selection function that selects the candidate moves to be evaluated at each step
    int max_depth = 0; // Maximum search depth for the solver (relevant for minimax based solvers)

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