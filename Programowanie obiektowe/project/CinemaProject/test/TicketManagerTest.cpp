#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "TicketManager.h"
#include "Ticket.h"
#include "TicketExceptions.h"
#include "Client.h"
#include "ClientException.h"
#include "Movie.h"
#include "MovieException.h"
#include "ClientType.h"
#include "Normal.h"
#include "Senior.h"
#include "Student.h"
#include "Seats.h"
#include "SeatsException.h"


namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteTicketManagerFixture {

    ClientTypePtr clientSenior = std::make_shared<Senior>();
    ClientTypePtr clientNormal = std::make_shared<Normal>();
    ClientTypePtr clientStudent = std::make_shared<Student>();

    ClientPtr klientSenior = std::make_shared<Client>("Jan", "Kowalski", "123456", clientSenior);
    ClientPtr klientNormal = std::make_shared<Client>("Jan", "Kowalski", "123456", clientNormal);
    ClientPtr klientStudent = std::make_shared<Client>("Jan", "Kowalski", "123456", clientStudent);

    const std::string movieTitle = "Cat's Eye";
    const std::string movieGenre = "Horror";
    const float movieBasePrice = 30;

    pt::ptime movieStartDate = pt::ptime(gr::date(2021, 6, 10), pt::hours(9) + pt::minutes(25));
    pt::ptime movieEndDate = pt::ptime(gr::date(2021, 6, 10), pt::hours(10) + pt::minutes(50));
    MoviePtr movie = std::make_shared<Movie>(movieTitle, movieStartDate, movieEndDate, movieGenre, movieBasePrice);

    SeatsPtr seat = std::make_shared<Seats>(1, 1);
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteTicketManagerFixture)

    BOOST_AUTO_TEST_CASE(TestTicketManagerConstructor) {
        TicketManagerPtr tm = std::make_shared<TicketManager>();
        BOOST_TEST(tm != nullptr);
        BOOST_TEST(tm->getSize() == 0);
    }


    BOOST_AUTO_TEST_CASE(TestTicketManagerRegisterTicket) {
        TicketManagerPtr tm = std::make_shared<TicketManager>();
        BOOST_TEST_REQUIRE(tm->getSize() == 0);
        tm->addTicket(klientNormal, movie, seat);
        BOOST_TEST(tm->getTicketByClient("123456")->getClient()->getPersonalID() == "123456");
        BOOST_TEST(tm->getSize() == 1);
    }

    BOOST_AUTO_TEST_CASE(TestTicketManagerRegisterTicketException) {
        TicketManagerPtr tm = std::make_shared<TicketManager>();
        BOOST_TEST_REQUIRE(tm->getSize() == 0);
        tm->addTicket(klientNormal, movie, seat);
        BOOST_TEST(tm->getSize() == 1);
        BOOST_CHECK_THROW(tm->addTicket(nullptr, movie, seat), TicketException);
        BOOST_TEST(tm->getSize() == 1);
        BOOST_CHECK_THROW(tm->addTicket(klientStudent, nullptr, seat), TicketException);
        BOOST_TEST(tm->getSize() == 1);
        BOOST_CHECK_THROW(tm->addTicket(klientSenior, movie, nullptr), TicketException);
        BOOST_TEST(tm->getSize() == 1);

    }

    BOOST_AUTO_TEST_CASE(TestTicketManagerDeleteTicket) {
        TicketManagerPtr tm = std::make_shared<TicketManager>();
        tm->addTicket(klientNormal, movie, seat);
        BOOST_TEST_REQUIRE(tm->getSize() == 1);

        tm->deleteTicket(tm->getTicketByClient("123456"));
        BOOST_TEST(tm->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestTicketManagerDeleteTicketThrow) {
        TicketManagerPtr tm = std::make_shared<TicketManager>();
        tm->addTicket(klientNormal, movie, seat);
        BOOST_TEST_REQUIRE(tm->getSize() == 1);

        BOOST_CHECK_THROW(tm->deleteTicket(nullptr), TicketException);
        BOOST_TEST(tm->getSize() == 1);

        tm->deleteTicket(tm->getTicketByClient("123456"));
        BOOST_TEST(tm->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestTicketManagerGetSize) {
        std::shared_ptr<TicketManager> tm = std::make_shared<TicketManager>();
        BOOST_TEST_REQUIRE(tm->getSize() == 0);
        tm->addTicket(klientNormal, movie, seat);
        tm->addTicket(klientStudent, movie, seat);
        tm->addTicket(klientSenior, movie, seat);
        tm->addTicket(klientNormal, movie, seat);
        tm->addTicket(klientStudent, movie, seat);
        BOOST_TEST(tm->getSize() == 5);
    }


    BOOST_AUTO_TEST_CASE(TestTicketManagerGetTicketByClient) {
        std::shared_ptr<TicketManager> tm = std::make_shared<TicketManager>();
        BOOST_TEST_REQUIRE(tm->getSize() == 0);
        tm->addTicket(klientNormal, movie, seat);
        BOOST_TEST_REQUIRE(tm->getSize() == 1);
        BOOST_TEST(tm->getTicketByClient("123456")->getClient()->getPersonalID() == "123456");

    }

BOOST_AUTO_TEST_SUITE_END()