#include <stdio.h>

//This code has been used to compute the mantissa (fraction) bits of 2.1, 6300 and -1.044 in order to convert them to SP and DP formats
//Exponent and sign bits has been computed manually
#define SP 23
#define DP 52

int mantissa[DP];
float decimal = 0.044;

int main()
{
    for(int i = 0; i<DP; i++){
        decimal = decimal * 2;
        if( (int) decimal == 0){
            mantissa[i] = 0;
        }else{
            mantissa[i] = 1;
            decimal -= 1;
        }
    }
    printf("Mantissa: ");
    for(int i = 0; i<DP; i++){
        printf("%d", mantissa[i]);
    }
    printf("\n");
}