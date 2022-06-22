#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Client.h"
#include "ClientType.h"
#include "Senior.h"
#include "Normal.h"
#include "Student.h"
#include "Movie.h"
#include "Seats.h"
#include "Ticket.h"
#include "TicketExceptions.h"
#include <boost/date_time.hpp>
#include <memory>
#include <string>


namespace pt = boost::posix_time;
namespace gr = boost::gregorian;


struct TestSuiteMovieFixture {
    ClientTypePtr clientSenior= std::make_shared<Senior>();
    ClientTypePtr clientNormal = std::make_shared<Normal>();
    ClientTypePtr clientStudent = std::make_shared<Student>();

    ClientPtr klientSenior = std::make_shared<Client>("Kamil", "Budzyn", "1234567890", clientSenior);
    ClientPtr klientNormal = std::make_shared<Client>("Kamil", "Budzyn", "1234567890", clientNormal);
    ClientPtr klientStudent = std::make_shared<Client>("Kamil", "Budzyn", "1234567890", clientStudent);

    const std::string movieTitle = "Peppa The Pig";
    const std::string movieGenre = "Action";
    const float movieBasePrice = 30;
    pt::ptime movieStartDate = pt::ptime(gr::date(2021, 5, 13), pt::hours(9) + pt::minutes(25));
    pt::ptime movieEndDate = pt::ptime(gr::date(2021, 5, 13), pt::hours(10) + pt::minutes(50));
    MoviePtr movie = std::make_shared<Movie>(movieTitle, movieStartDate, movieEndDate, movieGenre, movieBasePrice);

    pt::ptime movieStartDateSaturday = pt::ptime(gr::date(2021, 6, 13), pt::hours(9) + pt::minutes(25));
    pt::ptime movieEndDateSaturday = pt::ptime(gr::date(2021, 6, 13), pt::hours(10) + pt::minutes(50));
    MoviePtr movieSaturday = std::make_shared<Movie>(movieTitle, movieStartDateSaturday, movieEndDateSaturday, movieGenre,
                                                  movieBasePrice);

    pt::ptime movieStartDateFriday = pt::ptime(gr::date(2021, 6, 12), pt::hours(9) + pt::minutes(25));
    pt::ptime movieEndDateFriday = pt::ptime(gr::date(2021, 6, 12), pt::hours(10) + pt::minutes(50));
    MoviePtr movieFriday = std::make_shared<Movie>(movieTitle, movieStartDateFriday, movieEndDateFriday, movieGenre,
                                                movieBasePrice);

    pt::ptime movieStartDateSunday = pt::ptime(gr::date(2021, 6, 14), pt::hours(9) + pt::minutes(25));
    pt::ptime movieEndDateSunday = pt::ptime(gr::date(2021, 6, 14), pt::hours(10) + pt::minutes(50));
    MoviePtr movieSunday = std::make_shared<Movie>(movieTitle, movieStartDateSunday, movieEndDateSunday, movieGenre,
                                                movieBasePrice);

    SeatsPtr seat = std::make_shared<Seats>(1, 2);

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteMovieFixture)

    BOOST_AUTO_TEST_CASE(TestTicketConstructor) {
        Ticket t("2137", klientSenior, movie, seat);

        BOOST_TEST(t.getMovie() == movie);
        BOOST_TEST(t.getTicketID() == "2137");
        BOOST_TEST(t.getSeat() == seat);
        BOOST_TEST(t.getClient() == klientSenior);
    }

    BOOST_AUTO_TEST_CASE(TestTicketConstructorExceptions) {

        BOOST_CHECK_THROW(Ticket t("2137", nullptr, movie, seat), TicketException);
        BOOST_CHECK_THROW(Ticket t("2137", klientSenior, nullptr, seat), TicketException);
        BOOST_CHECK_THROW(Ticket t("2137", klientNormal, movie, nullptr), TicketException);
    }

    BOOST_AUTO_TEST_CASE(TestTicketGetFinalPriceNormal) {

        Ticket t("2137", klientNormal, movie, seat);
        BOOST_TEST(t.getFinalPrice() == 30);
    }

    BOOST_AUTO_TEST_CASE(TestTicketGetFinalPriceSenior) {

        Ticket t("2137", klientSenior, movie, seat);
        BOOST_TEST(t.getFinalPrice() == 21);
    }

    BOOST_AUTO_TEST_CASE(TestTicketGetFinalPriceStudent) {

        Ticket t("2137", klientStudent, movie, seat);
        BOOST_TEST(t.getFinalPrice() == 15);
    }

    BOOST_AUTO_TEST_CASE(TestTicketGetInfo) {

        Ticket t("2137", klientSenior, movie, seat);
        string output;
        output= "Ticket's informations: Ticket's ID: 2137\n"
                "Client Kamil Budzyn with client ID 1234567890. Ticket type: Senior.\n"
                "Movie's title: Peppa The Pig. Genre: Action. Duration: 85 minutes. \nThe movie starts at: 2021-May-13 09:25:00 and ends at: 2021-May-13 10:50:00\n"
                "Seat's row: 1, column: 2\n"
                "Total price: $21.00\n";
        BOOST_TEST(output == t.getInfo());
    }


BOOST_AUTO_TEST_SUITE_END()
