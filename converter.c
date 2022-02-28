#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * convert_to_decimal(int number, int frac, int radix, int dec) {
    static int num[2];
    num[0] = 0;
    int factor = 0;
    while (number > 0) {
        num[0] += (number%10 * pow(radix,factor));
        factor++;
        number /= 10;
    }
    while (frac < (int) pow(10,dec-1) - 1) {
        frac *= 10;
    }
    num[1] = 0;
    for (int i = dec; i > 0; i--) {
        num[1] += (frac % ((int) pow(10,dec+1-i))) * pow(radix, -i) * pow(10,i);
        frac /= pow(10,dec+1-i);
        frac *= pow(10,dec+1-i);
    }
    return num;
}

int * convert_dec_to_n(int num[2], int radix, int dec) {
    int frac_portion = num[1];
    int new_whole = 0;
    int mult_factor = 1;
    while (num[0]/radix > 0) {
        new_whole += (num[0]%radix) * mult_factor;
        mult_factor *= 10;
        num[0] /= radix;
    }
    new_whole += num[0] * mult_factor;
    //whole portion done
    //now have to find fractional portion
    int new_frac = 0;
    num[0] = new_whole;
    num[1] = 0;
    for (int i = dec; i > 0; i--) {
        new_frac = (frac_portion % ((int) pow(10,i))) / ((pow(radix, -1) * pow(10,i)));
        new_frac *= pow(10,i-1);
        num[1] += new_frac;
        frac_portion = frac_portion % (int) ((pow(radix, -1) * pow(10,i)));
    }
    printf("\n%d.%d\n\n",num[0],num[1]);
    return num;
}


int main() {
    printf("Welcome to the radix converter. You will be prompted ");
    printf("\nto enter a number along with its initial base. Then, ");
    printf("\nthe number will be converted to the next base inputted.\n");
    int run = 1;
    while(run) {
        printf("\nEnter a positive number (-1 to quit):\n");
        int whole = 0;
        int frac = 0;
        scanf("%d.%d", &whole, &frac);
        if (whole == -1) {
            run = 0;
            break;
        }
        printf("How many decimal places would you like? \n");
        int dec = 0;
        scanf("%d",&dec);
        printf("Enter a base:\n");
        int base = 0;
        scanf("%d", &base);
        int *num = convert_to_decimal(whole, frac, base, dec);
        printf("Enter a base to convert to:\n");
        int new_base = 10;
        scanf("%d",&new_base);
        convert_dec_to_n(num, new_base, dec);
    }
    return EXIT_SUCCESS;
}
