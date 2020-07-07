/* Alnguyn2 - MP3
 *
 * This programs calculates and prints the nth row of the Pascal Triangle 
 * using the formula ∏(n+1-i)/i for i = 1...k where 0 <= k <= n The program asks the user to 
 * input the row index they want calculated and will output that row. Row can be from 0...40
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Calculates and prints the nth row of the Pascal Triangle */
void pascalTriangle(int n);

int main()
{
    int row;

    printf("Enter a row index: ");
    scanf("%d",&row);

    /* prints the row of a pascal triangle */
    pascalTriangle(row);

    return 0;
}

/* Prints the nth row of the Pascal Triangle */
void pascalTriangle(int n){
    int k;
    int i;

    /* 0 <= k <= n */
    for (k = 0; k <= n; k++){
        unsigned long coef = 1;

        /* calculate (n + 1 - i) / i  for 1 <= i <= k */
        for (i = 1; i <= k; i++)
            /* guess C doesn't have compound assignemnts :( */
            coef = coef * (n + 1 - i) / i;
        
        /* print coef */
        printf("%li ", coef);
    }
  
    printf("\n"); 
}


