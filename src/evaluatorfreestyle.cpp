#include "evaluatorfreestyle.h"

EvaluatorFreeStyle *EvaluatorFreeStyle::singleton = NULL;

EvaluatorFreeStyle* EvaluatorFreeStyle::getInstance() {
  if (EvaluatorFreeStyle::singleton == NULL)
    EvaluatorFreeStyle::singleton = new EvaluatorFreeStyle();
  return EvaluatorFreeStyle::singleton;
}

void EvaluatorFreeStyle::evaluateLocalScore(Point& point) {

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

  for (int selfColor = BLACK, opponentColor = WHITE, i = 0; i < 2;
       selfColor = WHITE, opponentColor = BLACK, ++i) {
    for (int d = 0; d < 4; ++d) {
      // count the types in 4 directions
      ++(count[selfColor]
              [type[d].length(selfColor)]
              [type[d].life(selfColor)]);

      //* add score
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
      score[selfColor] += SCORE_DOUBLELIVE3[DEFENSE];
    }
  }
  point.setAbsScore(score[0], score[1]);

}
