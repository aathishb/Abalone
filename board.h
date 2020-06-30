/* 
 * File:   board.h
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:55 AM
 */

#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <map>
#include <sstream>
#include <iostream>
#include <cstdlib>

#define num_rows 9
#define side 5

class board{
    std::vector<cell**> rows;
    std::map<std::string,cell*> cells;
    int woc;//white marbles off the board count.
    int boc;//black marbles off the board count.
public:
    board();
    //create 61 cells on the heap, and connect them.
    board(const board&);
    //copy constructor
    ~board();
    //recycle 61 cells.
    operator std::string() const;
    //cast this object into a string.
    std::string traverseHorizontal() const;
    std::string traverseDiagonal() const;
    bool isAdjacent(std::string, std::string);
    bool move(std::string loc, int, int, int);
    //returns true if move is valid, false otherwise
    std::vector<cell**> getRows() const;
};

#endif /* BOARD_H */