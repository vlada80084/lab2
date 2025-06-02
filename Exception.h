#pragma once
#include <string>

class MyException {
    std::string message;
public:
    MyException(const std::string& msg) : message(msg) {}
    const std::string& what() const { return message; }
};