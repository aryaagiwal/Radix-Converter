#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * convert_to_decimal(int number, int frac, int radix) {
    static int num[2];
    num[0] = 0;
    int factor = 0;
    printf("%d and %d",number,frac);
    while (number > 0) {
        num[0] += (number%10 * pow(radix,factor));
        factor++;
        number /= 10;
    }
    while (frac < 9999) {
        frac *= 10;
    }
    num[1] = 0;
    num[1] += (frac % 10) * pow(radix, -5) * pow(10,5);
    frac /= 10;
    frac *= 10;
    num[1] += (frac % 100) * pow(radix, -4) * pow(10,4);
    frac /= 100;
    frac *= 100;
    num[1] += (frac % 1000) * pow(radix, -3) * pow(10,3);
    frac /= 1000;
    frac *= 1000;
    num[1] += (frac % 10000) * pow(radix, -2) * pow(10,2);
    frac /= 10000;
    frac *= 10000;
    num[1] += (frac % 100000) * pow(radix, -1) * pow(10,1); 
    return num;
}

int * convert_dec_to_n(int number[2], int radix) {
    int whole_portion = number[0];
    int frac_portion = number[1];
    int new_whole = 0;
    int mult_factor = 1;
    while (whole_portion/radix > 0) {
        new_whole += (whole_portion%radix) * mult_factor;
        mult_factor *= 10;
        whole_portion /= radix;
    }
    new_whole += whole_portion * mult_factor;
    //whole portion done
    //now have to find fractional portion
    int new_frac = 0;
    static int num[2];
    num[0] = new_whole;
    num[1] = 0;
    new_frac = (frac_portion % 100000) / ((pow(radix, -1) * pow(10,5)));
    new_frac *= pow(10,4);
    num[1] += new_frac;
    frac_portion = frac_portion % (int) ((pow(radix, -1) * pow(10,5)));

    new_frac = (frac_portion % 10000) / ((pow(radix, -1) * pow(10,4)));
    new_frac *= pow(10,3);
    num[1] += new_frac;
    frac_portion = frac_portion % (int) ((pow(radix, -1) * pow(10,4)));

    new_frac = (frac_portion % 1000) / ((pow(radix, -1) * pow(10,3)));
    new_frac *= pow(10,2);
    num[1] += new_frac;
    frac_portion = frac_portion % (int) ((pow(radix, -1) * pow(10,3)));

    new_frac = (frac_portion % 100) / ((pow(radix, -1) * pow(10,2)));
    new_frac *= pow(10,1);
    num[1] += new_frac;
    frac_portion = frac_portion % (int) ((pow(radix, -1) * pow(10,2)));

    num[1] += (frac_portion % 10) / ((pow(radix, -1) * pow(10,1)));
    
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
        printf("Enter a base:\n");
        int base = 0;
        scanf("%d", &base);
        int *num = convert_to_decimal(whole, frac, base);
        printf("Enter a base to convert to:\n");
        int new_base = 10;
        scanf("%d",&new_base);
        convert_dec_to_n(num, new_base);
    }
    return EXIT_SUCCESS;
}
