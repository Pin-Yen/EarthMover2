#ifndef VIRTUAL_BOARD_HEURISTIC_FREE_STYLE_H_
#define VIRTUAL_BOARD_HEURISTIC_FREE_STYLE_H_

#include "virtualboardheuristic.h"
#include "typetreefreestyle.h"
#include "evaluatorfreestyle.h"

class VirtualBoardHeuristicFreeStyle : public VirtualBoardHeuristic {
  public:
    static VirtualBoardHeuristicFreeStyle* create(int dimension) {
        VirtualBoardHeuristicFreeStyle *board = new VirtualBoardHeuristicFreeStyle(dimension);
        board->typeTree_ = TypeTreeFreeStyle::getInstance();
        board->evaluator_ = EvaluatorFreeStyle::getInstance();
        board->init();
        return board;
    }
  
  private:
    VirtualBoardHeuristicFreeStyle(int dimension): VirtualBoardHeuristic(dimension){};   
};

#endif