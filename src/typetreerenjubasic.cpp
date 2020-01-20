#include "typetreerenjubasic.h"
#include <utility>
#include <stddef.h>

void TypeTreeRenjuBasic::setAnalyzeLength() {
    analyzeLength = 11;
}

// initialize singleton instance to NULL
TypeTreeRenjuBasic* TypeTreeRenjuBasic::singleton = NULL;

TypeTreeRenjuBasic* TypeTreeRenjuBasic::getInstance() {
  if (TypeTreeRenjuBasic::singleton == NULL) {
    TypeTreeRenjuBasic::singleton = new TypeTreeRenjuBasic();
    TypeTreeRenjuBasic::singleton->init();
  }

  return TypeTreeRenjuBasic::singleton;
}

SingleType TypeTreeRenjuBasic::typeAnalyze(StoneStatus *status,
                                           StoneStatus color,
                                           bool checkLevel) {
  int connect = 1;
  // check the length of the connection around the analize point
  // under the following, we call this chess group "center group" (CG)
  // for example: --X O*OOX-- ; OOOO* O X
  //                  ^^^^      ^^^^^
  for (int move = -1, start = analyzeLength / 2 - 1;
       move <= 1; move += 2, start += 2) {
    for (int i = 0, checkPoint = start; i < 4; ++i, checkPoint += move) {
      if (status[checkPoint] != color) break;

      ++connect;
    }
  }

  if (connect > 5) {
    // CG's length > 5, return -1
    if (color == BLACK)
      return SingleType(-1, 0, 0);
    else
      return SingleType(5, 0, 0);
  } else if (connect == 5) {
    // CG's length == 5, return 5
    return SingleType(5, 0, 0);
  } else {
    // CG's length < 5

    // play at the analize point
    status[analyzeLength / 2] = color;

    // try to find the left and right bound of CG
    // if it's empty, see this point as new analize point
    // make a new status array and use recursion analize the status
    SingleType lType, rType;
    bool lInit = false, rInit = false;
    int level = 0;

    for (int move = -1, start = analyzeLength / 2 - 1;
         move <= 1; move += 2, start += 2) {
      for (int count = 0, checkPoint = start;
           count < 4; ++count, checkPoint += move) {
        // if reach CG's bound
        if (status[checkPoint] != color) {
          SingleType type;
          bool blocked = false;

          // if the bound is an empty point
          if (status[checkPoint] == EMPTY) {
            // make a new status array
            StoneStatus newStatus[analyzeLength];

            // transform from origin status
            for (int i = 0; i < analyzeLength; ++i) {
              int transformation_index = i - (analyzeLength / 2 - checkPoint);

              if (transformation_index < 0 ||
                  transformation_index >= analyzeLength)
                  // if out of bound, set it to Bound
                newStatus[i] = BOUND;
              else
                newStatus[i] = status[transformation_index];
            }

            // recursion analize
            type = typeAnalyze(newStatus, color, false);
          } else {
            // if the board of CG is not empty, it means blocked
            blocked = true;
            type = SingleType(0, 0, 0);
          }

          if (move == -1) {
            // left type result
            if (!lInit) {
              lInit = true;
              lType = type;
              if (!checkLevel || blocked) break;
              if (!lType.life() || lType.length() > 3) break;
            } else {
              if (lType == type) {
                ++level;
              } else {
                break;
              }
            }
          } else {
            // right type result
            if (!rInit) {
              rInit = true;
              rType = type;
              if (!checkLevel || blocked) break;
              if (!rType.life() || rType.length() > 3) break;
              if (lType == rType) {
                ++level;
              } else if (lType < rType) {
                level = 0;
              } else {
                break;
              }
            } else {
              if ((rType == type) && (rType >= lType)) {
                ++level;
              } else {
                break;
              }
            }
          }
        }
      }
    }

    // restore the analize point to empty
    status[analyzeLength / 2] = EMPTY;

    // keep lType > rType
    if (lType < rType)
      std::swap(lType, rType);

    if (lType.length() == 5 && rType.length() == 5) {
      // if left and right will both produce 5 after play at analize point
      if (connect == 4)
        // if connect == 4, it is a life four type
        return SingleType(4, 1, 0);
      else
        // it is a forbidden (X X*X X)
        return SingleType(-1, 0, 0);
    } else if (lType.length() == 5) {
      // if there is only one side produces 5 after play at analize point,
      // it is a dead four type
      return SingleType(4, 0, 0);
    } else if (lType.length() <= 0) {
      // if the longer size produces 0
      // or forbidden point after play at analize point,
      // it is a useless point
      return SingleType(0, 0, 0);
    } else {
      // if left length < 4, return left length - 1
      // (current recursion's result = lower recursion's result - 1)
      if (checkLevel) {
        if (!lType.life() || lType.length() > 3) {
          return SingleType(lType.length() - 1, lType.life(), 0);
        } else {
          return SingleType(lType.length() - 1, lType.life(),
                           level - (3 - (lType.length() - 1)));
        }
      } else {
        return SingleType(lType.length() - 1, lType.life(), 0);
      }
    }
  }
}
