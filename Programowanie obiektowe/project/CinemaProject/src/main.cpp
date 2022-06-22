#include <iostream>
#include "Client.h"
#include <memory>
#include <boost/date_time.hpp>
#include "Seats.h"
#include "Movie.h"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "ClientManager.h"
#include "MovieManager.h"
#include "TicketManager.h"
#include "SeatsManager.h"
#include "SeatsException.h"
#include "ClientException.h"
#include "TicketExceptions.h"
#include "MovieException.h"
#include "typedefs.h"
#include "ClientType.h"
#include "Normal.h"
#include "Senior.h"
#include "Student.h"
#include <boost/algorithm/string.hpp>
#include <typeinfo>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
using namespace std;


int main() {

    MovieManagerPtr movieManager(new MovieManager());
    ClientManagerPtr clientManager(new ClientManager());
    TicketManagerPtr ticketManager(new TicketManager());
    SeatsManagerPtr seatsManager(new SeatsManager());

    pt::ptime monday1815 = pt::ptime(gr::date(2021, 6, 29), pt::hours(18) + pt::minutes(15));
    pt::ptime monday2025 = pt::ptime(gr::date(2021, 6, 29), pt::hours(20) + pt::minutes(25));

    pt::ptime monday2115 = pt::ptime(gr::date(2021, 6, 29), pt::hours(21) + pt::minutes(15));
    pt::ptime monday2325 = pt::ptime(gr::date(2021, 6, 29), pt::hours(23) + pt::minutes(25));

    pt::ptime wednesday1830 = pt::ptime(gr::date(2021, 6, 24), pt::hours(18) + pt::minutes(30));
    pt::ptime wednesday2135 = pt::ptime(gr::date(2021, 6, 24), pt::hours(21) + pt::minutes(35));

    pt::ptime thursday1755 = pt::ptime(gr::date(2021, 6, 25), pt::hours(17) + pt::minutes(55));
    pt::ptime thursday2045 = pt::ptime(gr::date(2021, 6, 25), pt::hours(20) + pt::minutes(45));

    pt::ptime friday1620 = pt::ptime(gr::date(2021, 6, 26), pt::hours(16) + pt::minutes(20));
    pt::ptime friday1815 = pt::ptime(gr::date(2021, 6, 26), pt::hours(18) + pt::minutes(15));

    pt::ptime friday2015 = pt::ptime(gr::date(2021, 6, 26), pt::hours(20) + pt::minutes(15));
    pt::ptime friday2215 = pt::ptime(gr::date(2021, 6, 26), pt::hours(22) + pt::minutes(15));

    pt::ptime friday2255 = pt::ptime(gr::date(2021, 6, 26), pt::hours(22) + pt::minutes(55));
    pt::ptime saturday0035 = pt::ptime(gr::date(2021, 6, 27), pt::hours(00) + pt::minutes(35));

    pt::ptime saturday1735 = pt::ptime(gr::date(2021, 6, 27), pt::hours(17) + pt::minutes(35));
    pt::ptime saturday1925 = pt::ptime(gr::date(2021, 6, 27), pt::hours(19) + pt::minutes(25));

    pt::ptime saturday2015 = pt::ptime(gr::date(2021, 6, 27), pt::hours(20) + pt::minutes(15));
    pt::ptime saturday2255 = pt::ptime(gr::date(2021, 6, 27), pt::hours(22) + pt::minutes(55));

    pt::ptime sunday1455 = pt::ptime(gr::date(2021, 6, 28), pt::hours(14) + pt::minutes(55));
    pt::ptime sunday1645 = pt::ptime(gr::date(2021, 6, 28), pt::hours(16) + pt::minutes(45));

    movieManager->addMovie("My Best Friend's Birthday", friday2015, friday2215, "Comedy", 20);
    movieManager->addMovie("Reservoir Dogs", saturday1735, saturday1925, "Crime", 20);
    movieManager->addMovie("Pulp Fiction", thursday1755, thursday2045, "Crime", 20);
    movieManager->addMovie("Four Rooms", friday1620, friday1815, "Comedy", 20);
    movieManager->addMovie("Jackie Brown", wednesday1830, wednesday2135, "Crime", 20);
    movieManager->addMovie("Kill Bill: Vol. 1", monday1815, monday2025, "Action", 20);
    movieManager->addMovie("Kill Bill: Vol. 2", monday2115, monday2325, "Action", 20);
    movieManager->addMovie("Death Proof", saturday2015, saturday2255, "Action", 20);
    movieManager->addMovie("Hostel: Part II", friday2255, saturday0035, "Horror", 20);
    movieManager->addMovie("Inglourious Basterds", sunday1455, sunday1645, "Adventure", 20);

    seatsManager->addSeats(1, 1);
    seatsManager->addSeats(2, 2);
    seatsManager->addSeats(3, 3);
    seatsManager->addSeats(11, 11);
    seatsManager->addSeats(22, 22);
    seatsManager->addSeats(23, 23);

    clientManager->addClient("Wiktor", "Bechcinski", "229840", make_shared<Student>());

    std::string customerFirstName;
    std::string customerLastName;
    std::string customerID;
    std::string customerTypeString;

    cout << "Welcome to our cinema!" << endl;
    cout << "In order to get a ticket please provide us some information." << endl;
    cout << "Enter Your name:" << endl;
    cin >> customerFirstName;
    cout << "Enter Your surname:" << endl;
    cin >> customerLastName;
    cout << "Enter Your personal ID:" << endl;
    cin >> customerID;
    cout << "Enter Your discount type [available options: normal, student, senior]:" << endl;

    std::string strStudent = "student";
    std::string strSenior = "senior";
    std::string strNormal = "normal";


    ClientTypePtr customerType;
    while (true) {
        try {
            cin >> customerTypeString;
            if ((!boost::iequals(customerTypeString, strStudent)) && (!boost::iequals(customerTypeString, strSenior))
                && (!boost::iequals(customerTypeString, strNormal))) {
                throw ClientException("Please try again!");
            }
            if (boost::iequals(customerTypeString, strStudent)) {
                customerType = make_shared<Student>();
                break;
            }
            if (boost::iequals(customerTypeString, strSenior)) {
                customerType = make_shared<Senior>();
                break;
            }
            if (boost::iequals(customerTypeString, strNormal)) {
                customerType = make_shared<Normal>();
                break;
            }
        } catch (std::exception &e) {
            cout << e.what() << endl;
            continue;
        }
        break;
    }


    clientManager->addClient(customerFirstName, customerLastName, customerID, customerType);
    ClientPtr customer = clientManager->getClient(customerID);

    cout << movieManager->getMovies();

    cout << "Enter movie number You'd like to watch:" << endl;

    string movieChoice;
    MoviePtr customerMovie;

    while (true) {
        try {
            cin >> movieChoice;
            if (movieChoice != "1" && movieChoice != "2" && movieChoice != "3" && movieChoice != "4" &&
                movieChoice != "5" && movieChoice != "6" && movieChoice != "7" && movieChoice != "8" &&
                movieChoice != "8" && movieChoice != "9" && movieChoice != "10") {
                throw MovieException("Please try again!");
            }
            if (movieChoice == "1") {
                customerMovie = movieManager->getMovieByTitle("My Best Friend's Birthday");
                break;
            }
            if (movieChoice == "2") {
                customerMovie = movieManager->getMovieByTitle("Reservoir Dogs");
                break;
            }
            if (movieChoice == "3") {
                customerMovie = movieManager->getMovieByTitle("Pulp Fiction");
                break;
            }
            if (movieChoice == "4") {
                customerMovie = movieManager->getMovieByTitle("Four Rooms");
                break;
            }
            if (movieChoice == "5") {
                customerMovie = movieManager->getMovieByTitle("Jackie Brown");
                break;
            }
            if (movieChoice == "6") {
                customerMovie = movieManager->getMovieByTitle("Kill Bill: Vol. 1");
                break;
            }
            if (movieChoice == "7") {
                customerMovie = movieManager->getMovieByTitle("Kill Bill: Vol. 2");
                break;
            }
            if (movieChoice == "8") {
                customerMovie = movieManager->getMovieByTitle("Death Proof");
                break;
            }
            if (movieChoice == "9") {
                customerMovie = movieManager->getMovieByTitle("Hostel: Part II");
                break;
            }
            if (movieChoice == "10") {
                customerMovie = movieManager->getMovieByTitle("Inglourious Basterds");;
                break;
            }
        }
        catch (std::exception &e) {
            cout << e.what() << "Please try again!";
            continue;
        }
        break;
    }

    int column;
    int row;
    cout << "Enter row [1-30], column [1-30]";

    while (true) {
        try {
            cout << endl << "Row: ";
            cin >> row;
            cout << "Column: ";
            cin >> column;
            seatsManager->addSeats(row, column);
        } catch (std::exception &e) {
            cout << e.what() << " Please try again.";
            continue;
        }
        break;
    }

    SeatsPtr customerSeat(new Seats(row, column));

    ticketManager->addTicket(customer, customerMovie, customerSeat);
    cout << "You have successfully bought a ticket." << endl;
    cout << ticketManager->getTicketByClient(customerID)->getInfo();


    return 0;
}
