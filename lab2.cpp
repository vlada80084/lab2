#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <locale.h>
#include <stdlib.h>

typedef unsigned int uint;


void sin_(float* data, uint n, float x) {
    x = fmodf(x, 2.0f * (float)M_PI);
    data[0] = x;
    for (int i = 1; i < n; i++) {
        data[i] = ((-1) * data[i - 1] * x * x) / ((2 * i + 1) * (2 * i));
    }
}

void cos_(float* data, uint n, float x) {
    x = fmodf(x, 2.0 * (float)M_PI);
    data[0] = 1.0;
    for (int i = 1; i < n; i++) {
        data[i] = ((-1) * data[i - 1] * x * x) / ((2 * i) * (2 * i - 1));
    }
}

void exp_(float* data, uint n, float x) {
    data[0] = 1.0;
    for (int i = 1; i < n; i++) {
        data[i] = data[i - 1] * x / i;
    }
}

void ln_(float* data, uint n, float x) {
    data[0] = x;
    for (int i = 1; i < n; i++) {
        data[i] = ((-1) * data[i - 1] * x * i) / (i + 1);
    }
}

float direct_summation(float* data, uint n) {
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum = sum + data[i];
    }
    return sum;
}

float reverse_summation(float* data, uint n) {
    float sum = 0.0;
    for (int i = n - 1; i >= 0; i--) {
        sum = sum + data[i];
    }
    return sum;
}

float pairwise_summation(float* data, uint n) {
    if (n == 1) { return data[0]; }
    float sum = 0.0;
    int new_n = (n + 1) / 2;
    float* new_data = (float*)malloc(sizeof(float) * (new_n));
    if ((n % 2) == 0) {
        for (int i = 0; i < new_n; i++) {
            new_data[i] = data[i * 2] + data[i * 2 + 1];
        }
    }
    else {
        for (int i = 0; i < (new_n - 1); i++) {
            new_data[i] = data[2 * i] + data[2 * i + 1];
        }
        new_data[new_n - 1] = data[n - 1];
    }
    for (int i = 0; i < new_n; i++) {
        sum = sum + new_data[i];
    }
    free(new_data);
    return sum;
}

float common(float x, uint n, void(*functions)(float* mas, uint n, float x), float(*summations)(float* mas, uint n)) {
    float* data = (float*)malloc(sizeof(float) * n);
    float result;
    functions(data, n, x);
    result = summations(data, n);
    free(data);
    return result;

}

float choice(int flag_f, int flag_s, float x, uint n) {
    if (flag_f == 1) {
        if (flag_s == 1) { return common(x, n, sin_, direct_summation); }
        if (flag_s == 2) { return common(x, n, sin_, reverse_summation); }
        if (flag_s == 3) { return common(x, n, sin_, pairwise_summation); }
    }
    if (flag_f == 2) {
        if (flag_s == 1) { return common(x, n, cos_, direct_summation); }
        if (flag_s == 2) { return common(x, n, cos_, reverse_summation); }
        if (flag_s == 3) { return common(x, n, cos_, pairwise_summation); }
    }
    if (flag_f == 3) {
        if (flag_s == 1) { return common(x, n, exp_, direct_summation); }
        if (flag_s == 2) { return common(x, n, exp_, reverse_summation); }
        if (flag_s == 3) { return common(x, n, exp_, pairwise_summation); }
    }
    if ((flag_f == 4) && (x > -1) && (x <= 1)) {
        if (flag_s == 1) { return common(x, n, ln_, direct_summation); }
        if (flag_s == 2) { return common(x, n, ln_, reverse_summation); }
        if (flag_s == 3) { return common(x, n, ln_, pairwise_summation); }
    }
    else { printf("Недопустимое значение х (х <= -1)\n"); }
    return 0.0;
}

double error_rate(float result, int flag_f, float x) {
    float error;
    if (flag_f == 1) {
        return fabs(sin(x) - (double)result);
    }
    if (flag_f == 2) {
        return fabs(cos(x) - (double)result);
    }
    if (flag_f == 3) {
        return fabs(exp(x) - (double)result);
    }
    if (flag_f == 4) {
        return fabs(log(x + 1) - (double)result);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    float error;
    float result;
    double result_1 = 0.0, result_2 = 0.0, result_3 = 0.0;
    int flag_f;
    int flag_s;
    float x;
    uint n;
    printf("Выберите функцию:\n1 - sin(x)\n2 - cos(x)\n3 - exp(x)\n4 - ln(1+x)\n");
    printf("Введите цифру, соответствующую нужной функции: ");
    scanf_s("%d", &flag_f);
    if ((flag_f <= 0) || (flag_f > 4)) { printf("Недопустимое значение."); }
    else {
        printf("Выберите вид суммирования:\n1 - Прямое суммирование\n2 - Обратное суммирование\n3 - Попарное суммирование\n");
        printf("Введите цифру, соответствующую нужному суммированию: ");
        scanf_s("%d", &flag_s);
        if ((flag_s <= 0) || (flag_s > 3)) { printf("Недопустимое значение."); }
        else {
            printf("Введите значение х для функции: ");
            scanf_s("%f", &x);
            printf("Введите количество элементов в ряде: ");
            scanf_s("%d", &n);
            if (n <= 0) { printf("Недопустимое значение."); }
            else {
                result = choice(flag_f, flag_s, x, n);
                printf("Результат суммирования: %f\n", result);
                error = error_rate(result, flag_f, x);
                printf("Погрешность составила: %f\n", error);

            }

        }
    }
