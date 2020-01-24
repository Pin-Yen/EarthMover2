#include "typetree.h"
#include <iostream>
#include <cassert>

TypeTree::TypeTree() {
}

void TypeTree::init() {
    root_ = new TypeTree::Node();
    setAnalyzeLength();
    plantTree();
    cutSameResultChild(root_);
    std::cerr << "Done initializing TypeTree..." << std::endl;
}

ChessType* TypeTree::cutSameResultChild(TypeTree::Node *node) {
    if (node->leaf_)
        return &(node->type_);

    ChessType *currentType = NULL;
    bool canCut = true;

    for (int i = 0; i < 4; ++i)
        if (node->childNode_[i] != NULL) {
          // Check if the child subtree can be trimmed.
          ChessType* returnType = cutSameResultChild(node->childNode_[i]);

        if (returnType == NULL)
            // if children cannot be cut, then this node also cannot be cut
            canCut = false;
        else if (currentType == NULL)
            currentType = returnType;
        else if (*currentType != *returnType)
            // if different child has different result, cannot cut this node
            canCut = false;
    }

    if (!canCut) return NULL;
      // cut this node, free all children and set this node's type
    node->type_ = ChessType(*currentType);

    node->leaf_ = true;

    currentType = &(node->type_);

    for (int i = 0; i < 4; ++i)
        if (node->childNode_[i] != NULL) {
          delete node->childNode_[i];
          node->childNode_[i] = NULL;
      }

      return currentType;
  }

void TypeTree::plantTree() {
    // create tree seed
    StoneStatus status[analyzeLength_];
    for (int i = 0; i < analyzeLength_; ++i)
        status[i] = EMPTY;

    // grow tree
    dfsGrowTree(root_, status, analyzeLength_ / 2, -1, 0, 0, false, false);
}

void TypeTree::dfsGrowTree(
    Node *node, StoneStatus *status, int location, int move,
    int blackConnect, int whiteConnect, bool blackBlock, bool whiteBlock) {
  // if status == black or white, set block == true*/
  switch (status[location]) {
    case BLACK:
      blackBlock = true; break;
    case WHITE:
      whiteBlock = true;
  }

  if ((blackBlock && whiteBlock) || status[location] == BOUND ||
      location <= 0 || location >= analyzeLength_ - 1) {
    if (move == 1) {
      // reached leaf

      // set type
      SingleType bType = typeAnalyze(status, BLACK, true),
                 wType = typeAnalyze(status, WHITE, true);
      node->type_ = ChessType(bType, wType);

      node->leaf_ = true;

      return;
    } else {
      // set this node to jump node
      node->jump_ = true;

      // jump to middle of the status
      move += 2;
      location = analyzeLength_ / 2;

      // reset block
      blackBlock = false; whiteBlock = false;

      // reset connect
      blackConnect = 0; whiteConnect = 0;
    }
  } else {
    // if status == black or white, increase connect
    switch (status[location]) {
      case BLACK:
        ++blackConnect; break;
      case WHITE:
        ++whiteConnect;
    }
  }

  // move location
  location += move;

  const StoneStatus s[4] = {BLACK, WHITE, EMPTY, BOUND};

  for (int i = 0; i < 4; ++i) {
    // if connect == 4,
    // stop playing same color at this point to prevent appearing five
    if ((i == 0 && blackConnect >= 4) || (i == 1 && whiteConnect >= 4))
      continue;

    node->childNode_[i] = new Node();
    status[location] = s[i];
    dfsGrowTree(node->childNode_[i], status, location, move,
        blackConnect, whiteConnect, blackBlock, whiteBlock);
  }

  // restore current location to EMPTY
  // note: without this line,
  // the classification process should still work fine,
  // but will result in printing out garbage values on EMPTY points
  status[location] = EMPTY;
}

// DEPRECATED
// void TypeTree::init() {
//     setAnalyzeLength();
//     root_ = new Node;
//     plantTree();
//     cutSameResultChild(root_);    
// }

ChessType TypeTree::classify(Point *analyzePoint, VirtualBoard::NeighborIterator& neighborIterator) {
    Node* node = root_;

    Point *currentPoint;

    for (int dir=0; dir < 2; ++dir) {
        currentPoint = neighborIterator.next();
        for (int i=0; i < analyzeLength_ /2; ++i) {
            // Enter the child node acording to the status of current point.
            if (currentPoint != NULL) {
              node = node->childNode_[currentPoint->status()];
            } else {
              node = node->childNode_[BOUND];
            }

            // if reach leaf, return type
            if (node->leaf_)  
                return ChessType(node->type_);

            // if reach different color, change direction
            if (node->jump_)
                break;
    
            currentPoint = neighborIterator.next();
        }

        // Change direction and reposition iterator to origin position(analyze point).    
        neighborIterator.resetAndReverse();
    }

    assert(0);
}

