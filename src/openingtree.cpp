#include "openingtree.h"

OpeningTree::OpeningTree() {
  init();
}

bool OpeningTree::isInit_ = false;

OpeningTree::Node* OpeningTree::root = new Node();

void OpeningTree::init() {
  if (isInit_) return;
  isInit_ = true;

  std::ifstream file("./src/opening.txt");
  assert(file.good());

  float openingAmout;
  while (file >> openingAmout) {
    char table[5][5];
    for (int r = 0; r < 5; ++r)
      for (int c = 0; c < 5; ++c)
        file >> table[r][c];

    // insert 8 direction
    // rotate four times -> mirror -> rotate four times
    for (int m = 0; m < 2; ++m) {
      for (int r = 0; r < 4; ++r) {
        insert(table);
        rotate(table);
      }
      mirror(table);
    }
  }

  file.close();
}

void OpeningTree::rotate(char table[5][5]) {
  char temp[5][5];
  // rotate 90 degrees clockwise (row -> col, col -> 4 - row)
  for (int r = 0; r < 5; ++r)
    for (int c = 0; c < 5; ++c)
      temp[c][4 - r] = table[r][c];

  for (int r = 0; r < 5; ++r)
    for (int c = 0; c < 5; ++c)
      table[r][c] = temp[r][c];
}

void OpeningTree::mirror(char table[5][5]) {
  char temp[5][5];
  // mirror (row -> col, col -> row)
  for (int r = 0; r < 5; ++r)
    for (int c = 0; c < 5; ++c)
      temp[c][r] = table[r][c];

  for (int r = 0; r < 5; ++r)
    for (int c = 0; c < 5; ++c)
      table[r][c] = temp[r][c];
}

void OpeningTree::insert(char table[5][5]) {
  Node* currentNode = root;

  int oriR = 0, oriC = 0, curR, curC;
  // set the origin in the lower right corner in the table
  // e.g. the origin of the example below is "."
  //   X
  //   C O O C
  //     C X .
  //
  //
  for (int r = 0; r < 5; ++r)
    for (int c = 0; c < 5; ++c)
      if (table[r][c] == 'X' || table[r][c] == 'O') {
        if (r > oriR)
          oriR = r;
        if (c > oriC)
          oriC = c;
      }

  // set current point to origin
  curR = oriR; curC = oriC;

  while (true) {
    // if find a occupied point
    if (table[curR][curC] == 'X' || table[curR][curC] == 'O') {
      int color = table[curR][curC] == 'X' ? 0 : 1;

      // using vector type to record (origin to current point)
      if (currentNode->childNode[oriR - curR][oriC - curC][color] == NULL)
        currentNode->childNode[oriR - curR][oriC - curC][color] = new Node();
      currentNode = currentNode->childNode[oriR - curR][oriC - curC][color];
    }

    // the insert order is from right to left, from bottom to top
    --curC;
    if (curC < 0) {
      if (curR == 0) break;
      --curR;

      curC = 4;
    }
  }

  // record the fifth move
  for (curR = 0; curR < 5; ++curR)
    for (curC = 0; curC < 5; ++curC)
      if (table[curR][curC] == 'P') {
        // using vector type to record
        std::array<int, 2> result = {oriR - curR, oriC - curC};
        // if vector didnot contain this result, add this result into vector
        if (std::find(currentNode->result.begin(),
                      currentNode->result.end(),
                      result) == currentNode->result.end())
          currentNode->result.push_back(result);
      }
}

// classify method please refer to insert
int OpeningTree::classify(std::vector<Point*>& points) {
  Node* currentNode = root;

  int dimension = (int) sqrt(points.size());
  assert(dimension * dimension == points.size());

  int oriR = 0, oriC = 0;
  int left = dimension-1, top = dimension-1;
  // set the origin in the lower right corner, find the left and top
  // "i" is for point index
  for (int r = 0, i = 0; r < dimension; ++r)
    for (int c = 0; c < dimension; ++c, ++i)
      if (points[i]->status() == BLACK || points[i]->status() == WHITE) {
        if (r < top)
          top = r;
        if (c < left)
          left = c;
        if (r > oriR)
          oriR = r;
        if (c > oriC)
          oriC = c;
      }

  if (oriR - top > 4 || oriC - left > 4) return -1;

  int curR = oriR, curC = oriC;

  while (true) {
    int curIndex = curR * dimension + curC;
    if (points[curIndex]->status() == BLACK ||
        points[curIndex]->status() == WHITE) {
      StoneStatus color = points[curIndex]->status();
      if (currentNode->childNode[oriR - curR][oriC - curC][color] == NULL)
        return -1;

      currentNode = currentNode->childNode[oriR - curR][oriC - curC][color];
    }

    --curC;
    if (curC < oriC - 4 || curC < 0) {
      if (curR == oriR - 4 || curR == 0) break;
      --curR;

      curC = oriC;
    }
  }

  int index = -1, count = 1;
  for (std::array<int, 2> result : currentNode->result) {
    int r = oriR - result[0], c = oriC - result[1];
    if (r < 4 || r > 10 || c < 4 || c > 10) continue;

    if ((static_cast<double>(rand()) / RAND_MAX) <= (1. / count)) {
      index =  r * dimension + c;
      ++count;
    }
  }
  return index;
}