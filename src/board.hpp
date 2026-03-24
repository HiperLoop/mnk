#ifndef BOARD
#define BOARD

#include "util.hpp"
#include <iostream>
#include <format>

class Tiling {
public:
    // Schläfli symbol constants
    int m = 0;
    int n = 0;

    // Useful tiling constants
    int vertexDiag = 0;
    int shapeDir = 0;
    int shapeDiag = 0;

    // Coordinate system constants
    double distStep = 0;
    double angleStep = 0;

    // Constructor
    Tiling(int polygon_degree, int vertex_degree);

    void PrintData();

private:
    // Validate the tiling
    void EvenPolygonCheck();
    // Calculate the useful tiling constants
    void InitDirectionality();
    // Calculate the coordinate system constants
    void InitCoordinateSystem();
};

#endif