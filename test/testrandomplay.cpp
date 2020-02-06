#define DIMEN 15

#include <iostream>
#include <utility>

#include "displayboard.h"
#include "montecarloai.h"
#include "enum.h"

int index(int row, int col) {
    std::cout << "index=" << row * DIMEN + col << std::endl;
    return row * DIMEN + col;
}

int main() {
    DisplayBoard display(DIMEN);
    AI *ai = new MonteCarloAI();
    ai->reset(1, GOMOKU_RENJU_BASIC);
    int playCount = 0;

    while (true) {
        int indexToPlay;
        WhoWin whoWin;
        if (playCount % 2 == 0 ) {
            int r, c;
            display.getInput(&r, &c);
            indexToPlay = index(r, c);
            whoWin = ai->play(indexToPlay);
        } else {
            std::pair<WhoWin, int> randomResult = ai->randomPlay();
            whoWin = randomResult.first;
            indexToPlay = randomResult.second;
        }
        
        display.play(indexToPlay / DIMEN, indexToPlay % DIMEN);

        if (whoWin == BLACK_WIN) {
            std::cout << " BLACK wins!" << std::endl; break;
        } else if (whoWin == WHITE_WIN) {
            std::cout << " WHITE wins!" << std::endl; break;
        }
        playCount++;
    }
}