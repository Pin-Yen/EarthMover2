#ifndef VIRTUAL_BOARD_HEURISTIC_H_
#define VIRTUAL_BOARD_HEURISTIC_H_

#include "evaluator.h"
#include "typetree.h"
#include "virtualboard.h"

class VirtualBoardHeuristic : public VirtualBoard {
 public:

    VirtualBoardHeuristic* clone() final;
    static VirtualBoardHeuristic* create(int dimen);

    GameStatus play(int index) ;

    void init();
    
    void undo(int index);

 protected:
    VirtualBoardHeuristic(int dimen);

    TypeTree *typeTree_;
    Evaluator *evaluator_;

 private:

    VirtualBoardHeuristic(VirtualBoardHeuristic& source);

    void evaluateNeighbors(int index);


};

#endif