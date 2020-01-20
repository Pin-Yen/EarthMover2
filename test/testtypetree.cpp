#include "typetreefreestyle.h"
#include "point.h"
#include "chesstype.h"
#include <string>
#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <utility>

Point* constructPoints(std::string str, int direction) {
    Point* points[9];

    for (int i = 0; i < 9; ++i) {
        points[i] = new Point();
        switch (str[i]) {
            case 'X':
                points[i]->setStatus(BLACK);
                break;
            case 'O':
                points[i]->setStatus(WHITE);
                break;
            case '-':
            case '*':
                points[i]->setStatus(EMPTY);
                break;
            case '|':
                points[i]->setStatus(BOUND);
                break;
            default:
                assert(0);
        }
    }

    for (int i = 1; i < 9; ++i) {
        points[i]->setNeighbor(direction, points[i-1]);
        points[i-1]->setNeighbor(direction+4, points[i]);
    }

    return points[4];
}

int main() {
    TypeTreeFreeStyle *tree = TypeTreeFreeStyle::getInstance();
    NeighborAccessor* neighborAccessor[4] = {
        new Point::HorizontalNeighborAccessor(),
        new Point::DiagonalANeighborAccessor(),
        new Point::VerticalNeighborAccessor(),
        new Point::DiagonalBNeighborAccessor()
    };

    const std::vector<std::pair<std::string, ChessType>> tests = {
        // test five
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
        // test dead 3

        // test live 2
        // test dead 2

        // test live 1
        // test dead 1 

    };
    for (auto test : tests) {

        for (int dir = 0; dir < 4; ++dir) {
            Point *point = constructPoints(test.first, dir);
            ChessType result = tree->classify(point, neighborAccessor[dir]);
            std::cout << "Black: (length, life, level): " << (int)result.length(0)
                  << (int) result.life(0) << (int) result.level(0) << std::endl; 
            std::cout << "White: (length, life, level): " << (int) result.length(1)
                  << (int) result.life(1) << (int) result.level(1) << std::endl;
            assert(result == test.second);
        }
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