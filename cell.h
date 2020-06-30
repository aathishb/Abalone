/* 
 * File:   cell.h
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:39 AM
 */

#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>

#define neighbors 6

class cell{    
    char marble;
    std::vector<cell*> adjacent;
    std::string location;
    
public:
    char getMarble() const;
    void setMarble(const char&);
    cell* getAdjacent(const int&) const;
    void setAdjacent(cell*, const int&);
    std::string getLocation() const;
    void setLocation(const std::string& l);
    cell();
    ~cell();
};

#endif /* CELL_H */