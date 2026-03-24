#include "util.hpp"

CustomException::CustomException(const std::string& msg) : message(msg) {}

const char* CustomException::what() const noexcept {
    return message.c_str();
}

// Check if the tiling needs to be in the hyperbolic plane base on polygon egree (m) and vertex degree (n)
bool Geometry::IsHyperbolic(int m, int n) {
    // If the sum of internal angles of n polygons joind at each vertex is gretaer than 2pi, the tiling is hyperbolic
    return n * (m - 2) * M_PI / m > 2 * M_PI;
}

// Calculate the internal angle of Hyperbolic regular polygons
double Geometry::PolygonInternalAngle(int n) {
    return 2 * M_PI / n;
}

// Calculate the angle step between polygons surrounding a central polygon
double Geometry::CoordinateAngleStep(int m, int n) {
    // Given a regular tiling all polygons surrounding each polygon are evenly spaced in terms of angles
    // There are m * (n - 2) polygons surrounding each one
    // The result is dividing the whole circle (2pi) by the number of adjecent polygons
    return 2 * M_PI / (m * (n - 2));
}

