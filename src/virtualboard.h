#ifndef VIRTUAL_BOARD_H_
#define VIRTUAL_BOARD_H_

#include <cassert>
#include <cstdlib>
#include <vector>

#include "enum.h"
#include "point.h"

class VirtualBoard {
 public:

    ~VirtualBoard();

    virtual VirtualBoard* clone() = 0;

    /**
     * Plays a chess on the board.
     * Re-evaluates point scores according to the new move.
     * @param index The 1d index to play.
     * @return The game status after the play. 
     */
    virtual GameStatus play(int index) = 0;

    /**
     * return a random valid index.
     * When generating self-play games for dnn training,
     * a few random moves can diversifying the games.
     */ 
    virtual int randomValidIndex() = 0;

    /** TODO: Check if the return value can be removed*/ 
    int pass() {  ++playNumber_; return dimen_*dimen_; }
    
    /**
     * Undo the chess at index 
     * @param index The 1-d index of the chess to be removed. 
     */
    virtual void undo(int index) = 0;

    /** get score of point at index */
    int getScore(int index);

    /** get the sum of every point's score */
    int getScoreSum();

    /**
     * Get the index of the point with the highest score.
     * @return The index of the point with the highest score, or -1 if there are no point
     * with a significant score.
     */
    int getHSI();

    /** 
     * Same as getHSI(), but ignoring some points
     * @param ignoreIndex If ignoreIndex[index] == true, `index` will be ignored
     * from HSI.
     */
    int getHSI(bool ignoreIndex[]);

    /** 
     * @return 0 for black's turn, 1 for white's turn.
     */
    bool whoTurn() { return (playNumber_ & 1); }

    /** @return The number of points on the board. */
    int length() { return dimen_ * dimen_; }
    
    class NeighborIterator {
       public:

          /**
           * @param board The board to iterate
           * @param index The index of the start point to iterate from.
           * @param direction The direction to iterate. 0~7 starting from the left, clockwise.
           */
          NeighborIterator(VirtualBoard *board, int index, int direction);

          /**
           * @param board The board to iterate
           * @param iter The start point of the new iterator will be the current point of iter
           * @ direction The direction to iterate. 0~7 starting from the left, clockwise. 
           */
          NeighborIterator(VirtualBoard *board, NeighborIterator& iter, int direction);

          /**
           * @return The next point, according to `direction`, NULL if reached bound.
           */
          Point* next();

          /** reset the position of the iterator to its starting point,
           * and reverse the direction for subsequent calls to next().
           */
          void resetAndReverse();
          
       private:
          VirtualBoard *board_;
          int startIndex_, currentIndex_, direction_;

      };

    NeighborIterator createNeighborIterator(int index, int direction) {
        return NeighborIterator(this, index, direction);
    }


    NeighborIterator createNeighborIterator(NeighborIterator& it, int direction) {
      return NeighborIterator(this, it, direction);
    }

    Point* point(int index) { return points_[index]; }
    

 protected:
  VirtualBoard(int dimen);

  VirtualBoard(VirtualBoard& source);
  /** Points of the board.
   * The number of points = dimen * dimen.
   */
  std::vector<Point*> points_;
  int playNumber_;

    /** Dimension (length, width) of the board */
    int dimen_;
 private:

};

#endif