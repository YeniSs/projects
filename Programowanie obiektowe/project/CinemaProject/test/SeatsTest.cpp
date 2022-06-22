#include <boost/test/unit_test.hpp>
#include "../library/model/Seats.h"
#include "../library/Exceptions/SeatsException.h"


struct TestSuiteSeatsFixture {

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteSeatsFixture)

    BOOST_AUTO_TEST_CASE(TestSeatsConstructor) {
        Seats s(1, 2);

        BOOST_TEST(s.getRow() == 1);
        BOOST_TEST(s.getColumn() == 2);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsConstructorException) {

        BOOST_CHECK_THROW(Seats s(-3, 2), SeatsException);
        BOOST_CHECK_THROW(Seats s(31, 2), SeatsException);
        BOOST_CHECK_THROW(Seats s(3, -2), SeatsException);
        BOOST_CHECK_THROW(Seats s(3, 31), SeatsException);
    }

    BOOST_AUTO_TEST_CASE(TestSeatsgetInfo) {

        Seats s(1, 2);
        BOOST_TEST(s.getInfo() == "Seat's row: 1, column: 2");

        Seats b(23, 11);
        BOOST_TEST(b.getInfo() == "Seat's row: 23, column: 11");
    }

    BOOST_AUTO_TEST_CASE(TestSeatsGetSeatID) {
        Seats s(1, 2);
        BOOST_TEST(s.getSeatID() == "R1C2");

        Seats b(3, 7);
        BOOST_TEST(b.getSeatID() == "R3C7");
    }

BOOST_AUTO_TEST_SUITE_END()