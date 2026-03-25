#ifndef GAME_LOGIC
#define GAME_LOGIC

#include "board.hpp"

namespace GameLogic {
    // Function to get a line of tiles in a specific direction from a starting tile
    std::vector<Tile*> GetLine(Tiling& board, const Tile& start, double direction_angle, int max_length);

    // Function to determine if a player has won
    bool CheckWinCondition(Tiling& board, int playerId, int win_length);

    // Function to determine if a move is valid
    bool IsValidMove(const Tile& tile);

    // Function to apply a player's move to the board
    bool ApplyMove(int playerId, Tile& tile);
};

#endif