#include "board.hpp"

bool ComplexLessThan(const Complex& a, const Complex& b) {
    if (std::arg(a) != std::arg(b)) return std::arg(a) < std::arg(b);
    return std::abs(a) < std::abs(b);
}

// Tile constructor
Tile::Tile(double angle, double dist, int layer) : Coord(std::polar(dist, angle)), layer(layer) {}

// Tiling constructor
Tiling::Tiling(int polygon_degree, int vertex_degree, int tiling_radius) : 
m(polygon_degree), n(vertex_degree), tilingRadius(tiling_radius), cos_pi_m(std::cos(M_PI / polygon_degree)), cos_pi_n(std::cos(M_PI / vertex_degree)), sin_pi_m(std::sin(M_PI / polygon_degree)) {
    EvenPolygonCheck();
    InitDirectionality();
    InitCoordinateSystem();
    InitDistance();
}

// Tiling destructor
Tiling::~Tiling() {
    for (std::vector<Tile*>::iterator it = Tesselation.begin(); it != Tesselation.end(); ++it) {
        delete *it;
    }
    Tesselation.clear();
}

// Throw an exception if tiling is of odd-sided polygons
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
    angleStep = (2 * M_PI) / (shapeDir + shapeDiag);
    distStep = 2; // Make distStep 2x the raius of the circumscribed circle
}

void Tiling::InitDistance() {
    cosh_d = (cos_pi_n + cos_pi_m * cos_pi_m) / (sin_pi_m * sin_pi_m);
    side_length = acosh(cosh_d);
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

    std::cout << "Tesselation parameters:\n";
    std::cout << std::format("number of tiles = {}\n", Tesselation.size());
}

Algebra::Matrix<double> createRotation(double theta) {
    Algebra::Matrix<double> res(3); // Start with 1s on the diagonal
    double c = std::cos(theta);
    double s = std::sin(theta);

    res(0, 0) = c;  res(0, 1) = -s; res(0, 2) = 0;
    res(1, 0) = s;  res(1, 1) = c;  res(1, 2) = 0;
    res(2, 0) = 0;  res(2, 1) = 0;  res(2, 2) = 1;
    
    return res;
}

Algebra::Matrix<double> createTranslation(double d) {
    Algebra::Matrix<double> res(3);
    double ch = std::cosh(d);
    double sh = std::sinh(d);

    // This translates along the X-axis by distance d
    res(0, 0) = ch;  res(0, 1) = 0; res(0, 2) = sh;
    res(1, 0) = 0;  res(1, 1) = 1;  res(1, 2) = 0;
    res(2, 0) = sh;  res(2, 1) = 0;  res(2, 2) = ch;

    return res;
}

// Get the matrix that moves you to the i-th neighbor
Algebra::Matrix<double> Tiling::GetNeighborTransform(const Algebra::Matrix<double>& current, int edge_index) {
    // 1. Rotate to face the correct edge
    Algebra::Matrix<double> rot = createRotation(edge_index * (2.0 * M_PI / m));
    
    // 2. Translate by the side_length (step into the next polygon)
    Algebra::Matrix<double> trans = createTranslation(side_length);
    
    // 3. New Position = Current * Rotation * Translation
    return current * (rot * trans);
}

Complex Tiling::CalculateNeighbor(Complex Coord, int i) {
    return 0;
}

bool Tiling::IsTileDuplicate(Complex newCenter, const std::vector<Complex>& existing) {
    for (const auto& old : existing) {
        if (std::norm(newCenter - old) < 1e-6) return true;
    }
    return false;
}

// Generates the array of Tiles that make up the tilings
void Tiling::GenerateTesselation() {
    std::vector<Tile*> allTiles;
    std::set<Complex, decltype(&ComplexLessThan)> visited;
    std::queue<Tile*> frontier;

    // Start with the center tile at (0,0)
    Tile* root = new Tile(0, 0, 0);
    frontier.push(root);
    visited.insert(root->Coord);
    allTiles.push_back(root);

    while (!frontier.empty()) {
        Tile* current = frontier.front();
        frontier.pop();

        if (current->layer >= tilingRadius) continue;

        // Try to add 'n' neighbors for this regular n-gon
        for (int i = 0; i < n; ++i) {
            // Logic to calculate neighbor coordinates based on 'i'
            // This varies by tiling type (Square vs Hex vs Hyperbolic)
            Complex neighborPos = CalculateNeighbor(current->Coord, i);

            if (visited.find(neighborPos) == visited.end()) {
                visited.insert(neighborPos);
                Tile* next = new Tile(std::arg(neighborPos), std::abs(neighborPos), current->layer + 1);
                allTiles.push_back(next);
                frontier.push(next);
            }
        }
    }
    Tesselation = allTiles;
}