#include <iomanip>
#include <iostream>
#include <string>

#include "displayboard.h"

DisplayBoard::DisplayBoard(int dimen) {
  dimen_ = dimen;
  wipe();
}

// prints the current chesssboard
void DisplayBoard::invalidate() const {
  for (int r = 0; r < dimen_ + 2; ++r) {
    for (int c = 0; c < dimen_ + 2; ++c) {
      if (r > 0 && r < dimen_ + 1 &&
          c > 0 && c < dimen_ + 1) {
        printBoard(r, c, point_[r - 1][c - 1]);
      } else {
        printBoard(r, c, 0);
      }
    }
  }
}

void DisplayBoard::getInput(int *row, int *col) const {
  while (true) {
    std::cout << "enter the coordinate of next move (A1 ~ "
              << static_cast<char>('A' + dimen_ - 1)
              << dimen_ << ") : ";
    std::string input;
    std::cin >> input;

    int n = input.length();

    if (n == 2 || n == 3) {
      bool validColumn = false, validRow = false;

      // get column
      *col = input[0];
      if (*col >= 'A' && *col < 'A' + dimen_) {
        *col -= 'A';
        validColumn = true;
      } else if (*col >= 'a' && *col < 'a' + dimen_) {
        *col -= 'a';
        validColumn = true;
      }

      // get row
      bool isNumber = true;
      for (int i = 1; i < n; ++i)
        if (!isdigit(input[i])) {
          isNumber = false; break;
        }

      if (isNumber) {
        *row = std::stoi(input.substr(1, n - 1));

        if (*row >= 1 && *row <= dimen_) {
          (*row)--;
          validRow = true;
        }
      }

      if (validRow && validColumn) break;
    }

    std::cout << "Invalid input\n";
  }
}

// print a part of the board
void DisplayBoard::printBoard(int row, int col, int color) const {
  if (row == 0 || row == dimen_ + 1) {
    // if at the first or the last row, print the coordinate with letter
    std::cout << std::setw(4)
              << ((col == 0 || col == dimen_ + 1) ?
                     ' ' : static_cast<char>(64 + col));
  } else if (col == 0 || col == dimen_ + 1) {
    // if at the first or the last column, print the coordinate with number
    if (col == 0) {
      std::cout << std::setw(4) << row;
    } else {
      std::cout << "   " << row;
    }
  } else {
    std::string s;
    if (col == 1) {
      s = "   ";
    } else if (row == 1 || row == dimen_) {
      s = "═══";
    } else if ((row == 4 && col == 4) ||
            (row == 4 && col == dimen_ - 3) ||
            (row == dimen_ - 3 && col == 4) ||
            (row == dimen_ - 3 && col == dimen_ - 3) ||
            (row == dimen_ / 2 + 1 &&
             col == dimen_ / 2 + 1)) {
      s = "──╼";
    } else if ((row == 4 && col == 5) ||
            (row == 4 && col == dimen_ - 2) ||
            (row == dimen_ - 3 && col == 5) ||
            (row == dimen_ - 3 && col == dimen_ - 2) ||
            (row == dimen_ / 2 + 1 &&
             col == dimen_ / 2 + 2)) {
      s = "╾──";
    } else {
      s = "───";
    }

    if (color == 0) {
      if (row == 1) {
        if (col == 1) {
            s += "╔"; 
        } else if (col == dimen_) {
            s += "╗";
        } else {
            s += "╤";
        }
      } else if (row == dimen_) {
        if (col == 1) {
            s += "╚";
        } else if (col == dimen_) {
            s += "╝";
        } else {
            s += "╧";          
        }
      } else {
        if (col == 1) {
            s += "╟";
        } else if (col == dimen_) {
            s += "╢";
        } else {
          s += (((row == 4 && col == 4) ||
               (row == 4 && col == dimen_ - 3) ||
               (row == dimen_ - 3 && col == 4) ||
               (row == dimen_ - 3 &&
                col == dimen_ - 3) ||
               (row == dimen_ / 2 + 1 &&
                col == dimen_ / 2 + 1))
               ? "╋" : "┼");          
        }
      }
    } else {
      s += (color & 1) ? CHESS_BLACK : CHESS_WHITE;
    }
    std::cout << s;
  }

  // if at the last column, print \n
  if (col == dimen_ + 1) {
    std::string s = "\n    ";

    // if not at the first or last row, print │ between two row
    if (row > 0 && row < dimen_) {
      for (int i = 0; i < dimen_; ++i)
        s += ((i == 0 || i == dimen_ - 1) ? "   ║" : "   │");
    }

    s += "\n";
    std::cout << s;
  }
}

// puts a new chess, if the point is not empty then return false
bool DisplayBoard::play(int row, int col) {
  if (row >= 15 || row < 0 || col >= 15 || col < 0) return false;
  if (point_[row][col] != 0) return false;

  ++playNo_;

  point_[row][col] = playNo_;

  invalidate();

  return true;
}

// clears the whole game
void DisplayBoard::wipe() {
  point_.clear();
  for (int r = 0; r < dimen_; ++r) {
    point_.push_back(std::vector<int>());
    for (int c = 0; c < dimen_; ++c) {
      point_[r].push_back(0);
    }
  }

  playNo_ = 0;

  invalidate();
}

