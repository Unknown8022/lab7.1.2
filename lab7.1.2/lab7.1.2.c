#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define M_PI 3.14
double f(double x) 
{
    if (x <= -M_PI / 2) 
    {
        return sin(2) * cos(x / 2);
    }
    else if (x > -M_PI / 2 && x < M_PI / 2)
    {
        return fabs(x - (M_PI / 2));
    }
    else 
    {
        return (x - 1) / (2 + sqrt(x));
    }
}
// Метод прямокутників
double integral_rectangle(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    for (double x = a; x < b; x += step) 
    {
        sum += func(x) * step;
    }
    return sum;
}
// Метод трапецій
double integral_trapezoid(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    for (double x = a; x < b; x += step) 
    {
        sum += (func(x) + func(x + step)) * step / 2;
    }
    return sum;
}
// Метод Сімпсона
double integral_simpson(double (*func)(double), double a, double b, double step) 
{
    double sum = 0.0;
    int n = (b - a) / step;
    if (n % 2 != 0) n++; 
    double h = (b - a) / n;
    for (int i = 0; i <= n; i++) {
        double x = a + i * h;
        if (i == 0 || i == n)
            sum += func(x);
        else if (i % 2 == 0)
            sum += 2 * func(x);
        else
            sum += 4 * func(x);
    }
    return sum * h / 3;
}
int main() 
{
    FILE* file = fopen("output_custom.txt", "w");
    if (file == NULL) 
    {
        printf("Помилка відкриття файлу.\n");
        return 1;
    }
    double step = 0.1;
    double x, y, prev_y, next_y;
    // Табуляція
    fprintf(file, "x ");
    for (x = -M_PI; x <= 3; x += step) 
    {  
        fprintf(file, "%.2f ", x);
    }
    fprintf(file, "\n");

    fprintf(file, "y ");
    for (x = -M_PI; x <= 3; x += step) 
    {
        y = f(x);
        fprintf(file, "%.3f ", y);
    }
    fprintf(file, "\n");
    // Позначення екстремумів
    fprintf(file, "Extrema ");
    for (x = -M_PI; x <= 3; x += step) 
    {
        y = f(x);
        prev_y = f(x - step);
        next_y = f(x + step);
        if (y > prev_y && y > next_y) 
        {
            fprintf(file, "Max ");
        }
        else if (y < prev_y && y < next_y) 
        {
            fprintf(file, "Min ");
        }
        else 
        {
            fprintf(file, "--- ");
        }
    }
    fprintf(file, "\n");
    double a = -M_PI, b = 3; 
    double integral_rect = integral_rectangle(f, a, b, step);
    double integral_trap = integral_trapezoid(f, a, b, step);
    double integral_simp = integral_simpson(f, a, b, step);
    fprintf(file, "Integral [%.2f, %.2f]\n", a, b);
    fprintf(file, "Rectangle: %.5f\n", integral_rect);
    fprintf(file, "Trapezoid: %.5f\n", integral_trap);
    fprintf(file, "Simpson: %.5f\n", integral_simp);
    fclose(file);
    printf("Saved in output_custom.txt\n");
    return 0;
}