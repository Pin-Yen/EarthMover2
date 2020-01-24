#include "virtualboard.h"


VirtualBoard::VirtualBoard(int dimen) {
    dimen_ = dimen;
    playNumber_ = 0;

    int size = dimen * dimen;

    for (int i = 0; i < dimen*dimen; ++i) {
        points_.push_back(new Point());
    }
}

VirtualBoard::~VirtualBoard() {
    for (Point* point : points_) {
        delete point;
    }
}

VirtualBoard::VirtualBoard(VirtualBoard& source) {
    dimen_ = source.dimen_;
    playNumber_ = source.playNumber_;

    points_.reserve(source.points_.size());
    for (Point* point : source.points_) {
        // TODO: use placement new
        points_.push_back(new Point(*point));
    }
}


int VirtualBoard::getScore(int index) {
    return points_[index]->score(); 
}

int VirtualBoard::getScoreSum() {
    int sum = 0;

    for (Point* point : points_) {
        // Only add the score if it is positive.
        if (point->score() > 0)
            sum += point->score();
    }

  return sum;
}

int VirtualBoard::getHSI() {
    // ? Why random for two point with same score?
    // current max score, current same score amount
  int max = 0, same = 0, index = -1;

  for (int i = 0; i < points_.size(); ++i) {
    if (points_[i]->status() != EMPTY) continue;

    int score = points_[i]->score();

    if (score > max) {
      same = 1;

      max = score;
      index = i;
    } else if (score == max) {
      ++same;
      if ((static_cast<double>(rand()) / RAND_MAX) <= (1. / same)) {
        index = i;
      }
    }
  }

  // return -1 means that there is no useful point(can pass now)
  // Not representative of each point is occupied
  return index;
}

int VirtualBoard::getHSI(bool ignoreIndex[]) {
 // current max score, current same score amount
  int max = 0, index = -1;

  for (int i = 0; i < points_.size(); ++i) {
    if (ignoreIndex[i]) continue;

    int score = points_[i]->score();

    if (score > max) {
      max = score;
      index = i;
    }
  }

  // return -1 means that there is no useful point
  // Not representative of each point is occupied
  return index;
}

VirtualBoard::NeighborIterator::NeighborIterator(VirtualBoard *board, int index, int direction) {
    board_ = board;
    startIndex_ = index;
    currentIndex_ = index;
    direction_ = direction;
}

VirtualBoard::NeighborIterator::NeighborIterator(VirtualBoard *board, VirtualBoard::NeighborIterator& it, int direction) {
  board_ = board;
  startIndex_ = it.currentIndex_;
  currentIndex_ = it.currentIndex_;
  direction_ = direction;
}

Point* VirtualBoard::NeighborIterator::next() {
    int nextIndex;
    int row = currentIndex_ / board_->dimen_;
    int col = currentIndex_ % board_->dimen_;
    
    switch (direction_) {
        case 0: col--; break;
        case 1: row--; col--; break;
        case 2: row--; break;
        case 3: row--; col++; break;
        case 4: col++; break;
        case 5: row++; col++; break;
        case 6: row++; break;
        case 7: row++; col--; break;

        default: assert(0); 
    }

    if (row < 0 || col < 0 || row >= board_->dimen_ || col >= board_->dimen_) {
        return NULL;
    } else{
        currentIndex_ = row * board_->dimen_ + col;
        return board_->points_[currentIndex_];
    }
}

void VirtualBoard::NeighborIterator::resetAndReverse() {
    currentIndex_ = startIndex_;
    direction_ = (direction_ + 4) % 8;
}
