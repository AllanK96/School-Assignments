#include <stdio.h>

int main(void){

float e=1.0, limit, currentTerm = 1.0;
int count = 1;

printf("Please enter a limit for the term: ");
scanf("%f", &limit);

//yet another loop to check if valid
while(limit <= 0){
        printf("Please enter a POSITIVE LOWER LIMIT: ");
        scanf("%f", &limit);
}

//keep adding until the limit is greater than the current term
while (currentTerm > limit){
        float x = 1;
        currentTerm = 1.0; //resets each iteration so that it can be divided
        count++;

        for(x=1; x<count; x++){
                currentTerm = currentTerm/x;    //term divided by the factorial
        }
        e+= currentTerm; //add it to e
}

printf("e is %.15f after %d terms\n", e, count);

}

