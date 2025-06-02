#include <iostream>
#include "SLAU.h"
#include "Exception.h"

using namespace std;

template <typename T>
void run_solver() {
    int n, m;
    cout << "Enter number of equations: ";
    cin >> n;
    cout << "Enter number of variables: ";
    cin >> m;

    SLAU<T> matrix;
    matrix.resize(n);

    cout << "Enter matrix coefficients:\n";
    for (int i = 0; i < n; i++) {
        matrix[i] = Vector<T>(m);
        for (int j = 0; j < m; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrix[i][j];
        }
    }

    Vector<T> right(n);
    cout << "Enter right-hand side vector:\n";
    for (int i = 0; i < n; i++) {
        cout << "b[" << i + 1 << "]: ";
        cin >> right[i];
    }

    try {
        matrix.gauss_jordan(right);
        auto solution = matrix.gauss_jordan(right);
        matrix.check_solution(solution, right);
    }
    catch (MyException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    string type;
    cout << "Enter type (int, float, double, char): ";
    cin >> type;

    if (type == "int") run_solver<int>();
    else if (type == "float") run_solver<float>();
    else if (type == "double") run_solver<double>();
    else if (type == "char") run_solver<char>();
    else cout << "Unsupported type\n";

    return 0;
}
