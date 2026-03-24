#ifndef BOARD
#define BOARD

#include "util.hpp"
#include <iostream>
#include <format>
#include <map>

class Tile {
public:
    // Coordinates
    double coordAngle;
    double coordDist;

    // Tile value
    int value = 0;

    // Map of neighbouring tiles, ordered from the positive x axis counterclockwise
    std::map<int, Tile> neighbours;

    // Constructor
    Tile(double angle, double dist);
};

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

    // Radius of tiling
    int tilingRadius = 1;

    // Array of tiles
    Tile* Tesselation[];

    // Constructor
    Tiling(int polygon_degree, int vertex_degree, int tiling_radius);

    void PrintData();

private:
    // Validate the tiling
    void EvenPolygonCheck();
    // Calculate the useful tiling constants
    void InitDirectionality();
    // Calculate the coordinate system constants
    void InitCoordinateSystem();
    // Generate the tiles that make up the tiling
    void GenerateTesselation();
};

#endif