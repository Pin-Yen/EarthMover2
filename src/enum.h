#ifndef ENUM_H_
#define ENUM_H_

enum Rule {GOMOKU_FREESTYLE, GOMOKU_RENJU_BASIC};

enum GameStatus { LOSING = -1, NOTHING = 0, WINNING = 1 };

enum WhoWin { BLACK_WIN = 0, WHITE_WIN = 1, NO_RESULT = -1};

enum StoneStatus { BLACK = 0, WHITE = 1, EMPTY = 2, BOUND = 3 };

enum SearchStatus { LOSE = -1, TIE = 0, WIN = 1, UNKNOWN, LEAF };

#endif 