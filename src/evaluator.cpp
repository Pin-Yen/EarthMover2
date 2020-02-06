#include "evaluator.h"

Evaluator::Evaluator() {
    openingTree_ = new OpeningTree();
}

Evaluator::~Evaluator() {
    delete openingTree_;
}

void Evaluator::evaluateGlobalScore(std::vector<Point*>& points, int playNumber) {
    if (playNumber == 0) {
        // Start of the game, set all score to -1 except the middle point.
        for (Point* point : points)
            point->setScore(-1);

        points[points.size() / 2]->setScore(1);
        return;
    } else  if (playNumber <= 4) {
        // In the early stage of the game, use opening

        int index = openingTree_->classify(points);

        if (index != -1) {
            for (Point* point : points)
                point->setScore(-1);

            points[index]->setScore(1);
            return;
        }
    }

    // If not in the early stage of game, or scenario not found in opening tree,
    // use absloute score

    bool whoTurn = playNumber & 1;

    // find highest score
    int highestScore = -1;
    for (Point* point : points)
        if (point->absScore(whoTurn) > highestScore)
            highestScore = point->absScore(whoTurn);


    // If score of a point is less than 1/8 of the highest score, set it to -1.
    for (Point* point : points) {
        int score = point->absScore(whoTurn);
        if (score * 8 <= highestScore || (playNumber < 10 && score < 140))
            point->setScore(-1);
        else
            point->setScore(score);
    }
}
