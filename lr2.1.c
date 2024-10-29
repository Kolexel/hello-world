#include <stdio.h>

double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    double E;
    printf("Введите значение E: ");
    if (scanf("%lf", &E) != 1) {
        printf("Ошибка: введите правильное число для E.\n");
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
        double term = 1.0 / factorial(i); 
        SumCurrent += term; 

        i++;
    } while (SumCurrent - SumPrevious >= E); 

    printf("Сумма ряда: %.10f\n", SumCurrent);
    return 0;
}
