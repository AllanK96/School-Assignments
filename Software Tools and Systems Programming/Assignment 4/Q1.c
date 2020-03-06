#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//in hindsight, function isn't necessary
double deviationCalc(double a[], double mean);

int main(void){

double x, y, counter, mean, stdDeviation, piApprox[10]={0};
int i, j, N;

srand((unsigned) time(NULL));

do{
        printf("Enter a large integer: ");
        scanf("%d", &N);
}while(N<10);

for(j = 0; j < 10; j++){

        counter = 0;            //reset for each loop
        for (i = 0; i < N; i++){

                // x and y random values between 0 and 1
                x = (double)rand()/RAND_MAX;
                y = (double)rand()/RAND_MAX;

                // if the sum is less than 1, the point is in the area
                if ((x*x)+(y*y) <= 1){
                        counter++;
                }
        }
        piApprox[j] = ((counter/(double) N) * 4);
        mean += piApprox[j];
        printf("The approximation of pi at %d is: %f\n", j, piApprox[j]);
}


mean = (mean/10);
stdDeviation = deviationCalc(piApprox,mean);


printf("The mean is: %f\n", mean);
printf("The standard deviation is: %.6f\n", stdDeviation);

return 0;
}

double deviationCalc(double a[], double mean){
        int i;
        double value=0;

        for(i=0;i<10;i++){
                value += pow(a[i] - mean, 2);           //Standard deviation formula
        }

        return sqrt(value/10);
}

