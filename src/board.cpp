#include "board.hpp"

// Tile constructor
Tile::Tile(double angle, double dist, int layer) : Coord(std::polar(dist, angle)), layer(layer) {}

// Tiling constructor
Tiling::Tiling(int polygon_degree, int vertex_degree, int tiling_radius) : 
m(polygon_degree), n(vertex_degree), tilingRadius(tiling_radius), cos_pi_m(std::cos(std::numbers::pi / polygon_degree)), cos_pi_n(std::cos(std::numbers::pi / vertex_degree)), sin_pi_m(std::sin(std::numbers::pi / polygon_degree)) {
    // Check for invalid tilings
    EvenPolygonCheck();
    // Initialise Tiling parameters
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
        throw CustomException("Odd-sided polygon tiling is invalid.");
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
    angleStep = (2 * std::numbers::pi) / (shapeDir + shapeDiag);
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
    std::cout << std::format("angleStep = {}\n", angleStep * 180 / std::numbers::pi); // Convert radians to degrees for better readability

    std::cout << "Tesselation parameters:\n";
    std::cout << std::format("number of tiles = {}\n", Tesselation.size());
}

// Returns a rotation matrix pointing to the desired angle
Algebra::Matrix<double> createRotation(double theta) {
    Algebra::Matrix<double> res(3); // Start with 1s on the diagonal
    double c = std::cos(theta);
    double s = std::sin(theta);

    res(0, 0) = c;  res(0, 1) = -s; res(0, 2) = 0;
    res(1, 0) = s;  res(1, 1) = c;  res(1, 2) = 0;
    res(2, 0) = 0;  res(2, 1) = 0;  res(2, 2) = 1;
    
    return res;
}

// Returns translation matrix moving by a distance d
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
    Algebra::Matrix<double> rot = createRotation(edge_index * (2.0 * std::numbers::pi / m));
    
    // 2. Translate by the side_length (step into the next polygon)
    Algebra::Matrix<double> trans = createTranslation(side_length);
    
    // 3. New Position = Current * Rotation * Translation
    return current * (rot * trans);
}

// Function to retunr coordinate of neighbour
Complex Tiling::CalculateNeighbor(Complex Coord, int i) {
    // TODO
    return 0;
}

// Returns bool value of whether the desired tile already exists or not
bool Tiling::IsTileDuplicate(Complex newCenter, const std::vector<Complex>& existing) {
    for (const auto& old : existing) {
        if (std::norm(newCenter - old) < 1e-6) return true;
    }
    return false;
}

// Generates the array of Tiles that make up the tilings
void Tiling::GenerateTesselation() {
    std::vector<Tile*> allTiles;
    std::set<Complex, decltype(&Algebra::ComplexLessThan)> visited;
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