//
// Created by student on 03.06.2020.
//

#ifndef PROJECT_TICKET_H
#define PROJECT_TICKET_H


#include "typedefs.h"
#include <string>
#include "Seats.h"
#include "Client.h"
#include "Seats.h"
#include "Movie.h"
#include "Ticket.h"
#include "ClientType.h"

using namespace std;


class Ticket {
private:
    const string ticketID;
    const MoviePtr movie;
    SeatsPtr seat;
    ClientPtr client;
public:
    Ticket(string ticketID, ClientPtr client, const MoviePtr &movie, SeatsPtr seat);

    virtual ~Ticket();

    const string &getTicketID() const;

    const MoviePtr &getMovie() const;

    const ClientPtr &getClient() const;

    const SeatsPtr &getSeat() const;

    double getFinalPrice() const;

    string getInfo();

};


#endif //PROJECT_TICKET_H