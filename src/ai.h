#ifndef AI_H_
#define AI_H_

#include <string>
#include <utility>
#include "enum.h"

class AI {
 public:
    virtual WhoWin play(int) = 0;

    virtual std::pair<WhoWin, int> randomPlay() = 0;

    virtual int think() = 0;

    virtual void reset(int level, Rule rule) = 0;

    virtual void resign() = 0;

    virtual void undo() = 0;

    virtual void ponder(bool* continueThinking) = 0;
    
    virtual std::string getTreeJSON() =  0;
};
#endif