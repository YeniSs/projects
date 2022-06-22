#ifndef PROJECT_SEATS_H
#define PROJECT_SEATS_H

#include <iostream>
#include <string>

using namespace std;


class Seats {
    int row;
    int column;
public:
    Seats(int row, int column);

    virtual ~Seats();

    int getRow() const;

    int getColumn() const;

    string getSeatID() const;

    string getInfo() const;
};


#endif //PROJECT_SEATS_H