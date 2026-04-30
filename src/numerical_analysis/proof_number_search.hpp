#ifndef PNS
#define PNS

#include "solvers.hpp"

namespace Proof_Number_Search {
    // Eval function for proof number search
    double moveEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth);

    // Move selection function for proof number search
    std::vector<Tile*> moveSelectionFunction(Tiling* tiling, int playerId);

    // Proof number search solver class instance
    Solver* InitializeSolver(Tiling* tiling, int win_length, int maxDepth);
}

#endif