#define DIMEN 15

#include <iostream>
#include <fstream>
#include <utility>
#include <time.h>
#include <stdlib.h>

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
	    	*file << "T\n"; 
	    	std::cout << "TIE" << std::endl;
	    	break;
	    }

	    WhoWin whoWin;

	    if (rand() % 100 < 10) {
	    	std::pair<WhoWin, int> randomResult = ai->randomPlay();
	    	whoWin = randomResult.first;
	    	indexToPlay = randomResult.second;
	    	*file << "R";
	    	std::cout << "R";
	    } else {
	    	whoWin = ai->play(indexToPlay);
	    }

	    *file << indexToPlay << " ";
	    std::cout << indexToPlay << std::endl;
	    

	    if (whoWin == BLACK_WIN) {
	        *file << "B\n"; 
	        std::cout << "B WIN" << std::endl;
	        break;
	    } else if (whoWin == WHITE_WIN) {
	        *file << "W\n"; 
	        std::cout << "W WIN" << std::endl;
	        break;
	    }
	}
}

int main() {
	srand(time(NULL));
    AI *ai = new MonteCarloAI();
    std::ofstream file("selfplay_freestyle.txt");

    for (int i = 0; i < 2; ++i) {
    	printGameInfo(&file, i+1, GOMOKU_FREESTYLE, 0);
    	std::cout << "GAME " << i+1 << std::endl;
    	selfplay(&file, ai, GOMOKU_FREESTYLE, 0);
    }

    file.close();
}
