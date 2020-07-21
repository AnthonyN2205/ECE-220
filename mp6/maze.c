/* Alnguyn2 - MP6
 *
 * This program is a maze solver that uses backtracking and DFS to find a solution, if it exists.
 * The program first reads, from file, the dimensions of the maze and then the actual contents of the maze.
 * From there, it will print the unsolved version of the maze, solve the maze (again, if possible),
 * then print out the solution to the maze. After trying to solve the maze, any dynamically allocated
 * memory is freed ensuring no memory leaks.
 *
 */


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
     *          col row
     *          maze layout
     */
    fscanf(file, "%d %d", &maze->width, &maze->height);

    int i, j;
    char c;
    /* create an array of pointers */
    maze->cells = (char**)malloc(maze->height*sizeof(char*));
    /* allocate memory for every row */
    for (i = 0; i < maze->height; i++)
        maze->cells[i] = (char*)malloc(maze->width*sizeof(char));

    /* populate the maze */
    for (i = 0; i < maze->height; i++)
        for (j = 0; j < maze->width; j++){
            /* ignore newlines */
            if ((c = fgetc(file)) != '\n')
                maze->cells[i][j] = c;
            /* if it is a new line, push j back 1 */
            else
                j--;

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
        for (j = 0; j < maze->width; j++){ 
            if (maze->cells[i][j] == VISITED)
                printf("%c", EMPTY);
            else
                printf("%c", maze->cells[i][j]);

        }

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
        /* restore start and end marks */
        maze->cells[maze->startRow][maze->startColumn] = START;
        maze->cells[maze->endRow][maze->endColumn] = END;
        return 1;
    }

    /* index is outside of bounds */
    if (row < 0 || row >= maze->height-1 || col < 0 || col >= maze->width-1) return 0;
    /* non-empty cell */
    if (maze->cells[row][col] != EMPTY && maze->cells[row][col] != START && maze->cells[row][col] != END) return 0;


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
