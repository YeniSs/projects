#ifndef CINEMAPROJECT_MOVIEMEXCEPTION_H
#define CINEMAPROJECT_MOVIEMEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class MovieException : public logic_error {
public:
    explicit MovieException(const string & what_arg) : logic_error(what_arg) {}
};


#endif //CINEMAPROJECT_MOVIEMEXCEPTION_H
