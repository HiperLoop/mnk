#include "board.hpp"

Tiling::Tiling(int polygon_degree, int vertex_degree) : m(polygon_degree), n(vertex_degree) {
    EvenPolygonCheck();
    InitDirectionality();
    InitCoordinateSystem();
}

// This will throw an exception if tiling is of odd-sided polygons
void Tiling::EvenPolygonCheck() {
    if (m % 2 != 0) {
        throw CustomException("Uneven-sided polygon tiling is forbidden.");
    }
}

// Initialise useful tiling constants
void Tiling::InitDirectionality() {
    // The number of lines going through the sides and diagonals of each polygon is the same and equal to m/2
    shapeDir = m/2;
    // If there is an even number of polygons joined at each vertex, it makes sense to talk about diagonals
    if (n % 2 == 0) {
        vertexDiag = n/2;
        shapeDiag = shapeDir;
    }
}

// Initialise coordinate system constants
void Tiling::InitCoordinateSystem() {
    angleStep = Geometry::CoordinateAngleStep(m, n);

}

// Print all the information about the tiling
void Tiling::PrintData() {
    std::cout << std::format("Schlafli symbol: {{{}, {}}}\n", m, n);

    std::cout << "Useful tiling constants:\n";
    std::cout << std::format("vertexDiag = {}\n", vertexDiag);
    std::cout << std::format("shapeDir = {}\n", shapeDir);
    std::cout << std::format("shapeDiag = {}\n", shapeDiag);

    std::cout << "Coordinate system constants:\n";
    std::cout << std::format("distStep = {}\n", distStep);
    std::cout << std::format("angleStep = {}\n", angleStep * 180 / M_PI); // Convert radians to degrees for better readability
}