#include<stdio.h>
#include<math.h>
#include<limits.h>

double f(double x);
double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);

int main() {
    printf("%20.20f\n", integrateSim(&f, 20000000, 0, 50));
    printf("%20.20f\n", integrateLSum(&f, 200000000, 0, 50));
}

double f(double x) {
    return pow(2.7182818284590452, x);
}
// LEFT SUM
double integrateLSum(double (*f)(double x), int n, double a, double b) {
    double deltax = (b-a)/n;
     double sum = 0;
    for (; a < b; a+=deltax) {
        sum += f(a);
    }
    return sum*deltax;
}

double integrateSim(double (*f)(double x), int n, double a, double b) {
    // 1 4 2 4 2 4 1
    double sum = f(a)+f(b);
    double deltax = (b-a)/n;
    int i = 0;
    while ((a += deltax) < b) {
        sum += f(a)*((++i)&1 ? 2 : 1);
    }
    return sum*deltax*(2.0/3);
}
