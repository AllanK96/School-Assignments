#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

//Multiplication function
Complex_type multiply(struct complex_tag x, struct complex_tag y){

        //Create Complex_type struct
        Complex_type a, b, answer;

        //Set the Complex_type structs
        a.real = x.real;
        b.real = y.real;

        //Separate Real and imaginary
        double aReal = a.real, aImag = a.imaginary, bReal = b.real, bImag = b.imaginary;

        //Calculate and return
        answer.real = (aReal * bReal) - (aImag * bImag);
        answer.imaginary = (bReal * aImag) + (aReal * bImag);
        return answer;
}

//Division Function
int division(struct complex_tag *a, struct complex_tag *b, struct complex_tag *result){

        //Split real and imaginary
        double aReal = a->real, aImag = a->imaginary, bReal = b->real, bImag = b->imaginary;

        //Calculate and set result to real and imaginary parts using -> because of pointer
        result->real = ((aReal * bReal) + (aImag * bImag)) / ((bReal * bReal) + (bImag * bImag));
        result->imaginary = ((bReal * aImag) - (aReal * bImag)) / ((bReal * bReal) + (bImag * bImag));

        //Return -2 if bReal^2 + bImag^2 = 0
        if (((bReal * bReal) + (bImag * bImag)) == 0){
                return -2;
        }

        //else return 0
        return 0;
}

//Part D
int sumDif(struct complex_tag a, struct complex_tag b, struct complex_tag **sum, struct complex_tag **dif){

        //Create variables and allocate memory
        struct complex_tag *sumTmp;
        sumTmp= (struct complex_tag *) malloc(sizeof(sum));
        struct complex_tag *difTmp;
        difTmp = (struct complex_tag *) malloc(sizeof(dif));

        //Check to see if memory was successfully allocated
        if ((sumTmp == NULL) || (difTmp == NULL)){
                printf("Memory could not be allocated\n");
                return -1;
        }

        //Split into real and imaginary parts
        double aReal = a.real, aImag = a.imaginary, bReal = b.real, bImag = b.imaginary;

        //Set one of the variables to the sum of the 2 complex numbers
        sumTmp->real = aReal + bReal;
        sumTmp->imaginary = aImag + bImag;

        //Set the other to the difference between them
        difTmp->real = aReal - bReal;
        difTmp->imaginary = aImag - bImag;

        //Point to each sum and difference using the pointers in the parameters
        *sum = sumTmp;
        *dif = difTmp;

        return 0;
}


