#ifndef CINEMAPROJECT_CLIENTEXCEPTION_H
#define CINEMAPROJECT_CLIENTEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class ClientException : public logic_error {
public:
    explicit ClientException(const string &what_arg) : logic_error(what_arg) {}
};


#endif //CINEMAPROJECT_CLIENTEXCEPTION_H


