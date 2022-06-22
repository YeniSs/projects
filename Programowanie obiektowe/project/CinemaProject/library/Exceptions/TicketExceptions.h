#ifndef CINEMAPROJECT_TICKETEXCEPTIONS_H
#define CINEMAPROJECT_TICKETEXCEPTIONS_H

#include <stdexcept>

using namespace std;

class TicketException : public logic_error {
public:
    explicit TicketException(const string &what_arg) : logic_error(what_arg) {}
};

#endif //CINEMAPROJECT_TICKETEXCEPTIONS_H

