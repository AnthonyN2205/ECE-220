#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/* withinBounds - checks if the current (row,col) position is within the maze's bounds
 *
 * inputs: maze - pointer to maze struct
 *         row - current row index
 *         col - current col index
 *
 * outputs: 1 - true
 *          0 - false
 */
int withinBounds(maze_t *maze, int row, int col){
    return (row < 0 || row >= maze->height || col < 0 || col >= maze->width);
}



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
        for (j = 0; j < maze->width; j++){
            /* read char from file and assign to cell */
            char c = fgetc(file);

            /* ignore newline chars */
            if (c == '\n' || c == '\0')
                break;
                
            maze->cells[i][j] = c;

            /* get start and ending cells */
            if (c == START){
                maze->startRow = i;
                maze->startColumn = j;
            }
            else if (c == END){
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
    int i;
    /* free each row */
    for (i = 0; i < maze->height; i++)
        free(maze->cells[i]);

    /* free array pointer */
    free(maze->cells);
    /* free the pointer */
    free(maze);
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
        for (j = 0; j < maze->width; j++)   
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
    /* maze is solved */
    if (col == maze->endColumn && row == maze->endRow){
        /* restore starting and ending marks */
        maze->cells[maze->startRow][maze->startColumn] = START;
        maze->cells[maze->endRow][maze->endColumn] = END;
        return 1;
    }
    /* invalid position */
    if (!withinBounds(maze,col,row))
        return 0;

    /* set (row,col) as part of solution */
    maze->cells[row][col] = PATH;

    /*    check 4 adjacent cells where X is the current cell
     *     
     *           2
     *         1 X 3
     *           4
     */

    // check cell 1 
    if (solveMazeDFS(maze, col-1, row)) return 1;
    // check cell 2
    if (solveMazeDFS(maze, col, row-1)) return 1;
    // check cell 3
    if (solveMazeDFS(maze, col+1, row)) return 1;
    // check cell 4
    if (solveMazeDFS(maze, col, row+1)) return 1;

    /* unmark and mark as visited */ 
    maze->cells[row][col] = VISITED;

    return 0;
}
