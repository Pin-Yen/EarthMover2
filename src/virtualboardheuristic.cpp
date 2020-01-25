#include "virtualboardheuristic.h"


VirtualBoardHeuristic::VirtualBoardHeuristic(VirtualBoardHeuristic& source)
  : VirtualBoard(source) {
  typeTree_ = source.typeTree_;
  evaluator_ = source.evaluator_;
}

VirtualBoardHeuristic::VirtualBoardHeuristic(int dimen) : VirtualBoard(dimen) {

}

void VirtualBoardHeuristic::init() {
    // evaluate all points
    int size = points_.size();
    for (int index = 0; index < size; ++index) {
        for (int dir = 0; dir < 4; ++dir) {
            NeighborIterator iter = createNeighborIterator(index, dir);
            points_[index]->setType(typeTree_->classify(points_[index], iter), dir);
        }
        evaluator_->evaluateLocalScore(*(points_[index]));
    }

    evaluator_->evaluateGlobalScore(points_, playNumber_);
}


GameStatus VirtualBoardHeuristic::play(int index) {
    GameStatus status = evaluator_->checkWinOrLose(*(points_[index]), playNumber_ & 1);
    if (status != NOTHING) return status;

    ++playNumber_;

    StoneStatus color = ((playNumber_ & 1) ? BLACK : WHITE);

    points_[index]->setStatus(color);

    // set score to -1
    points_[index]->setAbsScore(-1, -1);

    evaluateNeighbors(index);

    evaluator_->evaluateGlobalScore(points_, playNumber_);

    return NOTHING;
}

void VirtualBoardHeuristic::undo(int index) {
  --playNumber_;

  // index == 225 means that previous move is pass
  if (index == dimen_ * dimen_) return;


  // re-evaluate the undo point
  points_[index]->setStatus(EMPTY);
  for (int dir = 0; dir < 4; ++dir) {
    NeighborIterator iter = createNeighborIterator(index, dir);
    points_[index]->setType(typeTree_->classify(points_[index], iter), dir);
  }
  evaluator_->evaluateLocalScore(*(points_[index]));

  evaluateNeighbors(index);

  evaluator_->evaluateGlobalScore(points_, playNumber_);
}


void VirtualBoardHeuristic::evaluateNeighbors(int index) {

    // iterate over neighbors in all 8 directions and evaluate.
    for (int dir = 0; dir < 8; ++dir) {
        NeighborIterator iter = createNeighborIterator(index, dir);

        bool blackBlocked = false, whiteBlocked = false;

        for (int n = 0; n < typeTree_->analyzeLength() / 2 &&! (blackBlocked && whiteBlocked); ++n) {
            Point *neighbor = iter.next();
            if (neighbor == NULL)
                break;
            else if (neighbor->status() == EMPTY) {
                NeighborIterator iterStartFromNeighbor = createNeighborIterator(iter, dir%4);
                neighbor->setType(
                      typeTree_->classify(neighbor, iterStartFromNeighbor),
                      dir % 4
                    );
                evaluator_->evaluateLocalScore(*neighbor);
            } else {
                if (neighbor->status() == BLACK)
                    blackBlocked = true;
                else if (neighbor->status() == WHITE)
                    whiteBlocked = true;           
            }
        }
    }
}
