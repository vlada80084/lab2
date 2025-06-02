#pragma once
#include "Matrix.h"
#include "oper.h"
#include <chrono>
#include <iostream>
#define eps 1e-10

template <typename T>
class SLAU : public Matrix<T> {
public:
    using Matrix<T>::Matrix;

    Vector<T> gauss_jordan(const Vector<T>& right_side) {
        int lines = this->get_num_of_lines();
        int columns = (*this)[0].get_vector_size();

        if (right_side.get_vector_size() != lines)
            throw std::invalid_argument("Right side size does not match number of lines");

        Vector<Vector<T>> augmented_matrix(lines);

        for (int i = 0; i < lines; i++) {
            augmented_matrix[i] = Vector<T>(columns + 1);
            for (int j = 0; j < columns; j++) {
                augmented_matrix[i][j] = (*this)[i][j];
            }
            augmented_matrix[i][columns] = right_side[i];
        }

        auto start_time = std::chrono::high_resolution_clock::now();

        for (int col = 0, row = 0; col < columns && row < lines; col++) {
            int max_row = row;
            T max_val = std::abs(augmented_matrix[row][col]);
            for (int i = row + 1; i < lines; i++) {
                operation_count++;
                if (std::abs(augmented_matrix[i][col]) > max_val) {
                    max_val = std::abs(augmented_matrix[i][col]);
                    max_row = i;
                }
            }

            if (max_val < eps) continue;

            if (max_row != row) {
                std::swap(augmented_matrix[row], augmented_matrix[max_row]);
                operation_count += columns + 1;
            }

            T pivot = augmented_matrix[row][col];
            for (int j = col; j <= columns; j++) {
                augmented_matrix[row][j] /= pivot;
                operation_count++;
            }

            for (int i = 0; i < lines; i++) {
                if (i != row && std::abs(augmented_matrix[i][col]) > eps) {
                    T factor = augmented_matrix[i][col];
                    for (int j = col; j <= columns; j++) {
                        augmented_matrix[i][j] -= factor * augmented_matrix[row][j];
                        operation_count += 2;
                    }
                }
            }
            ++row;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Estimated arithmetic operations: " << operations_count << "\n";

        Vector<T> solution(lines);
        for (int i = 0; i < lines; i++) {
            solution[i] = augmented_matrix[i][columns];
        }

        return solution;
    }

    void print_solution(const Vector<T>& solution) const {
        for (int i = 0; i < solution.get_vector_size(); i++) {
            std::cout << 'x' << (i + 1) << " = " << solution[i] << ";\n";
        }
    }

    bool check_solution(const Vector<T>& solution, const Vector<T>& right_side) const {
        int n = this->get_num_of_lines();
        int m = solution.get_vector_size();

        for (int i = 0; i < n; ++i) {
            T sum = 0;
            for (int j = 0; j < m; ++j) {
                sum += (*this)[i][j] * solution[j];
            }
            if (std::abs(sum - right_side[i]) > eps) {
                std::cout << "Check failed at row " << i + 1 << ": got " << sum << ", expected " << right_side[i] << "\n";
                return false;
            }
        }
        std::cout << "Solution verified successfully.\n";
        return true;
    }
};