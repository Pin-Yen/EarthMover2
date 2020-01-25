#ifndef POINT_H_
#define POINT_H_

#include "chesstype.h"
#include "enum.h"

class Point {
 public:
  Point() : status_(EMPTY) {}

  /** Copy constructor */
  Point(const Point& source)
      : status_(source.status_),
        score_(source.score_),
        absScore_{ source.absScore_[0], source.absScore_[1] },
        type_{ source.type_[0], source.type_[1],
               source.type_[2], source.type_[3] } {}

  ~Point() {}

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

  void setType(ChessType type, int direction) { type_[direction] = type; }


 private:
  /**
   * The classified chess type in four directions.
   * Indexed as: 0→ 1↓ 2↗ 3↘
   */
  ChessType type_[4];

  /** point's stone status */
  StoneStatus status_;

  /** 
   * The classified local score, 0 for black and 1 for white.
   * See evaluator::classifyLocalScore()
   */
  int absScore_[2];

  /** 
   * The final (globally adjusted) score for the point.
   * See evaluator::evaluateGlobalScore()
   */
  int score_;
};

#endif 