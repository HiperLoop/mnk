#include "proof_number_search.hpp"

Solver* Proof_Number_Search::InitializeSolver(Tiling* tiling, int win_length, int maxDepth) {
    std::cout << std::format("Initializing proof number search solver with win length {} and max depth {}...\n", win_length, maxDepth);
    return new Solver(tiling, win_length, false, true, moveEvalFunction, moveSelectionFunction, maxDepth);
}

double Proof_Number_Search::moveEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth) {
    // Check if game ending move
    if(GameLogic::CheckWinCondition(*tiling, 1, win_length)) {
        return 0; // Winning move for player 1 means 0 proof number for the node
    }
    if(GameLogic::CheckWinCondition(*tiling, 2, win_length)) {
        return std::numeric_limits<double>::infinity(); // Winning move for player 2 is proof number infinity from the perspective of player 1
    }
    if (depth >= maxDepth) {
        int remaining_moves = (Proof_Number_Search::moveSelectionFunction(tiling, playerId)).size();
        return remaining_moves == 0 ? std::numeric_limits<double>::infinity() : remaining_moves; // Heuristic: use the number of possible moves as a simple heuristic for the proof number (can be enhanced with more sophisticated heuristics)
    }
    if (playerId == 1) {
        int min_eval = std::numeric_limits<double>::infinity();
        for (Tile* move : Proof_Number_Search::moveSelectionFunction(tiling, playerId)) {
            // Simulate the move
            move->value = playerId; // Placeholder: mark the tile with the player's ID (can be enhanced with a proper game state management)
            double eval = Proof_Number_Search::moveEvalFunction(*move, 2, tiling, win_length, depth + 1, maxDepth);
            min_eval = eval < min_eval ? eval : min_eval; // Minimize the proof number for player 1
            move->value = 0; // Undo the move
        }
        return min_eval;
    }
    int eval_sum = 0;
        for (Tile* move : Proof_Number_Search::moveSelectionFunction(tiling, playerId)) {
            // Simulate the move
            move->value = playerId; // Placeholder: mark the tile with the player's ID (can be enhanced with a proper game state management)
            double eval = Proof_Number_Search::moveEvalFunction(*move, 2, tiling, win_length, depth + 1, maxDepth);
            eval_sum += eval; // Sum the proof numbers for player 2
            move->value = 0; // Undo the move
        }
        return eval_sum; // Return the sum of proof numbers for player 2
};

std::vector<Tile*> Proof_Number_Search::moveSelectionFunction(Tiling* tiling, int playerId) {
    std::vector<Tile*> possible_moves;
    for (Tile* tile : tiling->Tesselation) {
        if (GameLogic::IsValidMove(*tile)) {
            possible_moves.push_back(tile);
        }
    }
    return possible_moves; // Placeholder: simply return all valid moves, can be enhanced with heuristics
};