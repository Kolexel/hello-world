#include <stdio.h>
#include <math.h>

double Ln(double x) {
    double result = 0.0;
    x = (x - 1) / (x + 1);
    double term = x;
    int n = 1;

    while (fabs(term)) {
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
    scanf("%lf", &a);
    printf("Введите b: ");
    scanf("%lf", &b);
    printf("Введите значение E: ");
    scanf("%lf", &E);

    if(a>=b) {
        printf("Ошибка, a должно быть меньше b");
        return 1;
    }

    if(E<=0) {
        printf("Погрешность должна быть меньше 0");
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
















