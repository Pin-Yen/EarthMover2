#define DIMEN 15

#include <iostream>
#include <fstream>

#include "displayboard.h"
#include "montecarloai.h"
#include "enum.h"

void printGameInfo(std::ofstream *file, int gameNo, Rule rule, int aiLevel) {
	*file << "Game_No: " << gameNo
	      << " Game_Type: " << (rule == GOMOKU_FREESTYLE ? "freestyle" : "renju")
	      << " AI_Level: " << aiLevel << "\n";
}

void selfplay(std::ofstream *file, AI *ai, Rule rule, int aiLevel) {
	ai->reset(aiLevel, rule);

	while (true) {
	    int indexToPlay;

	    indexToPlay = ai->think();

	    // Tie
	    if (indexToPlay == -1) {
	    	*file << "T\n"; break;
	    }

	    *file << indexToPlay << " ";

	    WhoWin whoWin = ai->play(indexToPlay);

	    if (whoWin == BLACK_WIN) {
	        *file << "B\n"; break;
	    } else if (whoWin == WHITE_WIN) {
	        *file << "W\n"; break;
	    }
	}
}

int main() {
    AI *ai = new MonteCarloAI();
    std::ofstream file("selfplay_freestyle.txt");

    for (int i = 0; i < 1; ++i) {
    	printGameInfo(&file, i+1, GOMOKU_FREESTYLE, 2);
    	selfplay(&file, ai, GOMOKU_FREESTYLE, 2);
    }

    file.close();
}
