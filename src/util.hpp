#ifndef UTIL
#define UTIL

#include <exception>
#include <string>

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

#endif