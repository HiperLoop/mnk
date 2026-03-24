#ifndef UTIL
#define UTIL

#include <exception>
#include <string>

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
    bool IsHyperbolic(int m, int n);
    double PolygonInternalAngle(int n);
    double CoordinateAngleStep(int m, int n);

};

#endif