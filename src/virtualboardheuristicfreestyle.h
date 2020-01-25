#ifndef VIRTUAL_BOARD_HEURISTIC_FREE_STYLE_H_
#define VIRTUAL_BOARD_HEURISTIC_FREE_STYLE_H_

#include "virtualboardheuristic.h"
#include "typetreefreestyle.h"
#include "evaluatorfreestyle.h"

class VirtualBoardHeuristicFreeStyle : public VirtualBoardHeuristic {
  public:
    VirtualBoardHeuristicFreeStyle* clone() {
        return new VirtualBoardHeuristicFreeStyle(*this);
    }
    static VirtualBoardHeuristicFreeStyle* create(int dimension) {
        VirtualBoardHeuristicFreeStyle *board = new VirtualBoardHeuristicFreeStyle(dimension);
        board->setTypeTree();
        board->setEvaluator();
        board->init();
        return board;
    }
  private:
    void setTypeTree() {
        typeTree_ = TypeTreeFreeStyle::getInstance();        
    }

    void setEvaluator() {
        evaluator_ = EvaluatorFreeStyle::getInstance();        
    }

    VirtualBoardHeuristicFreeStyle(int dimension): VirtualBoardHeuristic(dimension){}; 

    VirtualBoardHeuristicFreeStyle(VirtualBoardHeuristicFreeStyle& source)
     : VirtualBoardHeuristic(source) {};  
};

#endif