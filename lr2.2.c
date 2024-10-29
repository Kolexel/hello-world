#include <stdio.h>
#include <math.h>

double Ln(double x) {
    double result = 0.0;
    x = (x - 1) / (x + 1);
    double term = x;
    int n = 1;

    while (fabs(term) > 1e-10) {
        result += term / n;
        n++;
        term *= x * x;
    }

    return 2 * result;
}

double LeftRectangle(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += Ln(a + i * h);
    }

    return sum * h;
}

int main() {
    double a, b, E;
    
    printf("Введите a: ");
    if (scanf("%lf", &a) != 1) {
        printf("Ошибка: введите правильное число для a.\n");
        return 1;
    }
    
    printf("Введите b: ");
    if (scanf("%lf", &b) != 1) {
        printf("Ошибка: введите правильное число для b.\n");
        return 1;
    }
    
    printf("Введите значение E: ");
    if (scanf("%lf", &E) != 1) {
        printf("Ошибка: введите правильное число для E.\n");
        return 1;
    }
    
    if (a >= b) {
        printf("Ошибка, a должно быть меньше b\n");
        return 1;
    }

    if (E <= 0) {
        printf("Погрешность должна быть больше 0\n");
        return 1;
    }

    double SumCurrent = 0.0;
    double SumPrevious = 0.0;
    int i = 1;

    do {
        SumPrevious = SumCurrent;
        SumCurrent = LeftRectangle(a, b, i);

        i++;
    } while (fabs(SumCurrent - SumPrevious) >= E);

    printf("Сумма ряда: %.10f\n", SumCurrent);
    return 0;
}
















