#include "board.h"
using namespace std;

board::board()
{
    woc = 0; boc = 0;
    int row_length;
    for (int i = 0; i < num_rows; i++)
    {
        if (i < side) {
            row_length = i + side;
        }
        else {
            row_length = (num_rows-i-1) + side;            
        }
        rows.push_back(new cell*[row_length]);
        for (int j = 0; j < row_length - 1; j++)
        {
            if (j == 0) {
                rows[i][j] = new cell();
                rows[i][j+1] = new cell();
            }
            else {
                rows[i][j+1] = new cell();
            }
            rows[i][j]->setAdjacent(rows[i][j+1], 2);
            rows[i][j+1]->setAdjacent(rows[i][j], 5);                
        }
    }
    
    for (int i = 0; i < num_rows-1; i++)
    {
        if (i < side-1)
        {
            for (int j = 0; j < i+side; j++)
            {
                rows[i][j]->setAdjacent(rows[i+1][j], 6);
                rows[i+1][j]->setAdjacent(rows[i][j], 3);
                rows[i][j]->setAdjacent(rows[i+1][j+1], 1);
                rows[i+1][j+1]->setAdjacent(rows[i][j], 4);
            }
        }
        else
        {
            for (int j = 0; j < (num_rows-i-1) + side; j++)
            {
                if (j == 0) {
                    rows[i][j]->setAdjacent(rows[i+1][j], 1);
                    rows[i+1][j]->setAdjacent(rows[i][j], 4);
                }
                
                else if (j == (num_rows-i-1-1) + side) {
                    rows[i][j]->setAdjacent(rows[i+1][j-1], 6);
                    rows[i+1][j-1]->setAdjacent(rows[i][j], 3);
                }
                
                else {
                    rows[i][j]->setAdjacent(rows[i+1][j-1], 6);
                    rows[i+1][j-1]->setAdjacent(rows[i][j], 3);
                    rows[i][j]->setAdjacent(rows[i+1][j], 1);
                    rows[i+1][j]->setAdjacent(rows[i][j], 4);
                }
            }
        }
    }
    
    char c = 'A';
    string s("");
    for (int i = 0; i < num_rows; i++)
    {
        if (i < side)
        {
            for (int j = 0; j < i+side; j++)
            {
                s = "";
                s += c;
                s += to_string(j+1)[0];
                rows[i][j]->setLocation(s);
                cells.emplace(s, rows[i][j]);
            }
        }
        else
        {
            int k = i-(side-1);
            for (int j = 0; j < (num_rows-i-1) + side; j++)
            {
                s = "";
                s += c;
                s += to_string(k+1)[0];
                rows[i][j]->setLocation(s);
                cells.emplace(s, rows[i][j]);
                ++k;
            }
        }
        ++c;
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (i == 0 || i == 1)
        {
            row_length = i+side;
            for (int j = 0; j < row_length; j++)
            {
                rows[i][j]->setMarble('@');
                rows[num_rows-i-1][j]->setMarble('O');
            }
        }
        else
        {
            for (int j = 2; j < 5; j++)
            {
                rows[i][j]->setMarble('@');
                rows[num_rows-i-1][j]->setMarble('O');
            }
        }
    }
}

board::board(const board& b): board() // Constructor delegation - lets constructor call another constructor
{
    int row_length;
    cell** row;
    for (int i = 0; i < num_rows; i++)
    {
        row = b.getRows()[i];
        /* getRows() returns a std::vector<cell**> which represents 9 rows
         * of pointers to the cells of the board, for easy access.
         * */        
        if (i < side) {
            row_length = i + side;
        }
        else {
            row_length = (num_rows-i-1) + side;
        }
        
        for (int j = 0; j < row_length; j++) {
            rows[i][j]->setMarble(row[j]->getMarble());
        }
    }
}

board::~board()
{
    int row_length;
    for (int i = 0; i < num_rows; i++)
    {
        if (i < side) {
            row_length = i + side;
        }
        else {
            row_length = (num_rows-i-1) + side;
        }
        
        for (int j = 0; j < row_length; j++)
        {
            delete rows[i][j];
        }
        
        delete[] rows[i];
        rows[i] = NULL;
    }
    rows.clear();
    rows.shrink_to_fit();
    cells.clear();
}

