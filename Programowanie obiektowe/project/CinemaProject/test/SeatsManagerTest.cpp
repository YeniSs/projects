#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "SeatsManager.h"
#include "Seats.h"
#include "SeatsException.h"


struct TestSuiteSeatsManagerFixture {

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteSeatsManagerFixture)

    BOOST_AUTO_TEST_CASE(TestSeatsManagerConstructor)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        BOOST_TEST(sm != nullptr);
        BOOST_TEST(sm->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerAddSeats)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        BOOST_TEST_REQUIRE(sm->getSize() == 0);
        sm->addSeats(1, 1);
        BOOST_TEST(sm->getSize() == 1);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerAddSeatsException)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        BOOST_TEST_REQUIRE(sm->getSize() == 0);
        sm->addSeats(1, 1);
        BOOST_TEST(sm->getSize() == 1);
        BOOST_CHECK_THROW(sm->addSeats(1, 1), SeatsException);
        BOOST_TEST(sm->getSize() == 1);
        sm->addSeats(2, 2);
        BOOST_TEST(sm->getSize() == 2);
        BOOST_CHECK_THROW(sm->addSeats(-1, 1), SeatsException);
        BOOST_TEST(sm->getSize() == 2);
        BOOST_CHECK_THROW(sm->addSeats(31, 1), SeatsException);
        BOOST_TEST(sm->getSize() == 2);
        BOOST_CHECK_THROW(sm->addSeats(1, -1), SeatsException);
        BOOST_TEST(sm->getSize() == 2);
        BOOST_CHECK_THROW(sm->addSeats(1, 31), SeatsException);
        BOOST_TEST(sm->getSize() == 2);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerDeleteSeats)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        sm->addSeats(1, 1);
        BOOST_TEST(sm->getSize() == 1);

        sm->deleteSeats(sm->getSeats("R1C1"));
        BOOST_TEST(sm->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerDeleteSeatsThrow)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        sm->addSeats(1, 1);
        BOOST_TEST(sm->getSize() == 1);

        sm->deleteSeats(sm->getSeats("R1C1"));
        BOOST_TEST(sm->getSize() == 0);

        BOOST_CHECK_THROW(sm->deleteSeats(sm->getSeats("R1C1")), SeatsException);
        BOOST_TEST(sm->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerGetSize)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        BOOST_TEST(sm->getSize() == 0);
        sm->addSeats(1, 1);
        sm->addSeats(2, 2);
        sm->addSeats(3, 3);
        sm->addSeats(4, 4);
        sm->addSeats(5, 5);
        BOOST_TEST(sm->getSize() == 5);

    }

    BOOST_AUTO_TEST_CASE(TestSeatsManagerGetSeats)
    {
        std::shared_ptr<SeatsManager> sm = std::make_shared<SeatsManager>();
        BOOST_TEST(sm->getSize() == 0);
        sm->addSeats(1, 2);

        SeatsPtr s = sm->getSeats("R1C2");
        BOOST_TEST(s->getSeatID() == "R1C2");
    }

BOOST_AUTO_TEST_SUITE_END()