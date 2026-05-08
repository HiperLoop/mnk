#include "proof_number_search.hpp"

// Evaluation corresponding to P1 win
double firstWinEval = 0;

Solver* Proof_Number_Search::InitializeSolver(Tiling* tiling, int win_length, int maxDepth) {
    std::cout << std::format("Initializing proof number search solver with win length {} and max depth {}...\n", win_length, maxDepth);
    return new Solver(tiling, win_length, false, true, stateEvalFunction, moveSelectionFunction, maxDepth, selectBestMove, firstWinEval);
}

double Proof_Number_Search::stateEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth) {
    // Check if game ending move
    if(GameLogic::CheckWinCondition(*tiling, 1, win_length)) {
        return 0; // Winning move for player 1 means 0 proof number for the node
    }
    if(GameLogic::CheckWinCondition(*tiling, 2, win_length)) {
        return 10000; // Winning move for player 2 is proof number infinity from the perspective of player 1
    }
    std::vector<Tile*> tiles = Proof_Number_Search::moveSelectionFunction(tiling, playerId);
    int remaining_moves = tiles.size();
    if(remaining_moves == 0) {
        return 10000;
    }
    if (depth >= maxDepth) {
        return remaining_moves == 0 ? 10000 : remaining_moves; // Heuristic: use the number of possible moves as a simple heuristic for the proof number (can be enhanced with more sophisticated heuristics)
    }
    if (playerId == 1) {
        int min_eval = 10000;
        int counter = 0;
        for (Tile* move : tiles) {
            // Simulate the move
            move->value = playerId; // Placeholder: mark the tile with the player's ID (can be enhanced with a proper game state management)
            double eval = Proof_Number_Search::stateEvalFunction(*move, 2, tiling, win_length, depth + 1, maxDepth);
            if(eval == 0) {return 0;}
            if(depth == 0) {
                counter++;
                std::cout << std::format("move {} out of {}\n", counter, tiles.size());
            }
            min_eval = eval < min_eval ? eval : min_eval; // Minimize the proof number for player 1
            move->value = 0; // Undo the move
        }
        return min_eval;
    }
    double eval_sum = 0;
    for (Tile* move : tiles) {
        // Simulate the move
        move->value = playerId; // Placeholder: mark the tile with the player's ID (can be enhanced with a proper game state management)
        double eval = Proof_Number_Search::stateEvalFunction(*move, 1, tiling, win_length, depth + 1, maxDepth);
        if(eval >= 10000) {return 10000;}
        eval_sum = std::max(std::max(eval_sum, eval), eval + eval_sum); // Sum the proof numbers for player 2
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

Tile* Proof_Number_Search::selectBestMove(int playerId, Tiling* tiling, int win_length, int maxDepth) {
    std::vector<Tile*> possible_moves = Proof_Number_Search::moveSelectionFunction(tiling, playerId);
    Tile* best_move = nullptr;
    double best_score = 10000;

    for (Tile* move : possible_moves) {
        double score = Proof_Number_Search::stateEvalFunction(*move, playerId, tiling, win_length, 0, maxDepth);
        if (score < best_score) {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}