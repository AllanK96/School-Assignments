#include <stdio.h>

int main(void){
int TimeofDay,TimeDuration, minuteSlot = 0, hourSlot = 0,result = 0;

printf("Enter an integer time of day:  ");
scanf("%d", &TimeofDay);

//make sure time is a valid interger input (doesn't include non-ints)
while ((TimeofDay > 2400 || TimeofDay < 0)|| (TimeofDay%100)>= 60){
        printf("Please enter a VALID time of Day:  ");
        scanf("%d", &TimeofDay);
}

printf("Enter an integer  time duration:  ");
scanf("%d", &TimeDuration);

//make sure time is a valid input
while ((abs(TimeDuration % 100)) > 60){
        printf("Please enter a VALID time duration:  ");
        scanf("%d", &TimeDuration);
}

//calculates new time
result = TimeofDay + TimeDuration;
minuteSlot = (result%100);

if (minuteSlot > 60){
        minuteSlot = minuteSlot - 60; //minutes go down
        hourSlot++;  //hour goes up if minutes more than 60
}
else if (minuteSlot < 0){
        minuteSlot = minuteSlot + 60;
}

hourSlot = hourSlot + result/100; //hour into integer

while (hourSlot > 24){
        hourSlot = hourSlot - 24;
}
while (hourSlot < 0){
        hourSlot = hourSlot + 24;
}
// sum everything together
result = (hourSlot*100) + minuteSlot;
printf("The time is now: %.4d", result);
}

