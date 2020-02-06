#ifndef EVALUATOR_RENJUBASIC_H_
#define EVALUATOR_RENJUBASIC_H_

#include "evaluator.h"

class EvaluatorRenjuBasic : public Evaluator {
 public:
    // static GameStatus checkWinOrLose(int score) {
    //     if (score >= SCORE_WIN) return WINNING;
    //     if (score == SCORE_FORBIDDEN) return LOSING;
    //     return NOTHING;
    // }
    
    GameStatus checkWinOrLose(Point& point, int who) {
        int score = point.absScore(who);
        if (score >= SCORE_WIN) return WINNING;
        if (score == SCORE_FORBIDDEN) return LOSING;
        return NOTHING;
    }

    void evaluateLocalScore(Point& point);

    static EvaluatorRenjuBasic* getInstance();

 private:

    static EvaluatorRenjuBasic* singleton;

    EvaluatorRenjuBasic(){};

    /** The "pricing table" for each chesstype.
     * [length-of-chesstype][Live(1)-or-dead(0)][level][black(0) or white(1)]
     * @see SingleType
     */
    const int SCORE[6][2][4][2] = {
      {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},               // 0
       {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},              // X
      {{{2, 1}, {0, 0}, {0, 0}, {0, 0}},               // D1
       {{6, 2}, {9, 5}, {15, 12}, {20, 16}}},          // L1
      {{{25, 14}, {0, 0}, {0, 0}, {0, 0}},             // D2
       {{64, 40}, {90, 62}, {110, 75}, {0, 0}}},       // L2
      {{{95, 60}, {0, 0}, {0, 0}, {0, 0}},             // D3
       {{265, 135}, {320, 170}, {0, 0}, {0, 0}}},      // L3
      {{{310, 190}, {0, 0}, {0, 0}, {0, 0}},           // D4
       {{10000, 800}, {0, 0}, {0, 0}, {0, 0}}},        // L4
      {{{SCORE_WIN, 500000}, {0, 0}, {0, 0}, {0, 0}},  // 5
       {{0, 0}, {0, 0}, {0, 0}, {0, 0}}}};             // X

    const int SCORE_DOUBLE4[2] = {9000, 500};
    const int SCORE_DEAD4LIVE3[2] = {2400, 400};
    const int SCORE_DOUBLELIVE3[2] = {320, 160};
};

#endif