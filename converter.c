#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double convert_to_decimal(int number, int frac, int radix) {
    double decimal_value = 0;
    int factor = 0;

    while (number > 0) {
        decimal_value += (number%10 * pow(radix,factor));
        factor++;
        number /= 10;
    }
    printf("(%f)  ",decimal_value);
    
    int len = 0;
    int temp = frac;
    while (temp > 0) {
        len++;
        temp /= 10;
    }

    int frac_factor = -1 * len;
    while (frac > 0) {
        decimal_value += (frac % 10) * pow(radix, frac_factor);
        frac_factor++;
        frac /= 10;
    }
    printf("%f",decimal_value);
    return decimal_value;
}


int main() {
    printf("Enter a number:\n");
    int whole = 0;
    int frac = 0;
    scanf("%d.%d", &whole, &frac);
    printf("Enter a base:\n");
    int base = 0;
    scanf("%d", &base);
    convert_to_decimal(whole, frac, base);
    return EXIT_SUCCESS;
}
