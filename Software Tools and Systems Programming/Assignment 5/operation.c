#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

int main(int argc, char *argv[]){

if (argc != 5){
        printf("Need 4 arguments\n");
        return 0;
}

//complex tag and type variables
struct complex_tag a, b;

struct complex_tag *quotient;
quotient =  (struct complex_tag *) malloc(sizeof(struct complex_tag));
struct complex_tag **sum;
sum = malloc(sizeof(struct complex_tag));
struct complex_tag **difference;
difference = (struct complex_tag **) malloc(sizeof(struct complex_tag));

Complex_type product;

//Set structure with arguments
a.real = atof(argv[1]);
a.imaginary = atof(argv[2]);
b.real = atof(argv[3]);
b.imaginary = atof(argv[4]);

//Call the multiplication function, with tag a and b
product = multiply(a,b);

//Call the division function, with a pointer to a, b, and the result, returns an int
int i = division(&a, &b, quotient);

//Call sum difference function, with tags a and b, and pointers to sum and difference structures
//Returns an int
int j = sumDif(a, b, sum, difference);

//Print complex numbers
printf("First complex number is: %.4f + %.4fi \n", a.real, a.imaginary);
printf("Second complex number is: %.4f +  %.4fi \n", b.real, b.imaginary);

//Multiplication
printf("The product of the complex numbers: %.4f", product.real);
if (product.imaginary >= 0) {
        printf(" + %.4fi \n", product.imaginary);
}else{
        //print negative sign with positive val
        printf(" - %.4fi \n", product.imaginary -= (product.imaginary * 2));
}

//Division
if (i == (-2)){
        printf("0 on denominator\n");
}else{
        printf("The quotient of the complex numbers: %.4f", quotient->real);
        if (quotient->imaginary >= 0){
                printf(" + %.4fi \n", quotient->imaginary);
        }
        else{
                //negative sign with positive val
                printf(" - %.4fi \n", quotient->imaginary -= (quotient->imaginary * 2));
        }
}


//Error with memory allocation
if (j == (-1)){
        printf("Error allocating memory");
}else{
        //Sum
        printf("Sum of the complex numbers: %.4f + %.4fi \n", (*sum)->real, (*sum)->imaginary);

        //Difference
        printf("The difference between the first complex number and second complex number: %.4f + %.4fi \n", (*difference)->real, (*difference)->imaginary);
}


return 0;
}

