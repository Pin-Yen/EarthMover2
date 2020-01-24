#include "evaluatorrenjubasic.h"

EvaluatorRenjuBasic* EvaluatorRenjuBasic::singleton = NULL;

EvaluatorRenjuBasic* EvaluatorRenjuBasic::getInstance() {
  if (EvaluatorRenjuBasic::singleton == NULL)
    EvaluatorRenjuBasic::singleton = new EvaluatorRenjuBasic();
  return EvaluatorRenjuBasic::singleton;
}
void EvaluatorRenjuBasic::evaluateLocalScore(Point& point) {
  
  // These const are only for indexing purposes,
  // enhancing the readibility of the code.
  const int ATTACK = 0;
  const int DEFENSE = 1;
  const int BLACK = 0;
  const int WHITE = 1;
  const int LIVE = 1;
  const int DEAD = 0;

  int score[2] = {0, 0};
  ChessType *type = point.type();
  
  // count[color][length][LorD]
  // color: 0 for BLACK, 1 for WHITE
  // length: means the length of the type, should be 0~5.
  // LorD: 0 for LIVE, 1 for DEAD
  // e.g count[1][4][0] means the number of white dead fours
  int count[2][6][2] = {0};
  bool forbidden = false, win = false;

  for (int selfColor = BLACK, opponentColor = WHITE, i = 0; i < 2;
       selfColor = WHITE, opponentColor = BLACK, ++i) {
    for (int d = 0; d < 4; ++d) {
      if (selfColor == BLACK) {
        if (type[d].length(selfColor) == -1) {
          forbidden = true;
          continue;
        } else if (type[d].length(selfColor) == 5) {
          win = true;
        }
      }
      // count the types in 4 directions
      ++(count[selfColor]
              [type[d].length(selfColor)]
              [type[d].life(selfColor)]);

      // add score
      score[selfColor] += SCORE[type[d].length(selfColor)]
                               [type[d].life(selfColor)]
                               [type[d].level(selfColor)]
                               [0];
      score[opponentColor] += SCORE[type[d].length(selfColor)]
                                   [type[d].life(selfColor)]
                                   [type[d].level(selfColor)]
                                   [1];
    }
  }

  if (count[BLACK][4][LIVE] + count[BLACK][4][DEAD] >= 2 ||
      count[BLACK][3][LIVE] >= 2) forbidden = true;

  // [0] attack, [1] defense

  // calculate score
  for (int selfColor = BLACK, opponentColor = WHITE, i = 0; i < 2;
       selfColor = WHITE, opponentColor = BLACK, ++i) {
    if (count[selfColor][5][0] > 0 ||
        count[opponentColor][5][0] > 0 ||
        count[selfColor][4][LIVE] > 0) {
      continue;
    } else if (count[selfColor][4][DEAD] >= 2) {
      // self muliy-4
      score[selfColor] += SCORE_DOUBLE4[ATTACK];
    } else if (count[selfColor][4][DEAD] > 0 &&
               count[selfColor][3][LIVE] > 0) {
      // self d4-l3
      score[selfColor] += SCORE_DEAD4LIVE3[ATTACK];
    } else if (count[opponentColor][4][DEAD] >= 2) {
      // opponent muliy-4
      if (selfColor == BLACK)
        score[selfColor] += SCORE_DOUBLE4[DEFENSE];
    } else if (count[opponentColor][4][DEAD] > 0 &&
               count[opponentColor][3][LIVE] > 0) {
      // opponent d4-l3
      score[selfColor] += SCORE_DEAD4LIVE3[DEFENSE];
    } else if (count[selfColor][3][LIVE] >= 2) {
      // self multi-3
      score[selfColor] += SCORE_DOUBLELIVE3[ATTACK];
    } else if (count[opponentColor][3][LIVE] >= 2) {
      // opponent multi-3
      if (selfColor = BLACK)
        score[selfColor] += SCORE_DOUBLELIVE3[DEFENSE];
      else
        score[selfColor] -= SCORE[3][1][0][0];
    }
  }

  if (forbidden && !win)
    score[BLACK] = SCORE_FORBIDDEN;


  point.setAbsScore(score[0], score[1]);
}
