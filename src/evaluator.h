#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include <vector>
#include "point.h"
#include "openingtree.h"

class Evaluator {
 public:

    Evaluator();

    ~Evaluator();
    
    /**
     * Set score of each point, with the global context taken into consideration.
     * Should only be called after local score is evaluated. see evaluateLocalScore()
     * 1. Use opening tree during early stage
     * 2. Set points with insignificant scores (compared to highest score) to 0.
     * @param points The points on the chessboard (flattened into 1d vectory).
     * @param playNo The play number.
     */
    void evaluateGlobalScore(std::vector<Point*>& points, int playNo);

    /**
     * Set score of the given point, only considering the local context.
     * (i.e. The score is calculated based on a "pricing table" for each 
     * chess type.)
     * @param point The point to be evaluated.
     */
    virtual void evaluateLocalScore(Point& point) = 0;


    /**
     * Check whether the player win or loses after the point is played.
     * @param point The point to be checked
     * @param who The player to be checked
     * @return The game status after the player plays on point.
     */
    virtual GameStatus checkWinOrLose(Point& point, int who) = 0;
    
    static const int SCORE_WIN = 10000000;
    static const int SCORE_FORBIDDEN = -100;

 protected:

    /** A pointer to the singleton OpeningTree instance */
    OpeningTree *openingTree_;

 private:
};

#endif // EVALUATOR_H_