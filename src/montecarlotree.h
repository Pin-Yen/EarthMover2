#ifndef MONTE_CARLO_TREE_H_
#define MONTE_CARLO_TREE_H_

#include <string>
#include <utility>

#include "enum.h"
#include "json.hpp"
#include "memorypool.h"
#include "virtualboard.h"

class MonteCarloTree {
 public:
  MonteCarloTree();
  ~MonteCarloTree();

  // Initialize MonteCarloTree.
  void init(VirtualBoard* board);

  // Monty Carlo Tree Search.
  // Keep searching until reach 'cycle'.
  // Return false if the search ends prematurely.
  bool mcts(int cycle);

  // Monty Carlo Tree Search.
  // Stop if the point that count most times > 'minCount',
  // will check it after each batch.
  void mctsMin(int batch, int minCount);

  // Monty Carlo Tree Search.
  // Keep searching until 'thinking' becomes false,
  void mctsControlled(const bool* continueThinking);
  // or reach the 'maxCycle'.
  void mctsMaxControlled(int maxCycle, const bool* thinking);

  // Monty Carlo Tree Search.
  // Line 26's multi-thread version.
  void mctsMinParallel(int threadAmount, int batch, int minCount);
  // Line 32's multi-thread version.
  void mctsMaxControlledParallel(int threadAmount, int maxCycle, const bool* thinking);

  // get the child that has highest playout from current node
  int mctsResult() const;

  // Called when a REAL point is played,
  // updates the current node and return game status.
  WhoWin play(int index);

  // pass
  void pass();

  // undo
  void undo();

  // Returns the whole tree in JSON format
  std::string getTreeJSON();

  // getter
  VirtualBoard* getCurrentBoard() { return currentBoard_; }

 private:
  class Node;

  // MCTS function.
  // Keep select the child node until reach a leaf or a winning node.
  // Return status and selectde node.
  std::pair<SearchStatus, Node*> selection(VirtualBoard* board);

  // MCTS function.
  // Simulate the game and return status.
  SearchStatus simulation(VirtualBoard* board) const;

  // MCTS function
  // Back propagation form leaf to current node.
  void backProp(Node* node, SearchStatus result);

  // Copy all children in 'srcNode' to 'destNode'.
  void copyAllChildren(const Node* srcNode, Node* destNode);

  // Copy tree, new tree's root is the current node of 'source'.
  void copy(const MonteCarloTree* source);

  // Merge all tree into this.
  void mergeTree(MonteCarloTree* tree);

  // Merge all children in 'mergedNode' into 'mergingNode'
  void mergeAllChildren(Node* mergingNode, const Node* mergedNode);

  void minusTree(MonteCarloTree* beMinusTree, const MonteCarloTree* minusTree);

  void minusAllChildren(Node* beMinusNode, const Node* minusNode);

  // returns the part of the tree below 'node' in JSON format
  nlohmann::json getSubTreeJSON(Node *node, bool whoTurn, int threshold);

  Node *root_, *currentNode_;

  VirtualBoard* currentBoard_;

  MemoryPool pool_;
};

#endif  // MONTE_CARLO_TREE_H_
