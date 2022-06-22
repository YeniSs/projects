#include <boost/test/unit_test.hpp>
#include "../library/model/Client.h"
#include <iostream>
#include "../library/model/ClientType.h"
#include "../library/model/Normal.h"
#include "../library/model/Senior.h"
#include "../library/model/Student.h"
#include "../library/Exceptions/ClientException.h"

using namespace std;

struct TestSuiteClientFixture {
    ClientTypePtr student = make_shared<Student>();
    ClientTypePtr senior = make_shared<Senior>();
    ClientTypePtr normal = make_shared<Normal>();
};

BOOST_FIXTURE_TEST_SUITE(TestClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ClientConstrutorTest) {

        Client c("Wiktor", "Bechcinski", "229840", student);
        BOOST_TEST(c.getFirstName() == "Wiktor");
        BOOST_TEST(c.getLastName() == "Bechcinski");
        BOOST_TEST(c.getPersonalID() == "229840");
        BOOST_TEST(c.getClientType() == student);

        Client b("Wiktor", "Malysz", "229840", senior);
        BOOST_TEST(b.getFirstName() == "Wiktor");
        BOOST_TEST(b.getLastName() == "Malysz");
        BOOST_TEST(b.getPersonalID() == "229840");
        BOOST_TEST(b.getClientType() == senior);

        Client a("Wiktor", "Bechcinski", "23003", normal);
        BOOST_TEST(a.getFirstName() == "Wiktor");
        BOOST_TEST(a.getLastName() == "Bechcinski");
        BOOST_TEST(a.getPersonalID() == "23003");
        BOOST_TEST(a.getClientType() == normal);
    }

    BOOST_AUTO_TEST_CASE(ClientConstrutorExceptionTest) {

        BOOST_CHECK_THROW(Client c("Wiktor", "Bechcinski", "229840", nullptr), ClientException);
        BOOST_CHECK_THROW(Client c("Wiktor", "Bechcinski", "", student), ClientException);
        BOOST_CHECK_THROW(Client c("Wiktor", "", "229840", student), ClientException);
        BOOST_CHECK_THROW(Client c("", "Bechcinski", "229840", student), ClientException);
    }

    BOOST_AUTO_TEST_CASE(ClientgetInfoTest) {

        ClientPtr d(new Client("Wiktor", "Bechcinski", "229840", normal));
        BOOST_TEST(dynamic_pointer_cast<Normal>(d->getClientType()));
        BOOST_TEST(d->getInfo() == ("Client Wiktor Bechcinski with client ID 229840. Ticket type: Normal."));

        ClientPtr d2(new Client("Kamil", "Budzyn", "229850", senior));
        BOOST_TEST(dynamic_pointer_cast<Senior>(d2->getClientType()));
        BOOST_TEST(d2->getInfo() == ("Client Kamil Budzyn with client ID 229850. Ticket type: Senior."));

        ClientPtr d3(new Client("Wiktor", "Budzyn", "213769", student));
        BOOST_TEST(dynamic_pointer_cast<Student>(d3->getClientType()));
        BOOST_TEST(d3->getInfo() == ("Client Wiktor Budzyn with client ID 213769. Ticket type: Student."));
    }

    BOOST_AUTO_TEST_CASE(ClientTypeDiscountsTest) {
        float starting_price = 100;
        BOOST_TEST(normal->applyDiscount(starting_price) == 100);
        BOOST_TEST(senior->applyDiscount(starting_price) == 70);
        BOOST_TEST(student->applyDiscount(starting_price) == 50);
    }


BOOST_AUTO_TEST_SUITE_END()

