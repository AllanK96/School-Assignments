#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies);

int main(void){

int dollar, twenties, tens, fives, toonies, loonies;

//validation
do{
        printf("Enter an amount of money: ");
        scanf("%d", &dollar);
        if(dollar < 0){
                printf("PLEASE ENTER A VALID AMOUNT: \n");
        }
}while(dollar < 0);

pay_amount(dollar,&twenties, &tens, &fives, &toonies, &loonies);        //call using refrence

//print values
printf("Smallest number of bills and coins used for the dollar amount: $%d\n", dollar);
printf("$20: %d, $10: %d, $5: %d, $2: %d, $1: %d\n", twenties,tens,fives,toonies,loonies);	//number of each bill/coin

return 0;
}

void pay_amount( int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies){

*twenties=dollars/20;   //reference to dollars/20
dollars%=20;            //amount after mod20

*tens=dollars/10;
dollars%=10;

*fives=dollars/5;
dollars%=5;

*toonies=dollars/2;
dollars%=2;

*loonies=dollars;        //Reference to last dollar amount
}

