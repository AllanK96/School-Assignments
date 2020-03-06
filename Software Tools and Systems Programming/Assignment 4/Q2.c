#include <stdio.h>

int main(void){
int size, counter = 2, row, column;

do{
        printf("Enter the size of magic square (Odd, between 1-99): ");
        scanf("%d", &size);
        if((size%2)==0)
                printf("INPUT A VALID SIZE \n");
} while((size%2 != 1) || (size > 99 || size < 1));

int magicSquare[size][size];            //create array of size

for (row = 0; row < size; row++){                       //set all values of magic square to 0
        for (column = 0; column < size; column++){
                magicSquare[row][column] = 0;
        }
}

row = 0, column = size/2;

//
//Realized after writing my whole program that we were supposed to use pointers
//To-do: Re-write program with pointers
//

magicSquare[row][column] = 1;

while(counter <= (size*size)){
        if((column == size-1) && row == 0){
                row = row+1;
                magicSquare[row][column] = counter;
                counter++;
        }
        else if(row == 0){
                row = size-1;
                column += 1;
                magicSquare[row][column] = counter;
                counter++;
        }
        else if(row==0 && column==0){
                row = size-1;
                column = column+1;
                magicSquare[row][column] = counter;
                counter++;
        }
        else if((row == size-1) && (column == size-1)){
                row = row - 1;
                column = 0;
                magicSquare[row][column] = counter;
                counter++;
        }
        else if(column == (size-1)){
                row = row -1;
                column = 0;
                magicSquare[row][column] = counter;
                counter++;
        }
        else{           //if nothing else is hit, then...
                if(magicSquare[row-1][column+1] != 0){          //check to see if visited
                        row = row + 1;
                        magicSquare[row][column] = counter;
                        counter++;
                }
                else{                                           //if not visited
                        row = row-1;
                        column = column+1;
                        magicSquare[row][column] = counter;
                        counter++;
                }
   	}
}

//prints magic square
for(row = 0; row < size; row++){
        for(column = 0; column < size; column++){
                printf("%d ", magicSquare[row][column]);
        }
        printf("\n");
}
return 0;
}

