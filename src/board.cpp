#include "board.hpp"
#include <iostream>

Tiling::Tiling(int initial_m, int initial_n) : m(initial_m), n(initial_n) {
    // This will throw an exception if validation fails
    EvenPolygonCheck(m, n);
    
    // If we reach here, validation passed. 
    // You can add your diagonal calculations here.
}

void Tiling::EvenPolygonCheck(int m, int n) {
    if (m % 2 != 0) {
        throw CustomException("Uneven-sided polygon tiling is forbidden.");
    }
}