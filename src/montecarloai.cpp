#include "montecarloai.h"

#include <assert.h>
#include <iostream>

#include "virtualboardheuristicfreestyle.h"
#include "virtualboardheuristicrenjubasic.h"
#include "enum.h"

MonteCarloAI::MonteCarloAI() {
  tree_ = new MonteCarloTree();
}

MonteCarloAI::~MonteCarloAI() {
  delete tree_;
}

int MonteCarloAI::think() {
  switch (level_) {
    case -1:
      tree_->mcts(1000); break;
    case 0:
      tree_->mctsMinParallel(2, 3200, 1600); break;
    case 1:
      tree_->mctsMinParallel(3, 3200, 2400); break;
    case 2:
      tree_->mctsMinParallel(4, 3200, 3200); break;
    default:
      assert(false);
  }

  return tree_->mctsResult();
}

WhoWin MonteCarloAI::play(int index) {
  return tree_->play(index);
}

std::pair<WhoWin, int> MonteCarloAI::randomPlay() {
  return tree_->randomPlay();
}

void MonteCarloAI::reset(int level, Rule rule) {
  VirtualBoard* vb;

  switch (rule) {
    case GOMOKU_FREESTYLE: vb = VirtualBoardHeuristicFreeStyle::create(15); break;
    case GOMOKU_RENJU_BASIC: vb = VirtualBoardHeuristicRenjuBasic::create(15); break;
    default: assert(0);
  }

  tree_->init(vb);
  level_ = level;
}

void MonteCarloAI::ponder(bool* continueThinking) {
  tree_->mctsMaxControlledParallel(4, MAX_BACKGROUND_CYCLE_, continueThinking);
}
