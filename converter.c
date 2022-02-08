#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * convert_to_decimal(int number, int frac, int radix) {
    static int num[2];
    double decimal_value = 0;
    int factor = 0;

    //printf("%d and %d",number,frac);
    while (number > 0) {
        decimal_value += (number%10 * pow(radix,factor));
        factor++;
        number /= 10;
    }
    //printf("(%f)  ",decimal_value);
    num[0] = decimal_value;
    decimal_value = 0;

    int len = 0;
    int temp = frac;
    while (temp > 0) {
        len++;
        temp /= 10;
    }

    int frac_factor = -1 * len;
    int mult_factor = 10;
    while (frac > 0) {
        decimal_value += (frac % 10) * pow(radix, frac_factor);
        frac_factor++;
        frac /= 10;
        mult_factor *= 10;
    }
    //printf("%f",decimal_value);
    num[1] = decimal_value * mult_factor * 10;
    return num;
}

int * convert_dec_to_n(int number[2], int new_base) {
    int whole_portion = number[0];
    int frac_portion = number[1];
    //printf("(%d.%d)",whole_portion,frac_portion);
    int new_whole = 0;
    int mult_factor = 1;
    while (whole_portion/new_base > 0) {
        new_whole += (whole_portion%new_base) * mult_factor;
        mult_factor *= 10;
        whole_portion /= new_base;
    }
    new_whole += whole_portion * mult_factor;

    //whole portion done
    //now have to find fractional portion
    int new_frac = 0;
    static int num[2];
    num[0] = new_whole;

    printf("%d.",new_whole);

    //first going to get length of fractional portion
    int len = 0;
    int temp = frac_portion;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    //now len stores len, and frac_portion stores actual fraction
    int buffer = 5;
    mult_factor = pow(10,len-1+buffer);
    frac_portion *= pow(10, buffer);
    int power_factor = -1;
    //printf("Decimal fraction is %d, and base is %d\n",frac_portion,new_base);
    while (frac_portion > 0 && mult_factor > 0) {
        new_frac += ((int) (frac_portion / (pow(new_base,power_factor) * pow(10,len+buffer)))) * mult_factor;
        int temp =   (pow(new_base,power_factor) * pow(10,len+buffer))  ;   
        //printf("%d",temp);
        //printf(" and the new fraction currently holds the value of %d",new_frac);
        
        frac_portion = frac_portion%((int) (pow(new_base,power_factor) * pow(10,len+buffer)));
        //printf(" and frac_portion has %d left.", frac_portion);
        power_factor--;
        mult_factor /= 10;
        num[1] = new_frac;
    }
    printf("%d",num[1]);
    num[1] = new_frac;
    return num;
}


int main() {
    printf("What would you like to do?\n");
    printf("1. Convert a non base 10 number to its base 10 form\n");
    printf("2. Convert a number from base 10 to a base of your choice\n");
    printf("3. Covert a non base 10 number to a base of your choice\n");
    printf("Please pick an option (1, 2, or 3)");
    int option = 0;
    int whole = 0;
    int frac = 0;
    int base = 0;
    scanf("%d", &option);
    if (option > 3 || option < 1) {
        printf("invalid response");
    } else if (option == 1) {
        printf("Enter a number:\n");
        scanf("%d.%d", &whole, &frac);
        printf("Enter its base:\n");
        scanf("%d", &base);
        printf("%d", convert_to_decimal(whole, frac, base));
    } else if (option == 2) {
        printf("Enter a base 10 number:\n");
        scanf("%d.%d", &whole, &frac);
        printf("Enter a base to convert to:\n");
        int new_base = 10;
        scanf("%d",&new_base);
        int *num = convert_to_decimal(whole, frac, 10);
        convert_dec_to_n(num, base);
    } else {
        printf("Enter a number:\n");
        scanf("%d.%d", &whole, &frac);
        printf("Enter its base:\n");
        scanf("%d", &base);
        int *num = convert_to_decimal(whole, frac, base);
        printf("Enter a base to convert to:\n");
        int new_base = 10;
        scanf("%d",&new_base);
        convert_dec_to_n(num, new_base);
    }
    return EXIT_SUCCESS;
}
