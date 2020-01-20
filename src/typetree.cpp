#include "typetree.h"

TypeTree::TypeTree() {
}

ChessType* TypeTree::cutSameResultChild(TypeTree::Node *node) {
    if (node->leaf)
        return &(node->type);

    ChessType *currentType = NULL;
    bool canCut = true;

    for (int i = 0; i < 4; ++i)
        if (node->childNode[i] != NULL) {
          // Check if the child subtree can be trimmed.
          ChessType* returnType = cutSameResultChild(node->childNode[i]);

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
    node->type = ChessType(*currentType);

    node->leaf = true;

    currentType = &(node->type);

    for (int i = 0; i < 4; ++i)
        if (node->childNode[i] != NULL) {
          delete node->childNode[i];
          node->childNode[i] = NULL;
      }

      return currentType;
  }

void TypeTree::plantTree() {
    // create tree seed
    StoneStatus status[analyzeLength];
    for (int i = 0; i < analyzeLength; ++i)
        status[i] = EMPTY;

    // grow tree
    dfsGrowTree(root, status, analyzeLength / 2, -1, 0, 0, false, false);
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
      location <= 0 || location >= analyzeLength - 1) {
    if (move == 1) {
      // reached leaf

      // set type
      SingleType bType = typeAnalyze(status, BLACK, true),
                 wType = typeAnalyze(status, WHITE, true);
      node->type = ChessType(bType, wType);

      node->leaf = true;

      return;
    } else {
      // set this node to jump node
      node->jump = true;

      // jump to middle of the status
      move += 2;
      location = analyzeLength / 2;

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

    node->childNode[i] = new Node();
    status[location] = s[i];
    dfsGrowTree(node->childNode[i], status, location, move,
        blackConnect, whiteConnect, blackBlock, whiteBlock);
  }

  // restore current location to EMPTY
  // note: without this line,
  // the classification process should still work fine,
  // but will result in printing out garbage values on EMPTY points
  status[location] = EMPTY;
}

void TypeTree::init() {
    setAnalyzeLength();
    root = new Node;
    plantTree();
    cutSameResultChild(root);    
}

ChessType TypeTree::classify(Point *analyzePoint, NeighborAccessor* neighborAccessor) {
    Node* node = root;

    // Current point is initialized to the backward of analyzePoint
    Point *currentPoint = neighborAccessor->backward(analyzePoint);

    for (int dir=0; dir < 2; ++dir) {
        for (int i=0; i < analyzeLength/2 && currentPoint != NULL; ++i) {
            // Enter the child node acording to the status of current point.
            node = node->childNode[currentPoint->status()];

            // if reach leaf, return type
            if (node->leaf) 
                return ChessType(node->type);

            // if reach different color, change direction
            if (node->jump)
                break;
    
            if (dir==0)
                currentPoint = neighborAccessor->backward(currentPoint);
            else
                currentPoint = neighborAccessor->forward(currentPoint);
        }

        // Change direction: reset the current point to forward of analyze point.    
        currentPoint = neighborAccessor->forward(analyzePoint);
    }
}

