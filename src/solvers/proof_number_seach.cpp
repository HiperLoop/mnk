#include "proof_number_search.hpp"

bool Proof_Number_Search::proofNumberSearch(Tiling* tiling, int playerId, int maxDepth) {};

double Proof_Number_Search::moveEvalFunction(Tile& target, int playerId, Tiling* tiling, int win_length, int depth, int maxDepth) {
    // Check if game ending move
    if(GameLogic::CheckWinCondition(*tiling, playerId, win_length)) {
        return 0; // Winning move for player 1 means 0 proof number for the node
    }
    if(GameLogic::CheckWinCondition(*tiling, playerId, win_length)) {
        return std::numeric_limits<double>::infinity() * (playerId == 1 ? 1 : -1); // Winning move for player 2 is proof number infinity from the perspective of player 1
    }
    if (depth >= maxDepth) {
        return size(Proof_Number_Search::moveSelectionFunction(tiling, playerId)); // Heuristic: use the number of possible moves as a simple heuristic for the proof number (can be enhanced with more sophisticated heuristics)
    }
    return ; // Neutral move (can be enhanced with heuristics)
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