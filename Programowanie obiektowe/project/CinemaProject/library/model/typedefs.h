#ifndef PROJECT_TYPEDEFS_H
#define PROJECT_TYPEDEFS_H

#include <memory>
#include <functional>
using namespace std;

class ClientType;
class Client;
class Movie;
class Ticket;
class Seats;
class ClientManager;
class MovieManager;
class TicketManager;
class SeatsManager;

typedef shared_ptr<Client> ClientPtr;
typedef shared_ptr<ClientType> ClientTypePtr;
typedef shared_ptr<Movie> MoviePtr;
typedef shared_ptr<Ticket> TicketPtr;
typedef shared_ptr<Seats> SeatsPtr;

typedef shared_ptr<ClientManager> ClientManagerPtr;
typedef shared_ptr<MovieManager> MovieManagerPtr;
typedef shared_ptr<SeatsManager> SeatsManagerPtr;
typedef shared_ptr<TicketManager> TicketManagerPtr;

typedef function<bool(ClientPtr)> ClientPredicate;
typedef function<bool(MoviePtr)> MoviePredicate;
typedef function<bool(TicketPtr)> TicketPredicate;
typedef function<bool(SeatsPtr)> SeatsPredicate;

#endif //PROJECT_TYPEDEFS_H