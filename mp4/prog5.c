/* Alnguyn2 - MP4
 *
 * This program implements a code-breaking game. The program ask a user to input a seed
 * then generates 4 random digits from [1,8], obviously hidden to the user. The user must then
 * try to guess the correct 4 sequence. The program will let the user know how close they are
 * based on the number of perfect matches and mismatched guesses. The user has 12 guesses to 
 * figure out the solution
 *
 */


/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]){
    int seed;
    char post[2];
    
    /* valid string; set seed */
    if (sscanf(seed_str, "%d%1s", &seed, post) == 1){
        srand(seed);
        return 1;
    }

    /* invalid string */
    printf("set_seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four){
    guess_number = 1;

    /* creates random number [1,8] */
    solution1 = rand() % 8 + 1;
    solution2 = rand() % 8 + 1;
    solution3 = rand() % 8 + 1;
    solution4 = rand() % 8 + 1;

    /* assign solution values */
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;

    //printf("%d %d %d %d\n", solution1, solution2, solution3, solution4);
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
    int w,x,y,z;
    int i, j;
    char post[2];

    /* place each solution into an array for easier checking */
    int solutions[4] = {solution1, solution2, solution3, solution4};

    int perfect_guesses = 0;
    int mismatched_guesses = 0;

    /* solution/guess paired indices */
    int paired_guesses[4] = {0,0,0,0};
    int paired_solutions[4] = {0,0,0,0};

    /* only if exactly 4 int values were read and the numbers are [1,8] */
    if (sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4 && valid_nums(w,x,y,z)){
        *one = w;
        *two = x; 
        *three = y;
        *four = z;

        int guesses[4] = {w,x,y,z};

        /* check for perfect guesses */
        for (i = 0; i < 4; i++)
            if (solutions[i] == guesses[i]){
                paired_guesses[i] = 1;
                paired_solutions[i] = 1;
                perfect_guesses++;
            }

        /* for any unpaired guesses, check for a solution */
        for (i = 0; i < 4; i++)
            if (!paired_guesses[i])
                /* guess is unpaired, now search for an unpaired solution */
                for (j = 0; j < 4; j++)
                    if (!paired_solutions[j] && solutions[j] == guesses[i]){
                        paired_guesses[i] = 1;
                        paired_solutions[j] = 1;
                        mismatched_guesses++;

                        /* stop the loop if we found a solution, otherwise we search repeated values */
                        break;
                    }

        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_guesses, mismatched_guesses);
        
        /* increment guess count */
        guess_number++;

        return 1;
    }
    
    /* not a valid guess */
    printf("make_guess: invalid guess\n");
    return 0;
}

/* valid_num(int w, int x, int y, int z) - checks if all numbers are between [1,8]
 *      
 * input: numbers to check
 * output: none
 *
 * return values: 0 - false, 1 - true
 *
 */
int valid_nums(int w, int x, int y, int z){
    return (w > 0 && w < 9 && x > 0 && x < 9 && y > 0 && y < 9 && z > 0 && z < 9);
}


