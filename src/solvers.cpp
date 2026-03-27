#include "solvers.hpp"

Solver::Solver(Tiling* tiling, int win_length, bool is_maker_maker, bool is_two_player, double (*move_eval_function)(Tile&), std::vector<Tile*> (*move_selection_function)(Tiling* tiling), int max_depth) 
    : tiling(tiling), win_length(win_length), is_maker_maker(is_maker_maker), is_two_player(is_two_player), move_eval_function(move_eval_function), move_selection_function(move_selection_function), max_depth(max_depth) {}

Solver::~Solver() {     
    // Free any resources if necessary (currently none)
}

Tile * Solver::selectBestMove(Tiling * tiling) {
    std::vector<Tile*> possible_moves = move_selection_function(tiling);
    Tile* best_move = nullptr;
    double best_score = -std::numeric_limits<double>::infinity();

    for (Tile* move : possible_moves) {
        double score = move_eval_function(*move);
        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}

bool Solver::performPly(int playerId) {
    Tile* best_move = selectBestMove(tiling);
    if (best_move != nullptr) {
        GameLogic::ApplyMove(playerId, *best_move); // Apply the move for the given player ID
    }
    else {
        // Handle the case where there are no valid moves (e.g., pass or end game)
        std::cout << std::format("No valid moves available for player {}.\n", playerId); // Placeholder message
    }

    return GameLogic::CheckWinCondition(*tiling, playerId, win_length); // Check if this move wins the game for the player
}

bool Solver::firstWins() {
    for(int depth = 0; depth < max_depth; ++depth) {
        for(int playerId = 1; playerId <= (is_two_player ? 2 : 1); ++playerId) {
            if (performPly(playerId)) {
                return playerId == 1; // Return true if the first player wins, false if the second player wins
            }
        }
    }
    return false; // If no winner after max_depth, return false
}