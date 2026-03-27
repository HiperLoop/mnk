#include "game_logic.hpp"

// Get a line of tiles in a specific direction from a starting tile
std::vector<Tile*> GameLogic::GetLine(Tiling& board, const Tile& start, double direction_angle, int max_length) {
    std::vector<Tile*> line;
    Complex currentPos = start.Coord;

    while (line.size() < max_length) {
        // Calculate the coordinates of the next tile in the specified direction
        Complex currentPos = board.CalculateNeighbor(start.location, static_cast<int>(direction_angle / board.angleStep));

        // Find the tile at the new position (if it exists)
        Tile* nextTile = nullptr;
        for (Tile* tile : board.Tesselation) {
            if (std::norm(tile->Coord - currentPos) < 1e-6) { // Check if this tile is at the new position
                nextTile = tile;
                break;
            }
        }

        if (nextTile == nullptr) {
            break; // No more tiles in this direction
        }

        line.push_back(nextTile);
    }

    return line;
}

// Check if a player has won by having a line of their tiles of length win_length
bool GameLogic::CheckWinCondition(Tiling& board, int playerId, int win_length) {
    // Check all tiles on the board
    for (const Tile* tile : board.Tesselation) {
        if (tile->value == playerId) {
            // Check in all directions for a line of length win_length
            for (int dir = 0; dir < (board.shapeDiag + board.shapeDir); ++dir) {
                std::vector<Tile*> line = GetLine(board, *tile, dir * board.angleStep, board.tilingRadius);
                int count = 1; // Start with the current tile

                // Count how many tiles in this line belong to the player
                for (Tile* nextTile : line) {
                    if (nextTile->value == playerId) {
                        count++;
                    } else {
                        break; // Stop counting if we hit a tile that doesn't belong to the player
                    }
                }

                if (count >= win_length) {
                    return true; // Player has won
                }
            }
        }
    }

    return false; // No winning line found
}

// Check if a tile is a valid move target (i.e. not already occupied)
bool GameLogic::IsValidMove(const Tile& tile) {
    // Check if the tile is already occupied
    return tile.value == 0;
}

// Set the value of a tile to playerId to indicate that the player has claimed that tile
bool GameLogic::ApplyMove(int playerId, Tile& tile) {
    // Apply the move by setting the tile's value to the player's ID
    if (!IsValidMove(tile)) {
        return false; // Move is invalid, tile is already occupied
    }
    tile.value = playerId;
    return true;
}

// Set the value of all tiles in a tesselation to be unoccupied (0)
void GameLogic::ResetBoard(Tiling& board) {
    for (Tile* tile : board.Tesselation) {
        tile->value = 0; // Reset all tiles to unoccupied
    }
}