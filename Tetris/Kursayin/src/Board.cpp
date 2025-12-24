#include "Board.h"
#include <cstring>

bool Board::checkCollides(int newx, int newy, int curRot, const Piece &p) {
  int x,y = 0;  
	for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if(p.rotations[curRot][i][j]) {
                 x = newx + j;
                 y = newy + i;
                if(x < 0 || x >= WIDTH || y >= HEIGHT) 
										return true;
									
                if(y >= 0 && grid[y][x] != 0)
										return true;
								
            }

    return false;
}

void Board::placePiece(int x, int y, int curRot, const Piece &p) {
	//This is the function that “locks” the tetromino into the board and will never move again unless lines get /cleared.
  int boardx, boardy = 0;  
	for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if(p.rotations[curRot][i][j]) {
                boardx = x + j;
                boardy = y + i;
                if( boardy >= 0) 
									grid[boardy][boardx] = p.color;
            }
}

int  Board::clearLines() {
		bool full;
		int clearedLines = 0;
		for(int i = HEIGHT - 1; i >= 0; --i) {
				full = true;
				for(int j = 0; j < WIDTH; ++j) {
						if (grid[i][j] == 0) {
								full = false;
								break;
						}
				}
				if (full) {
						++clearedLines;
						for(int k = i; k > 0; --k) {
								for(int j = 0; j < WIDTH; ++j) {
									grid[k][j] = grid[k - 1][j];
								}
						}

						for(int col = 0; col < WIDTH; ++col) {
								grid[0][col] = 0;
						}
						//To re-check the same row index again, because its content changed after shifting.
							++i;
				}

		}
		return clearedLines;
}