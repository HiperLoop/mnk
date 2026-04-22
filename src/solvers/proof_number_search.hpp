#include "solvers.hpp"
#include "../background_logic/game_logic.hpp"

namespace Proof_Number_Search {
    // Function to perform the proof number search algorithm
    bool proofNumberSearch(Tiling* tiling, int playerId, int maxDepth);

    // Eval function for proof number search
    double moveEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth);

    // Move selection function for proof number search
    std::vector<Tile*> moveSelectionFunction(Tiling* tiling, int playerId);
}