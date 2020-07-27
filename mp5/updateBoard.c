/* Alnguyn2 - MP5
 * 
 * This MP implements the Game of Life devised by John Horton Conway. It uses a 1-D array
 * as the game board that is set with alive(1) and dead(0) cells. The game continously updates
 * based on the adjacent cells. The game ends when there are no more changes to the board.
 * The functions were implemented using the fact that the next board must be generated
 * based on the current board. The current state of the board must be saved into a temp board
 * and then updating after calculating the next state of the board.
 * 
 *
 */


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
 * outputs: 1 if alive && valid
 *          0 otherwise
 *
 */
int validCell(int *board, int boardRowSize, int boardColSize, int row, int col){
    /* check if invalid index */
    if (row < 0 || col < 0 || row >= boardRowSize || col >= boardColSize)
        return 0;
    /* row-major order */
    int index = row*boardColSize + col;

    /* check if it's a valid index */
    if (index >= 0 && index < boardRowSize*boardColSize)
        /* if it's alive, then it's a valid neighbor */
        if (board[index])
            return 1;

    return 0;
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
    /* neighbors to check (X is the cell to check) 
     *
     *          A B C
     *          D X E
     *          F G H
     */

    /* check if all these adjacent cells are 1(alive) && valid(within range)
     * 
     * checking cells in the order of A,B,C, ..., G,H
     *
     * The total neighbor count is the sum of all valid & alive neighbors
     */
    return  validCell(board, boardRowSize, boardColSize, row - 1, col - 1) +
            validCell(board, boardRowSize, boardColSize, row - 1, col) +
            validCell(board, boardRowSize, boardColSize, row - 1, col + 1) +
            validCell(board, boardRowSize, boardColSize, row, col - 1) +
            validCell(board, boardRowSize, boardColSize, row, col + 1) +
            validCell(board, boardRowSize, boardColSize, row + 1, col - 1) +
            validCell(board, boardRowSize, boardColSize, row + 1, col) +
            validCell(board, boardRowSize, boardColSize, row + 1, col + 1);
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
    int oldBoard[boardRowSize*boardColSize];

    /* Save the current state since we can't update board in real-time */
    for (i = 0; i < boardRowSize*boardColSize; i++)
        oldBoard[i] = board[i];

    /* check every cell in row-major order */
    for (i = 0; i < boardRowSize; i++)
        for (j = 0; j < boardColSize; j++){
            /* if the current cell is alive, check its neighbors */
            if (oldBoard[i*boardColSize+j]){
                /* current cell will die if neighbor count is not 2 or 3 */
                if (countLiveNeighbor(board, boardRowSize, boardColSize, i, j) < 2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j) > 3)
                    oldBoard[i*boardColSize+j] = 0;
            }
            /* if current cell is dead, check if there are exactly 3 neighbors */
            else if (!oldBoard[i*boardColSize+j]){
                /* dead cell becomes alive if exactly 3 neighbors are present */
                if (countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3)
                    oldBoard[i*boardColSize+j] = 1;
            }
        }

    /* update the actual board */
    for (i = 0; i < boardRowSize*boardColSize; i++)
        board[i] = oldBoard[i];
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
    int i;    
    int nextBoard[boardRowSize*boardColSize];

    /* save current board to generate the next */
    for (i = 0; i < boardRowSize*boardColSize; i++)
        nextBoard[i] = board[i];

    /* generate the next board */
    updateBoard(nextBoard, boardRowSize, boardColSize);

    /* check if the next board is different than the current */
    for (i = 0; i < boardRowSize*boardColSize; i++)
        /* board has been changed */
        if (nextBoard[i] != board[i])
            return 0;

    /* board stayed the same, so we're done */
    return 1;
}

				
				
			

