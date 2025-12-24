#include "../headers/Game.h"
#include <cstdlib>

Game::Game() {
    pieces = creatPieces();
		nextPiece = rand() % pieces.size();
    newPiece();
	}
	
	void Game::newPiece() {
		curPiece = nextPiece;
		nextPiece = rand() % pieces.size();
    curRot = 0; 
		// the formula of computing center of board;
		curX = (Board::WIDTH - Piece::SIZE) / 2;
		curY = 0;
		
	// curX and curY are standard values for appearing the new piece
	// it the center and the top of the board,
	// change that position and see what happen

    if(board.checkCollides(curX, curY, curRot, pieces[curPiece])) {
				gameOver = true;
				return;

    }
}

void Game::reset() {
		board = Board();
		score = 0;
		level = 0;
		clearedLines = 0;
		gameOver = false;

}


bool Game::isGameOver() const {
		return gameOver;
}
void Game::moveLeft() { 
	if(!board.checkCollides(curX - 1, curY, curRot, pieces[curPiece])) 
				--curX; 
}
void Game::moveRight(){ 
		if(!board.checkCollides(curX+1, curY, curRot, pieces[curPiece])) 
					++curX; 
}
void Game::rotate() { 
	int nextRot = (curRot + 1) % 4; 
	if(!board.checkCollides(curX, curY, nextRot, pieces[curPiece])) 
				curRot = nextRot;

}
void Game::moveDown(){ 
		if(!board.checkCollides(curX, curY+1, curRot, pieces[curPiece])) 
				++curY; 
}
void Game::moveInstantlyDown(){
    while(!board.checkCollides(curX, curY + 1, curRot, pieces[curPiece])) 
					++curY;

    board.placePiece(curX, curY, curRot, pieces[curPiece]);
    
		int lines = board.clearLines();  
		clearedLines += lines;
    switch(lines) {
        case 1: score += 100; break;
        case 2: score += 300; break;
        case 3: score += 500; break;
        case 4: score += 800; break;
    }
		level = clearedLines / 4;

    newPiece();
}
