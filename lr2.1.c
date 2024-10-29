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
    scanf("%lf", &E);

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