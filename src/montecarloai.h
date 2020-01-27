#include "ai.h"
#include "montecarlotree.h"

class MonteCarloAI : public AI {
 public:
    MonteCarloAI();

    ~MonteCarloAI();

    int think();

    WhoWin play(int);

    void reset(int level, Rule rule);

    void resign() {};

    void undo() { tree_->undo(); };

    void ponder(bool* continueThinking);
    
    std::string getTreeJSON() { return tree_->getTreeJSON(); };

 private:
    MonteCarloTree *tree_;

    int level_;

    static const int MAX_BACKGROUND_CYCLE_ = 100000;

};