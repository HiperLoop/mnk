#include "proof_number_search.hpp"

bool Proof_Number_Search::proofNumberSearch(Tiling* tiling, int playerId, int maxDepth) {};

double Proof_Number_Search::moveEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length) {
    // Check if game ending move
    if(GameLogic::CheckWinCondition(*tiling, playerId, win_length)) {
        return std::numeric_limits<double>::infinity() * (playerId == 1 ? 1 : -1); // Winning move for player 1 is positive infinity, for player 2 is negative infinity
    }
    else {
        return 0; // Neutral move (can be enhanced with heuristics)
    }
};

Tile* Proof_Number_Search::moveSelectionFunction(Tiling* tiling, int playerId) {};