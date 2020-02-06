#ifndef OPENINGTREE_H_
#define OPENINGTREE_H_

#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include "point.h"

class OpeningTree {
 public:

  OpeningTree();

  /** initialize opening tree */
  static void init();

  /**
   * Returns the suggested move based on the given board situations.
   * @param points The poins on the board.
   * @return The index of the suggested move. 
   */
  static int classify(std::vector<Point*>& points);

 private:
  struct Node {
    Node() {
      for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c) {
          childNode[r][c][0] = NULL;
          childNode[r][c][1] = NULL;
        }
    }

    std::vector<std::array<int, 2>> result;

    Node *childNode[5][5][2];
  };

  /** rotate "table" 90 degrees clockwise */
  static void rotate(char table[5][5]);

  /**  mirror "table" by swapping table's rows and columns */
  static void mirror(char table[5][5]);

  /** insert "table" to tree */
  static void insert(char table[5][5]);

  static Node* root;

 private:
  static bool isInit_;
};
#endif  // OPENINGTREE_H_
