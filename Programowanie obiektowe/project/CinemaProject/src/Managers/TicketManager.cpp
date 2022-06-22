#include "TicketManager.h"
#include "TicketExceptions.h"
#include "ClientException.h"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
using namespace std;

TicketManager::TicketManager() {

}
TicketManager::~TicketManager() = default;

void TicketManager::addTicket(ClientPtr client, MoviePtr film, SeatsPtr seat) {
    try {
        boost::uuids::random_generator gen;
        boost::uuids::uuid u = gen();
        string ticketID = to_string(u);
        TicketPtr t(new Ticket(ticketID, client, film, seat));
        ticketRepo.addObject(t);
    } catch (exception &e) {
        throw TicketException(e.what());
    }
}
void TicketManager::deleteTicket(TicketPtr ticket) {
    if (ticket == nullptr) throw TicketException("Given ticket doesn't exist");
    archiveRepo.addObject(ticket);
    ticketRepo.removeObject(ticket);
}

int TicketManager::getSize() {
    return ticketRepo.getSize();
}

TicketPtr TicketManager::getTicketByClient(string clientID) {
    TicketPredicate p = [clientID](TicketPtr t) { return clientID == t->getClient()->getPersonalID(); };
    return ticketRepo.find(p);
}