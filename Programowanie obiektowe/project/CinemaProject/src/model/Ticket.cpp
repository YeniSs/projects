#include "Ticket.h"
#include "TicketExceptions.h"
#include <string>

using namespace std;

Ticket::Ticket(string ticketID, ClientPtr client, const MoviePtr &movie, SeatsPtr seat)
try: ticketID(ticketID), client(client), movie(movie), seat(seat) {
    if ((client == nullptr) || (movie == nullptr) || (seat == nullptr)) {
        throw TicketException("You cannot pass empty variables");
    }
} catch (std::exception &e) {
    throw TicketException("Cannot construct a movie");
}

Ticket::~Ticket() = default;

const string &Ticket::getTicketID() const {
    return ticketID;
}

const MoviePtr &Ticket::getMovie() const {
    return movie;
}

double Ticket::getFinalPrice() const {
    return client->getClientType()->applyDiscount(movie->getBasePrice());
}
string Ticket::getInfo() {
    string output;
    double tmpFinalPrice = getFinalPrice();
    output = "Ticket's informations: Ticket's ID: " + getTicketID() + "\n" +
              client->getInfo() + "\n" +
              movie->getInfo() + "\n" +
              seat->getInfo() + "\n" +
              "Total price: $" + to_string(tmpFinalPrice).substr(0,5) + "\n";
    return output;
}

const SeatsPtr &Ticket::getSeat() const {
    return seat;
}

const ClientPtr &Ticket::getClient() const {
    return client;
}