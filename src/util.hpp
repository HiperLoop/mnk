#ifndef UTIL
#define UTIL

#include <exception>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

class CustomException : public std::exception {
private:
    std::string message;

public:
    // Constructor accepts a string
    explicit CustomException(const std::string& msg);

    // Overriding the virtual what() method from std::exception
    // The 'noexcept' ensures the exception handler itself doesn't crash
    virtual const char* what() const noexcept override;
};

namespace Geometry {
    // Checks if the space needs to be hyperbolic
    bool IsHyperbolic(int m, int n);
    // Returns internal angle of the regular m-gons
    double PolygonInternalAngle(int n);
    // Returns angle between playable directions
    double CoordinateAngleStep(int m, int n);
};

namespace Algebra {
    template <typename T>
    class Matrix {
    public:
        int n; // Size of the NxN matrix
        std::vector<T> data;

        // Constructor: Initialize NxN matrix with zeros
        Matrix(int size) : n(size), data(size * size, 0) {}

        // Access element at (row, col) - Read/Write
        T& operator()(int r, int c) {
            return data[r * n + c];
        }

        // Access element at (row, col) - Read Only
        const T& operator()(int r, int c) const {
            return data[r * n + c];
        }

        int size() const { return n; }

        // Static method to create an NxN Identity Matrix
        static Matrix<T> Identity(int size) {
            Matrix<T> identity(size);
            for (int i = 0; i < size; ++i) {
                identity(i, i) = static_cast<T>(1);
            }
            return identity;
        }

        // --- ALGEBRA OPERATORS ---

        // Addition: C = A + B
        Matrix<T> operator+(const Matrix<T>& other) const {
            if (n != other.n) throw std::invalid_argument("Matrix dimensions must match.");
            Matrix<T> result(n);
            for (int i = 0; i < n * n; ++i) {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        // Subtraction: C = A - B
        Matrix<T> operator-(const Matrix<T>& other) const {
            if (n != other.n) throw std::invalid_argument("Matrix dimensions must match.");
            Matrix<T> result(n);
            for (int i = 0; i < n * n; ++i) {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

        // Multiplication: C = A * B
        // Optimized using i-k-j loop order for cache locality
        Matrix<T> operator*(const Matrix<T>& other) const {
            if (n != other.n) throw std::invalid_argument("Matrix dimensions must match.");
            Matrix<T> result(n);
            for (int i = 0; i < n; ++i) {
                for (int k = 0; k < n; ++k) {
                    T temp = (*this)(i, k); // Cache the row element
                    for (int j = 0; j < n; ++j) {
                        result(i, j) += temp * other(k, j);
                    }
                }
            }
            return result;
        }

        // Helper to print matrix
        void print() const {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << (*this)(i, j) << " ";
                }
                std::cout << "\n";
            }
        }
    };
}

#endif