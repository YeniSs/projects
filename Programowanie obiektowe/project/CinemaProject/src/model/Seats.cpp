#include "Seats.h"
#include "SeatsException.h"
#include <string>

using namespace std;


Seats::Seats(int row, int column)
try: row(row), column(column){

    if ((row < 0 || row > 30) || (column < 0 || column > 30)) {
        throw SeatsException("Row or column out of range.");
    }
} catch (exception &e) {
    throw SeatsException(e.what());
}

Seats::~Seats() = default;

int Seats::getRow() const {
    return row;
}

int Seats::getColumn() const {
    return column;
}

string Seats::getSeatID() const {
    string output;
    output = "R" + to_string(getRow()) + "C" +to_string(getColumn());
    return output;
}

string Seats::getInfo() const {
    string output;
    output = "Seat's row: " + to_string(getRow()) + ", column: " + to_string(getColumn());
    return output;
}