#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Movie.h"
#include "MovieException.h"
#include <boost/date_time.hpp>
#include "sstream"


namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestMovieFixture {
    std::string movieTitle = "Cats";
    std::string movieGenre = "Musical";
    float basePrice = 30;

    pt::ptime startDate = pt::ptime(gr::date(2021, 5, 13), pt::hours(9) + pt::minutes(25));
    pt::ptime endDate = pt::ptime(gr::date(2021, 5, 13), pt::hours(10) + pt::minutes(50));
};

BOOST_FIXTURE_TEST_SUITE(TestMovie, TestMovieFixture)

    BOOST_AUTO_TEST_CASE(MovieConstrutorTest) {
        Movie f(movieTitle, startDate, endDate, movieGenre, basePrice);
        BOOST_TEST(f.getTitle() == "Cats");
        BOOST_TEST(f.getGenre() == "Musical");

        std::ostringstream out;
        out << f.getStartTime();
        BOOST_CHECK_EQUAL(out.str(), "2021-May-13 09:25:00");

        out.clear();
        out.str(std::string());
        out << f.getEndTime();
        BOOST_CHECK_EQUAL(out.str(), "2021-May-13 10:50:00");
        BOOST_CHECK_EQUAL(f.getBasePrice(), 30);
    }

    BOOST_AUTO_TEST_CASE(MovieConstrutorExceptionTest) {

        BOOST_CHECK_THROW(Movie f("", startDate, endDate, movieGenre, basePrice), MovieException);
        BOOST_CHECK_THROW(Movie f(movieTitle, pt::not_a_date_time, endDate, movieGenre, basePrice), MovieException);
        BOOST_CHECK_THROW(Movie f(movieTitle, startDate, pt::not_a_date_time, movieGenre, basePrice), MovieException);
        BOOST_CHECK_THROW(Movie f(movieTitle, startDate, endDate, "", basePrice), MovieException);
        BOOST_CHECK_THROW(Movie f(movieTitle, endDate, startDate, movieGenre, basePrice), MovieException);
        BOOST_CHECK_THROW(Movie f(movieTitle, startDate, endDate, movieGenre, -12.0), MovieException);
    }


    BOOST_AUTO_TEST_CASE(MovieGetDurationTest) {

        Movie f(movieTitle, startDate, endDate, movieGenre, basePrice);
        BOOST_TEST(f.getMovieTime() == 85);

        Movie a(movieTitle, startDate, startDate, movieGenre, basePrice);
        BOOST_TEST(a.getMovieTime() == 0);
    }

    BOOST_AUTO_TEST_CASE(MovieGetInfoTest) {

        Movie f(movieTitle, startDate, endDate, movieGenre, basePrice);
        std::stringstream out;
        out << "Movie's title: Cats. Genre: Musical. Duration: 85 minutes. ";
        out << "\nThe movie starts at: 2021-May-13 09:25:00 and ends at: 2021-May-13 10:50:00";
        BOOST_TEST(f.getInfo()==out.str());
    }

BOOST_AUTO_TEST_SUITE_END()
