#ifndef BOARD
#define BOARD

#include "util.hpp"
#include <format>
#include <set>
#include <queue>
#include <map>

class Tile {
public:
    // Coordinates
    Complex Coord;
    int layer = 0;

    // Tile value
    int value = 0;

    // Constructor
    Tile(double angle, double dist, int layer);
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

    // Transform constants
    double cos_pi_m = 0;
    double cos_pi_n = 0;
    double sin_pi_m = 0;
    
    // Hyperbolic distance constants
    double cosh_d = 0;
    double side_length = 0; 

    // Radius of tiling
    int tilingRadius = 0;

    // Vector of tiles
    std::vector<Tile*> Tesselation;

    // Constructor
    Tiling(int polygon_degree, int vertex_degree, int tiling_radius);

    // Destructor
    ~Tiling();

    void PrintData();

    // Returns transform matrix to get to the desired neighbour
    Algebra::Matrix<double> GetNeighborTransform(const Algebra::Matrix<double>& current, int edge_index);


    Complex CalculateNeighbor(Complex Coord, int i);

    // Checks whether a tile is being generated duplictely
    bool IsTileDuplicate(Complex newCenter, const std::vector<Complex>& existing);

private:
    // Validate the tiling
    void EvenPolygonCheck();
    // Calculate the useful tiling constants
    void InitDirectionality();
    // Calculate the coordinate system constants
    void InitCoordinateSystem();
    // Calculate useful constants the notion of distance
    void InitDistance();
    // Generate the tiles that make up the tiling
    void GenerateTesselation();
};

#endif