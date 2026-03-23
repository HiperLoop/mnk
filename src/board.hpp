#ifndef BOARD
#define BOARD

#include "util.hpp"

class Tiling {
public:
    // Schläfli symbol constants
    int m = 0;
    int n = 0;

    // Calculated useful tiling properties
    int vertexDiag = 0;
    int shapeDiag = 0;
    int shapeThrough = 0;

    // Constructor
    Tiling(int initial_m, int initial_n);

private:
    // Helper to validate the tiling
    void EvenPolygonCheck(int m, int n);
};

#endif