board::operator string() const
{
    string s("");
    int row_length;
    for (int i = num_rows-1; i >= 0 ; i--)
    {
        if (i < side) {
            row_length = i + side;
        }
        else {
            row_length = (num_rows-i-1) + side;
        }
        s += string(num_rows - row_length, ' ');
        for (int j = 0; j < row_length; j++)
        {
            s += rows[i][j]->getMarble();
            s += ' ';
        }
        s += string(num_rows - row_length, ' ');
        s += '\n';
    }
    return s;
}

string board::traverseHorizontal() const
{
    string s("");
    cell* c = rows[0][0];
    
    for (int i = 0; i < num_rows; i++)
    {
        c = rows[i][0];
        while (c != nullptr)
        {
            s += c->getLocation();
            s += " ";
            c = c->getAdjacent(2);
        }
        s += '\n';
    }
    return s;
}

string board::traverseDiagonal() const
{
    string s("");
    cell* c = rows[0][0];
    
    for (int i = 0; i < side; i++)
    {
        c = rows[0][i];
        while (c != nullptr)
        {
            s += c->getLocation();
            s += ' ';
            c = c->getAdjacent(6);
        }
        s += '\n';
    }
    
    for (int i = 1; i < side; i++)
    {
        c = rows[i][i+side-1];
        while (c != nullptr)
        {
            s += c->getLocation();
            s += ' ';
            c = c->getAdjacent(6);
        }
        s += '\n';
    }
    return s;
}

bool board::isAdjacent(string c1, string c2) {
    cell* current;
    for (int i = 0; i < neighbors; i++)
    {
        current = cells.at(c1)->getAdjacent(i+1);
        if (current != nullptr && current->getLocation() == c2) {
            return true;
        }
    }
    return false;
}

bool board::move(string loc, int num_mar, int mar_dir, int move_dir)
{
    cell* current = cells.at(loc);
    if (current->getMarble() == '+') {
        return false;
    }
    char mar = current->getMarble();
    
    for (int i = 0; i < num_mar; i++)
    {
        if (current->getMarble() != mar) {
            return false;
        }
        current = current->getAdjacent(mar_dir);
    }
    
    current = cells.at(loc);
    cell* move_cell;
    bool on_board = true;
    if (abs(mar_dir - move_dir) == 3)
    {
        move_cell = current->getAdjacent(move_dir);
        if (move_cell->getMarble() == mar) {
            return false;
        }
        else if (move_cell->getMarble() != '+')
        {
            char opponent_mar = move_cell->getMarble();
            int oppCount = 0;
            while (move_cell != nullptr && move_cell->getMarble() != '+')
            {
                if (move_cell->getMarble() == opponent_mar) {
                    ++oppCount;
                    move_cell = move_cell->getAdjacent(move_dir);
                }
                if (move_cell == nullptr) {
                    on_board = false;
                }
            }
            if (num_mar > oppCount)
            {
                for (int i = 0; i < num_mar; i++)
                {
                    current->getAdjacent(move_dir)->setMarble(mar);
                    current->setMarble('+');
                    current = current->getAdjacent(mar_dir);
                }
                
                if (on_board == true)
                {
                    move_cell = cells.at(loc)->getAdjacent(move_dir)
                                             ->getAdjacent(move_dir);
                    move_cell->setMarble(opponent_mar);
                    if (oppCount == 2) {
                        move_cell->getAdjacent(move_dir)->setMarble(opponent_mar);
                    }
                }
                else
                {
                    if (opponent_mar == '@') {
                        ++woc;
                    }
                    else {
                        ++boc;
                    }
                }
                return true;
                
            }
            else {
                return false;
            }
            
        }
        else
        {
            for (int i = 0; i < num_mar; i++)
            {
                current->getAdjacent(move_dir)->setMarble(mar);
                current->setMarble('+');
                current = current->getAdjacent(mar_dir);
            }
            return true;
        }
    }
    else
    {
        for (int i = 0; i < num_mar; i++)
        {
            move_cell = current->getAdjacent(move_dir);
            if (move_cell == nullptr || move_cell->getMarble() != '+') {
                return false;
            }
            current = current->getAdjacent(mar_dir);
        }
        current = cells.at(loc);
        for (int i = 0; i < num_mar; i++)
        {
            current->getAdjacent(move_dir)->setMarble(mar);
            current->setMarble('+');
            current = current->getAdjacent(mar_dir);
        }
        return true;
    }
}

vector<cell**> board::getRows() const
{
    return rows;
}