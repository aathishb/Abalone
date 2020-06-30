#include "cell.h"
using namespace std;

cell::cell() {
    setMarble('+');
    for (int i = 0; i < neighbors; i++) {
        adjacent.push_back(nullptr);
    }
}

cell::~cell() {
    setMarble('\0');
    adjacent.clear();
    adjacent.shrink_to_fit();
}

char cell::getMarble() const {
    return marble;
}

void cell::setMarble(const char& c) {
    marble = c;
}

cell* cell::getAdjacent(const int& i) const {
    return adjacent[i-1];
}

void cell::setAdjacent(cell* c, const int& i) {
    adjacent[i-1] = c;
}

string cell::getLocation() const {
    return location;
}

void cell::setLocation(const string& l) {
    location = l;
}