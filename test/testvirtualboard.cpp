#define DIMEN 15

#include "displayboard.h"
#include "virtualboardheuristicfreestyle.h"
#include "virtualboardheuristicrenjubasic.h"

#include <iostream>

int index(int row, int col) {
    std::cout << "index=" << row * DIMEN + col << std::endl;
    return row * DIMEN + col;
}

void debugBoard(VirtualBoard& board) {
    std::cout << (board.whoTurn() ? "White's" : "Black's") << " turn..." << std::endl;

    int highestScoreIndex = board.getHSI();
    if (highestScoreIndex != -1) {
        std::cout << "highestScoreIndex: " << (char) ('A' + highestScoreIndex % DIMEN)   << ","
                  <<highestScoreIndex / DIMEN + 1<< std::endl;
    } else {
        std::cout << "No significant point" << std::endl;
    } 

    std::cout << "HighestScore: " << board.getScore(highestScoreIndex) << std::endl;
    std::string arrow = "-\\|/";
    for (int dir=0; dir<4; ++dir) {
        for (int color=0; color<2; ++color) {
            std::cout << arrow[dir] << (color == 0 ? "X" : "O")
                       <<"(length, life, level) = (" 
                       << (int) board.point(highestScoreIndex)->type(dir).length(color)
                       << (int) board.point(highestScoreIndex)->type(dir).life(color)
                       << (int) board.point(highestScoreIndex)->type(dir).level(color)
                       << ")" << std::endl;

        }

    }
    std::cout << "Score sum: " << board.getScoreSum() << std::endl;

    return;
}


int main() {
    VirtualBoard* board = VirtualBoardHeuristicRenjuBasic::create(DIMEN);
    DisplayBoard display(DIMEN);

    while(true) {
        VirtualBoard *tmp = board->clone();
        delete board;
        board = tmp;
        debugBoard(*board);

        int r, c;
        display.getInput(&r, &c);
        GameStatus status = board->play(index(r, c));
        if (status == WINNING) {
            std::cout << (board->whoTurn() == 0 ? "BLACK" : "WHITE") << " wins!"
                      << std::endl;
                      break;
        } else if (status == LOSING) {
            std::cout << (board->whoTurn() == 0 ? "BLACK" : "WHITE") << " loses!"
                      << std::endl;
                      break;
        }
        display.play(r, c);
    }


    delete board;
}