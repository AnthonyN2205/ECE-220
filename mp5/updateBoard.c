

/* keep track of the old board before updating it */
int *oldBoard;


/* validCell - Checks (in row-major order) if the current (row,col) index is within [0, boardRowSize*boardColSize-1];
 *
 * inputs: 
 *         board - 1-D game board
 *         boardRowSize - how many rows on board
 *         boardColSize - how many cols on board
 *         row - current row index
 *         col - current col index
 *         count - neighbor count
 *
 * outputs: none
 *
 */
void validCell(int *board, int boardRowSize, int boardColSize, int row, int col, int *count){
    /* row-major order = row*BoardColSize + col */
    int index = row*boardColSize + col;

    /* check if it's a valid index */
    if (index >= 0 && index < (boardRowSize*boardColSize)-1)
        /* if it's alive, then increment neighbor count */
        if (board[index])
            count++;
}


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int *neighbors = 0;

    /* neighbors to check (X is the current index) 
     *
     *          A B C
     *          D X E
     *          F G H
     */

    /* check if all these adjacent cells are 1(alive) && valid(within range), neighbors will be incremented if both conditions hold 
     * 
     * checking cells in the order of A,B,C, ..., G,H
     *
     */
    validCell(board, boardRowSize, boardColSize, row - 1, col - 1, neighbors);
    validCell(board, boardRowSize, boardColSize, row - 1, col, neighbors);
    validCell(board, boardRowSize, boardColSize, row - 1, col + 1, neighbors);
    validCell(board, boardRowSize, boardColSize, row, col - 1, neighbors);
    validCell(board, boardRowSize, boardColSize, row, col + 1, neighbors);
    validCell(board, boardRowSize, boardColSize, row + 1, col - 1, neighbors);
    validCell(board, boardRowSize, boardColSize, row + 1, col, neighbors);
    validCell(board, boardRowSize, boardColSize, row + 1, col + 1, neighbors);

    return *neighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int i, j;

    /* check every cell */
    for (i = 0; i < boardRowSize; i++)
        for (j = 0; j < boardColSize; j++){
            /* save old board before updating */
            oldBoard[i*boardColSize + j] = board[i*boardColSize + j];
            /* if the current cell is alive, check neighbors */
            if (board[i*boardColSize+j]){
                /* current cell will die if neighbor count is not 2 or 3 */
                if (countLiveNeighbor(board, boardRowSize, boardColSize, i, j) < 2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j) > 3)
                    board[i*boardColSize+j] = 0;
            }
            /* if current cell is dead, check if there are exactly 3 neighbors */
            else if (!board[i*boardColSize+j])
                /* dead cell becomes alive if exactly 3 neighbors are present */
                if (countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3)
                    board[i*boardColSize+j] = 1;
        }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int i,j;

    for (i = 0; i < boardRowSize; i++)
        for (j = 0; j < boardColSize; j++)
            /* if the new board is different than the old board, an alive cell changed */
            if (oldBoard[i*boardColSize+j] != board[i*boardColSize+j])
                return 0;

    /* board stayed the same, so we're done */
    return 1;
}

				
				
			

