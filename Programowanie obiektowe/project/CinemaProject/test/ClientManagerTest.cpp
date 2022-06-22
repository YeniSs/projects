#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "ClientManager.h"
#include "Client.h"
#include "ClientType.h"
#include "Normal.h"
#include "Student.h"
#include "Senior.h"
#include "ClientException.h"
#include <iostream>
#include <sstream>
#include <string>


struct TestSuiteClientManagerFixture {

    ClientTypePtr student = std::make_shared<Student>();
    ClientTypePtr normal = std::make_shared<Normal>();
    ClientTypePtr senior = std::make_shared<Senior>();
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteClientManagerFixture)

    BOOST_AUTO_TEST_CASE(TestClientManagerConstructor) {
        ClientManagerPtr m = std::make_shared<ClientManager>();
        BOOST_TEST(m != nullptr);
        BOOST_TEST(m->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestClientManagerAddClient) {
        ClientManagerPtr clientManager(new ClientManager());
        BOOST_TEST_REQUIRE(clientManager->getSize() == 0);
        clientManager->addClient("Wiktor", "Bechcinski", "229840", normal);
        BOOST_TEST(clientManager->getSize() == 1);
        clientManager->addClient("Kamil", "Budzyn", "229850", senior);
        BOOST_TEST(clientManager->getSize() == 2);
    }

    BOOST_AUTO_TEST_CASE(TestClientManagerAddClientExceptions) {
        ClientManagerPtr clientManager(new ClientManager());
        BOOST_TEST_REQUIRE(clientManager->getSize() == 0);
        BOOST_CHECK_THROW(clientManager->addClient("", "Bechcinski", "229840", student), ClientException);
        BOOST_CHECK_THROW(clientManager->addClient("Wiktor", "", "229840", student), ClientException);
        BOOST_CHECK_THROW(clientManager->addClient("Wiktor", "Bechcinski", "", student), ClientException);
        BOOST_CHECK_THROW(clientManager->addClient("Wiktor", "Bechcinski", "229840", nullptr), ClientException);
        BOOST_TEST(clientManager->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestClientManagerDeleteClient) {
        ClientManagerPtr clientManager(new ClientManager());
        BOOST_TEST_REQUIRE(clientManager->getSize() == 0);
        clientManager->addClient("Wiktor", "Bechcinski", "229840", normal);
        BOOST_TEST(clientManager->getSize() == 1);
        clientManager->addClient("Kamil", "Budzyn", "229850", senior);
        BOOST_TEST(clientManager->getSize() == 2);
        clientManager->deleteClient(clientManager->getClient("229850"));
        BOOST_TEST(clientManager->getSize() == 1);
        clientManager->deleteClient(clientManager->getClient("229840"));
        BOOST_TEST(clientManager->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestClientManagerGetClient) {
        ClientManagerPtr clientManager(new ClientManager());
        BOOST_TEST_REQUIRE(clientManager->getSize() == 0);
        clientManager->addClient("Wiktor", "Bechcinski", "229850", student);
        BOOST_TEST_REQUIRE(clientManager->getSize() == 1);
        BOOST_TEST(clientManager->getClient("229850")->getPersonalID() == "229850");
    }

BOOST_AUTO_TEST_SUITE_END()