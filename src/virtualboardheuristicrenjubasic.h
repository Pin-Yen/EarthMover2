#ifndef VIRTUAL_BOARD_HEURISTIC_RENJU_BASIC_H_
#define VIRTUAL_BOARD_HEURISTIC_RENJU_BASIC_H_

#include "virtualboardheuristic.h"
#include "typetreerenjubasic.h"
#include "evaluatorrenjubasic.h"

class VirtualBoardHeuristicRenjuBasic : public VirtualBoardHeuristic {
  public:
    static VirtualBoardHeuristicRenjuBasic* create(int dimension) {
        VirtualBoardHeuristicRenjuBasic *board = new VirtualBoardHeuristicRenjuBasic(dimension);
        board->typeTree_ = TypeTreeRenjuBasic::getInstance();
        board->evaluator_ = EvaluatorRenjuBasic::getInstance();
        board->init();
        return board;
    }
  
  private:
    VirtualBoardHeuristicRenjuBasic(int dimension): VirtualBoardHeuristic(dimension){};   
};

#endif