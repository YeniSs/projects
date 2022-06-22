#ifndef PROJECT_TICKETMANAGER_H
#define PROJECT_TICKETMANAGER_H

#include "typedefs.h"
#include "Repository.h"
#include "Client.h"
#include "Movie.h"
#include "Seats.h"
#include "Movie.h"
#include "Ticket.h"
#include <string>

using namespace std;


class TicketManager {
    Repository<TicketPtr> ticketRepo;
    Repository<TicketPtr> archiveRepo;
public:
    TicketManager();

    virtual ~TicketManager();

    void addTicket(ClientPtr client, MoviePtr film, SeatsPtr seat);

    void deleteTicket(TicketPtr ticket);

    int getSize();

    TicketPtr getTicketByClient(string clientID);
};


#endif //PROJECT_TICKETMANAGER_H