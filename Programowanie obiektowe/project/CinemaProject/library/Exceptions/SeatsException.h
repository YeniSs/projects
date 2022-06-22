#ifndef PROJEKT_SEATSEXCEPTION_H
#define PROJEKT_SEATSEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class SeatsException : public logic_error {
public:
    explicit SeatsException(const string &what_arg) : logic_error(what_arg) {}
};

#endif //PROJEKT_SEATSEXCEPTION_H


