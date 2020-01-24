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

    // get who turn, black = 0, white = 1
    bool whoTurn() { return (playNumber_ & 1); }
    
    class NeighborIterator {
       public:
          NeighborIterator(VirtualBoard *board, int index, int direction);
          NeighborIterator(VirtualBoard *board, NeighborIterator& iter, int direction);
          Point* next();
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