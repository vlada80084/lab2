#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <locale.h>
#include "Exception.h"

using namespace std;


template <typename T>
class Vector {
private:
    T* cords;
    int size;

public:
    Vector() : cords(nullptr), size(0) {}


    explicit Vector(int _size) : size(_size) {
        if (size > 0) {
            cords = new T[size]();  
        }
        else {
            cords = nullptr;        
        }
    }
    Vector(initializer_list<T> list) : size(static_cast<int>(list.size())) {
        if (size > 0) {
            cords = new T[size]();
        }
        else {
            cords = nullptr;
        }
        int i = 0;
        for (const T& val : list) { cords[i++] = val; }
    }

    Vector(int _size, const T& value) : size(_size) {
        if (size > 0) {
            cords = new T[size]();
        }
        else {
            cords = nullptr;
        }
        for (int i = 0; i < size; ++i) { cords[i] = value; }
    }

    Vector(const Vector& other) : size(other.size) {
        if (size > 0) {
            cords = new T[size]();
        }
        else {
            cords = nullptr;
        }
        for (int i = 0; i < size; ++i) { cords[i] = other.cords[i]; }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] cords;
            size = other.size;
            cords = (size > 0) ? new T[size] : nullptr;
            for (int i = 0; i < size; ++i) cords[i] = other.cords[i];
        }
        return *this;
    }

    Vector(Vector&& other) noexcept : cords(other.cords), size(other.size) {
        other.cords = nullptr;
        other.size = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] cords;
            cords = other.cords;
            size = other.size;
            other.cords = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Vector() { delete[] cords; }

    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw MyException("Vector index out of range");
        return cords[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw MyException("Vector index out of range");
        return cords[index];
    }

    int get_vector_size() const { return size; }

    void print_vector() const {
        cout << "[";
        for (int i = 0; i < size; ++i) {
            cout << cords[i] << (i != size - 1 ? ", " : "");
        }
        cout << "]";
    }
};
