#include "App.h"

int main() {

	runGame();
	return 0;

}

//g++ -std=c++17 \
    src/main.cpp \
    src/App.cpp \
    src/Game.cpp \
    src/Board.cpp \
    src/Piece.cpp \
    src/Scores.cpp \
    -Iheaders \
    -o tetris \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


