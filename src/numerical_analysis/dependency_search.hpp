#ifndef DEPENDENCY_SEARCH
#define DEPENDENCY_SEARCH

#include "board.hpp"

class Threat {
public:
    std::vector<Tile*> tiles; // Tiles that form the threat
    int playerId; // Player for whom the threat is relevant
    int threatLevel; // A measure of how urgent it is to address this threat

    Threat(std::vector<Tile*> tiles, int playerId, int threatLevel) : tiles(tiles), playerId(playerId), threatLevel(threatLevel) {}
};

namespace DependencySearch {
    // Function to identify threats in the current tiling state for a given player
    std::vector<Threat> identifyThreats(Tiling* tiling, int playerId);

    // Move evalution function for the dependency based search solver
    double move_eval_function(Tile& target);

    // Move selection function for the dependency based search solver
    std::vector<Tile*> move_selection_function(Tiling* tiling);
}

#endif