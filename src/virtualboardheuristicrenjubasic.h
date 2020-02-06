#ifndef VIRTUAL_BOARD_HEURISTIC_RENJU_BASIC_H_
#define VIRTUAL_BOARD_HEURISTIC_RENJU_BASIC_H_

#include "virtualboardheuristic.h"
#include "typetreerenjubasic.h"
#include "evaluatorrenjubasic.h"

class VirtualBoardHeuristicRenjuBasic : public VirtualBoardHeuristic {
  public:
    VirtualBoardHeuristicRenjuBasic* clone() {
        return new VirtualBoardHeuristicRenjuBasic(*this);
    }
    static VirtualBoardHeuristicRenjuBasic* create(int dimension) {
        VirtualBoardHeuristicRenjuBasic *board = new VirtualBoardHeuristicRenjuBasic(dimension);
        board->setTypeTree();
        board->setEvaluator();
        board->init();
        return board;
    }
  
  private:

    void setTypeTree() {
        typeTree_ = TypeTreeRenjuBasic::getInstance();
    }

    void setEvaluator() {
        evaluator_ = EvaluatorRenjuBasic::getInstance();
    }
    VirtualBoardHeuristicRenjuBasic(VirtualBoardHeuristicRenjuBasic& source)
     : VirtualBoardHeuristic(source) {};
    VirtualBoardHeuristicRenjuBasic(int dimension): VirtualBoardHeuristic(dimension){};


};

#endif