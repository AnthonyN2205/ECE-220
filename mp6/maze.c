#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    /* open file for read-only, assumes user ALWAYS inputs valid filename */
    FILE *file = fopen(fileName, "r");

    /* create maze struct */
    maze_t *maze = (maze_t*)malloc(sizeof(maze_t));

    /* read from file and populate the maze
     *
     * file format:
     *          row col
     *          maze layout
     */
    fscanf(file, "%d %d", &maze->width, &maze->height);

    int i, j;
    /* create an array of pointers */
    maze->cells = (char**)malloc(maze->height*sizeof(char*));
    /* allocate memory for every row */
    for (i = 0; i < maze->height; i++)
        maze->cells[i] = (char*)malloc(maze->width*sizeof(char));

    /* populate the maze */
    for (i = 0; i < maze->height; i++)
        for (j = 0; j <= maze->width; j++){
            /* read char from file and assign to cell */
            char c = getc(file);

            /* ignore newline chars */
            if (c != '\n')
                maze->cells[i][j] = c;

            /* get start and ending cells */
            if (c == 'S'){
                maze->startRow = i;
                maze->startColumn = j;
            }
            else if (c == 'E'){
                maze->endRow = i;
                maze->endColumn = j;
            }
        }

    /* close file */
    fclose(file);

    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j;

    for (i = 0; i < maze->height; i++){
        for (j = 0; j <= maze->width; j++)   
            printf("%c", maze->cells[i][j]);

        printf("\n");
    }
}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
