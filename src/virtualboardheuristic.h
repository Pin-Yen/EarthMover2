#ifndef VIRTUAL_BOARD_HEURISTIC_H_
#define VIRTUAL_BOARD_HEURISTIC_H_

#include "evaluator.h"
#include "typetree.h"
#include "virtualboard.h"

class VirtualBoardHeuristic : public VirtualBoard {
 public:

    virtual VirtualBoardHeuristic* clone() = 0;
    static VirtualBoardHeuristic* create(int dimen);

    GameStatus play(int index) ;

    void init();
    
    void undo(int index);

 protected:
    
    VirtualBoardHeuristic(int dimen);

    VirtualBoardHeuristic(VirtualBoardHeuristic& source);

    /** Should be implement by subclass to set typetree. */
    virtual void setTypeTree() = 0;

    /**Should be implement by subclass to set evaluator. */
    virtual void setEvaluator() = 0;

    /** Should be set by subclass */
    TypeTree *typeTree_;

    /** shoud be set by subclass */
    Evaluator *evaluator_;

 private:


    void evaluateNeighbors(int index);


};

#endif