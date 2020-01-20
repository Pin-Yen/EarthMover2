#ifndef POINT_H_
#define POINT_H_

#include "chesstype.h"
#include "stonestatus.h"

class Point {
 public:
  Point() : status_(EMPTY) {}

  Point(const Point& source)
      : status_(source.status_),
        score_(source.score_),
        absScore_{ source.absScore_[0], source.absScore_[1] },
        type_{ source.type_[0], source.type_[1],
               source.type_[2], source.type_[3] } {}

  ~Point() {}

  class HorizontalNeighborAccessor;
  class VerticalNeighborAccessor;
  class DiagonalANeighborAccessor;
  class DiagonalBNeighborAccessor;

  /** 
   * Set the neighor of the point
   * @param which Which neighbor (0~7).
   * @param neighbor The neighboring point.
   */
  void setNeighbor(int which, Point* neighbor) {
    this->neighbor[which] = neighbor;
  }

  void setStatus(StoneStatus status) { status_ = status; }
  StoneStatus status() const { return status_; }
  const StoneStatus* statusRef() { return &status_; }

  int* absScore() { return absScore_; }
  int absScore(bool color) const { return absScore_[color]; }

  int score() const { return score_; }
  void setScore(int score) { score_ = score; }

  void setAbsScore(int black, int white) {
    absScore_[0] = black;
    absScore_[1] = white;
  }

  ChessType& type(int index) { return type_[index]; }
  ChessType* type() { return type_; }

 private:
  // chess type array
  // index: 0→ 1↓ 2↗ 3↘
  ChessType type_[4];

  /** Pointer to neighboring points, indexed clockwise starting from the left*/
  Point* neighbor[8];

  /** point's stone status */
  StoneStatus status_;

  int absScore_[2];
  int score_;
};


class NeighborAccessor {
 public:
    virtual Point* backward(Point *point) = 0;
    virtual Point* forward(Point *point) = 0;
};

class Point::VerticalNeighborAccessor : public NeighborAccessor{
 public:
    Point* backward(Point *point) {
        return point->neighbor[2];
    }

    Point* forward(Point *point) {
        return point->neighbor[6];
    }
};

class Point::HorizontalNeighborAccessor : public NeighborAccessor{
 public:
    Point* backward(Point *point) {
        return point->neighbor[0];
    }

    Point* forward(Point *point) {
        return point->neighbor[4];
    }
};

class Point::DiagonalANeighborAccessor : public NeighborAccessor{
 public:
    Point* backward(Point *point) {
        return point->neighbor[1];
    }

    Point* forward(Point *point) {
        return point->neighbor[5];
    }
};

class Point::DiagonalBNeighborAccessor : public NeighborAccessor{
 public:
    Point* backward(Point *point) {
        return point->neighbor[3];
    }

    Point* forward(Point *point) {
        return point->neighbor[7];
    }
};

#endif 