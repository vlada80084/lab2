#pragma once
#include "Vector.h"
#include "Exception.h"

template <typename T>
class Matrix : public Vector<Vector<T>>{
private:
    Vector<Vector<T>> matrix;
    int size;

public:
    Matrix() : size(0) {}

    Matrix(std::initializer_list<Vector<T>> vecs) : size(vecs.size()) {
        matrix = Vector<Vector<T>>(size);
        int i = 0;
        for (const auto& vec : vecs) {
            matrix[i++] = vec;
        }
    }

    Vector<T>& operator[](int index) {
        if (index < 0 || index >= size)
            throw MyException("Matrix index out of range");
        return matrix[index];
    }

    const Vector<T>& operator[](int index) const {
        if (index < 0 || index >= size)
            throw MyException("Matrix index out of range");
        return matrix[index];
    }

    int get_num_of_lines() const { return size; }

    void resize(int _size) {
        size = _size;
        matrix = Vector<Vector<T>>(size);
    }

    void print_matrix() const {
        for (int i = 0; i < size; i++) {
            matrix[i].print_vector();
            cout << endl;
        }
    }
};