#include "typetreefreestyle.h"
#include "point.h"
#include "chesstype.h"
#include <string>
#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include "virtualboard.h"

class VirtualBoardTest : public VirtualBoard {
 public:
    VirtualBoardTest(std::string str):VirtualBoard(15) {
        int i = 110;
        for (char c : str) {
            
            switch (c) {
                case 'X':
                    points_[i]->setStatus(BLACK);
                    break;
                case 'O':
                    points_[i]->setStatus(WHITE);
                    break;
                case '-':
                case '*':
                    points_[i]->setStatus(EMPTY);
                    break;
                case '|':
                    points_[i]->setStatus(BOUND);
                    break;
                default:
                    assert(0);
            }
            ++i;
        }
    }

    VirtualBoard* clone() { return NULL; }

    GameStatus play(int index) { return NOTHING; }

    Point* point(int index) {return points_[index]; }
 protected:
    void undo(int index) {};

 

};
// Point* constructPoints(std::string str, int direction) {
//     Point* points[9];

//     for (int i = 0; i < 9; ++i) {
//         points[i] = new Point();
//         switch (str[i]) {
//             case 'X':
//                 points[i]->setStatus(BLACK);
//                 break;
//             case 'O':
//                 points[i]->setStatus(WHITE);
//                 break;
//             case '-':
//             case '*':
//                 points[i]->setStatus(EMPTY);
//                 break;
//             case '|':
//                 points[i]->setStatus(BOUND);
//                 break;
//             default:
//                 assert(0);
//         }
//     }

//     for (int i = 1; i < 9; ++i) {
//         points[i]->setNeighbor(direction, points[i-1]);
//         points[i-1]->setNeighbor(direction+4, points[i]);
//     }

//     return points[4];
// }

int main() {
    TypeTreeFreeStyle *tree = TypeTreeFreeStyle::getInstance();


    const std::vector<std::pair<std::string, ChessType>> tests = {
        // test five
        {"--OO*OO--", ChessType(SingleType(0, 0, 0), SingleType(5, 0, 0))},
        {"|OOO*O-XX", ChessType(SingleType(0, 0, 0), SingleType(5, 0, 0))},
        {"XXXX*OOO-", ChessType(SingleType(5, 0, 0), SingleType(4, 0, 0))},
        {"||XX*XX||", ChessType(SingleType(5, 0, 0), SingleType(0, 0, 0))},
        // test live four
        {"X-OO*O-||", ChessType(SingleType(0, 0, 0), SingleType(4, 1, 0))},
        {"----*XXX-", ChessType(SingleType(4, 1, 0), SingleType(1, 0, 0))},
        // test dead four
        {"XOOO*----", ChessType(SingleType(1, 0, 0), SingleType(4, 0, 0))},
        {"OXX-*XO--", ChessType(SingleType(4, 0, 0), SingleType(0, 0, 0))},
        // test renju forbidden

        // test live 3
        {"--OO*----", ChessType(SingleType(1, 0, 0), SingleType(3, 1, 0))},
        // test dead 3

        // test live 2
        // test dead 2
        {"----*OOX-", ChessType(SingleType(1, 0, 0), SingleType(3, 0, 0))},

        // test live 1
        // test dead 1 

    };
    for (auto test : tests) {

        VirtualBoard *board = new VirtualBoardTest(test.first);
        VirtualBoard::NeighborIterator iter = board->createNeighborIterator(114, 0);
        for (int k = 0; k < 2; ++k) {
            for (int i  = 0; i < 4; ++i)
                std::cerr << (int)(iter.next()->status()) << std::endl;
            iter.resetAndReverse();            
        }

        ChessType result = tree->classify(((VirtualBoardTest*)board)->point(114), iter);
        std::cout << "Black: (length, life, level): " << (int)result.length(0)
              << (int) result.life(0) << (int) result.level(0) << std::endl; 
        std::cout << "White: (length, life, level): " << (int) result.length(1)
              << (int) result.life(1) << (int) result.level(1) << std::endl;
        assert(result == test.second);
    } 
    // for (int dir = 0; dir < 4; ++dir) {

    //     // Point *current = point;
    //     // for (int i = 0; i < 4; ++i)  {
    //     //     std::cout << (int) current->status() << std::endl;
    //     //     current = neighborAccessor[dir]->backward(current);
    //     // }
    //     // current = neighborAccessor[dir]->forward(point);
    //     // for (int i = 0; i < 4; ++i)  {
    //     //     std::cout << (int) current->status() << std::endl;
    //     //     current = neighborAccessor[dir]->forward(current);
    //     // }

    //     ChessType chessType = tree->classify(point, neighborAccessor[dir]);

    //     std::cout << "Black: (length, life, level): " << (int)chessType.length(0)
    //               << (int) chessType.life(0) << (int) chessType.level(0) << std::endl; 
    //     std::cout << "White: (length, life, level): " << (int) chessType.length(1)
    //               << (int) chessType.life(1) << (int) chessType.level(1) << std::endl;
    // }
}