#include <stdio.h>

int main(void){

float monthlyPayment, loanAmount, interestRate, remainingBalance, n;
int counter = 0;

printf("Enter a loan amount: ");
scanf("%f", &loanAmount);


//check if input is valid (greater thasn 0)
while(loanAmount < 0){
        printf("Please enter A VALID LOAN AMOUNT: ");
        scanf("%f", &loanAmount);
}

printf("Please input an interest rate: ");
scanf("%f", &interestRate);

//check if input is valid interest rate (under 100%)
while(interestRate > 100 || interestRate < 0){
        printf("Please enter a VALID INTEREST RATE: ");
        scanf("%f", &interestRate);
}

// Monthly interest rate
interestRate = (interestRate/100)/12;

printf("Please enter a monthly payment: ");
scanf("%f", &monthlyPayment);

//Check for valid input
while(monthlyPayment < 0){
        printf("Please enter a VALID MONTHLY PAYMENT: ");
        scanf("%f", &monthlyPayment);
}

//number of monthly payments
printf("Please enter a number of monthly payments; ");
scanf("%f", &n);

//check for valid input, god this is repeatative
while(n < 0){
        printf("Please enter a VALID NUMBER OF MONTHLY PAYMENTS: ");
        scanf("%f", &n);
}

//prints monthly payments woooooooo

while (n > counter){
        //remaining balance after 1 payment
        remainingBalance = loanAmount + (loanAmount * interestRate) - monthlyPayment;
        counter++;
        //prints balance after each payment
        printf("Current balance after payment %d is $%.2f\n",counter,remainingBalance);
        if ((remainingBalance - monthlyPayment) < 0){
                remainingBalance = remainingBalance + (remainingBalance*interestRate);
                printf("The final charge is $%.2f\n", remainingBalance);
                remainingBalance = 0;
                printf("Balance is now $%.2f\n", remainingBalance);
                printf("Payments are now completed\n");
                break;
        }
        loanAmount = remainingBalance; //update loan amount to current balance
}
}

