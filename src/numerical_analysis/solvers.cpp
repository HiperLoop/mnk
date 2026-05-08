#include "solvers.hpp"

// Constructor
Solver::Solver(Tiling* tiling, int win_length, bool is_maker_maker, bool is_two_player, double (*state_eval_function)(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth), std::vector<Tile*> (*move_selection_function)(Tiling* tiling, int playerId), int max_depth, Tile* (*selectBestMove)(int playerId, Tiling* tiling, int win_length, int maxDepth), double firstWinEval)
    : tiling(tiling), win_length(win_length), is_maker_maker(is_maker_maker), is_two_player(is_two_player), state_eval_function(state_eval_function), move_selection_function(move_selection_function), max_depth(max_depth), selectBestMove(selectBestMove), firstWinEval(firstWinEval) {
        std::cout << std::format("Initialized solver with win length {}, maker-maker: {}, two-player: {}, max depth: {}.\n", win_length, is_maker_maker, is_two_player, max_depth);
    }

// Destructor
Solver::~Solver() {     
    // Free any resources if necessary (currently none)
}

bool Solver::performPly(int playerId) {
    Tile* best_move = selectBestMove(playerId, tiling, win_length, max_depth);
    if (best_move != nullptr) {
        GameLogic::ApplyMove(playerId, *best_move); // Apply the move for the given player ID
    }
    else {
        // Handle the case where there are no valid moves (e.g., pass or end game)
        //std::cout << std::format("No valid moves available for player {}.\n", playerId); // Placeholder message
        return false; // No moves means this player cannot win on this ply
    }

    return GameLogic::CheckWinCondition(*tiling, playerId, win_length); // Check if this move wins the game for the player
}

bool Solver::firstWins() {
    double startEval = state_eval_function(*(tiling->Tesselation[0]), 1, tiling, win_length, 0, max_depth);
    std::cout << startEval << "\n";
    return startEval == firstWinEval; // Return whether eval at start equals firstWinEval
}