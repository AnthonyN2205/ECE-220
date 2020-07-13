
/* validCell - checks if the given [row][col] indicies are within the boundaries of the board.
 *             a valid index is [0, boardRowSize*boardColSize - 1]
 *
 * inputs: boardRowSize - how many rows on board
 *         boardColSize - how many cols on board
 *         row - current row index
 *         col - current col index
 * 
 * outputs: 0 - false, not within boundaries
 *          1 - true, within boundaries
 */
int validCell(int boardRowSize, int boardColSize, int row, int col){
    /* row-major order = row*BoardColSize + col */
    int index = row*boardColSize + col;

    return (index >= 0 && index < (boardRowSize*boardColSize)-1);
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
    /* check the 8 adjacent cells of board[row][col] */
    //int i, j;
    int neighbors = 0;

    



    return neighbors;
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
    return 1;
}

				
				
			

