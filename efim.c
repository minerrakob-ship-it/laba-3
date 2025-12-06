#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Функция вычисления значения кривой (передача по значению)
double f(double x) {
    return (2 * pow(x, 3)) + (-2 * pow(x, 2)) + (0 * x) + (10);
}

// Функция вычисления первообразной (для формулы Ньютона-Лейбница)
double F(double x) {
    return (0.5 * pow(x, 4)) + (-2.0/3.0 * pow(x, 3)) + (10 * x);
}

// Функция вычисления интеграла методом трапеций
double trapezoidalMethod(double a, double b, int n) {
    double h = fabs(b - a) / (double)n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        // Учитываем только положительную часть по оси OY
        double fx = f(x);
        if (fx > 0) {
            sum += fx;
        }
    }
    
    return sum * h;
}

// Функция вычисления интеграла по формуле Ньютона-Лейбница
double NewtonLeibnizMethod(double a, double b) {
    return F(b) - F(a);
}

// Функция для вычисления абсолютной погрешности
double calculateAbsoluteError(double exact_value, double approx_value) {
    return fabs(exact_value - approx_value);
}

// Функция для вычисления относительной погрешности в процентах
double calculateRelativeErrorPercent(double exact_value, double approx_value) {
    if (fabs(exact_value) < 1e-12) {
        return 0.0; // Избегаем деления на ноль
    }
    return (calculateAbsoluteError(exact_value, approx_value) / fabs(exact_value)) * 100.0;
}

// Процедура отображения меню
void displayMenu() {
    system("@cls||clear");
    printf("=== CALCULATE AREA UNDER THE CURVE ===\n");
    printf("Curve: f(x) = 2x^3 - 2x^2 + 10\n");
    printf("1. Enter lower integration limit\n");
    printf("2. Enter upper integration limit\n");
    printf("3. Enter number of partitions\n");
    printf("4. Calculate integral values\n");
    printf("5. Exit\n");
    printf("Enter menu item: ");
}

// Функция ввода числа с проверкой (передача по значению - сообщение)
double inputDouble(const char* message) {
    double value;
    printf("%s", message);
    scanf("%lf", &value);
    return value;
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    while (getchar() != '\n');
}
int main() {
    int choice, n = 1000;
    double a = 0, b = 0;
    int isAEntered = 0, isBEntered = 0;
    
    setlocale(0, "Russian");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                system("@cls||clear");
                printf("Enter lower integration limit: ");
                scanf("%lf", &a);
                isAEntered = 1;
                
                // Ограничения для положительной части по OY
                if (a < 0) {
                    printf("Note: for positive part along OY axis, lower limit set to 0\n");
                    a = 0;
                }
                clearInputBuffer();
                break;
            }
            
            case 2: {
                system("@cls||clear");
                printf("Enter upper integration limit: ");
                scanf("%lf", &b);
                isBEntered = 1;
                
                if (b <= a) {
                    printf("Error: upper limit must be greater than lower limit\n");
                    printf("Automatically set to: a + 1\n");
                    b = a + 1;
                }
                clearInputBuffer();
                break;
            }
            
            case 3: {
                system("@cls||clear");
                printf("Current number of partitions: %d\n", n);
                printf("Enter new number of partitions: ");
                scanf("%d", &n);
                
                if (n < 1) {
                    printf("Error: number of partitions must be positive\n");
                    printf("Set to default value: 1000\n");
                    n = 1000;
                }
                clearInputBuffer();
                break;
            }
            
            case 4: {
                system("@cls||clear");
                if (isAEntered && isBEntered) {
                    // Вычисление интеграла методом трапеций
                    double trapezoidal_result = trapezoidalMethod(a, b, n);
                    
                    // Вычисление интеграла по формуле Ньютона-Лейбница
                    double newton_leibniz_result = NewtonLeibnizMethod(a, b);
                    
                    // Вычисление абсолютной погрешности
                    double abs_error = calculateAbsoluteError(newton_leibniz_result, trapezoidal_result);
                    
                    // Вычисление относительной погрешности в процентах
                    double rel_error_percent = calculateRelativeErrorPercent(newton_leibniz_result, trapezoidal_result);
                    
                    printf("CALCULATION RESULTS:\n");
                    printf("====================\n");
                    printf("Function: f(x) = 2x^3 - 2x^2 + 10\n");
                    printf("Integration limits: [%.2f, %.2f]\n", a, b);
                    printf("Number of partitions: %d\n\n", n);
                    
                    printf("Values:\n");
                    printf("1. Trapezoidal method result: %.10f\n", trapezoidal_result);
                    printf("2. Newton-Leibniz method result: %.10f\n\n", newton_leibniz_result);
                    
                    printf("Error analysis:\n");
                    printf("1. Absolute error: |Newton-Leibniz - trapezoidal| = %.10f\n", abs_error);
                    printf("2. Relative error: %.6f%%\n\n", rel_error_percent);
                    
                    printf("Interpretation:\n");
                    printf("- The trapezoidal method gives an approximate value\n");
                    printf("- The Newton-Leibniz formula gives the exact value\n");
                    printf("- Absolute error shows the difference between exact and approximate values\n");
                    printf("- Relative error shows this difference as a percentage of the exact value\n");
                } else {
                    printf("Error: integration limits not set\n");
                    printf("Please enter items 1 and 2 first\n");
}
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                getchar();
                break;
            }
            
            case 5: {
                system("@cls||clear");
                printf("Exiting program...\n");
                break;
            }
            
            default: {
                system("@cls||clear");
                printf("Invalid menu item. Please choose from 1 to 5\n");
                printf("Press Enter to continue...");
                clearInputBuffer();
                getchar();
                break;
            }
        }
        
    } while (choice != 5);
    
    return 0;
}