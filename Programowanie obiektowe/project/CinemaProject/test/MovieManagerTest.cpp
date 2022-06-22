#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include "typedefs.h"
#include "MovieManager.h"
#include "Movie.h"
#include "MovieException.h"
#include "sstream"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

struct TestSuiteMovieManagerFixture {

    std::string movieTitle = "Kedi";
    std::string movieGenre = "Documentary";
    float basePrice = 30;

    pt::ptime startDate = pt::ptime(gr::date(2021, 6, 10), pt::hours(9) + pt::minutes(25));
    pt::ptime endDate = pt::ptime(gr::date(2021, 6, 10), pt::hours(10) + pt::minutes(50));

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepo, TestSuiteMovieManagerFixture)

    BOOST_AUTO_TEST_CASE(TestMovieManagerConstructor) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST(m != nullptr);
        BOOST_TEST(m->getSize() == 0);
        BOOST_TEST(m->getMovies().empty());
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerAddClient) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        BOOST_TEST(m->getSize() == 1);
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerAddClientExceptions) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        BOOST_CHECK_THROW(m->addMovie("", startDate, endDate, movieGenre, basePrice), MovieException);
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        BOOST_CHECK_THROW(m->addMovie(movieTitle, pt::not_a_date_time, endDate, movieGenre, basePrice),
                          MovieException);
        BOOST_CHECK_THROW(m->addMovie(movieTitle, startDate, pt::not_a_date_time, movieGenre, basePrice),
                          MovieException);
        BOOST_CHECK_THROW(m->addMovie(movieTitle, startDate, endDate, "", basePrice), MovieException);
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        BOOST_CHECK_THROW(m->addMovie(movieTitle, endDate, startDate, movieGenre, basePrice), MovieException);
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        BOOST_CHECK_THROW(m->addMovie(movieTitle, startDate, endDate, movieGenre, -5), MovieException);
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        BOOST_TEST_REQUIRE(m->getSize() == 1);
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerDeleteClient) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        BOOST_TEST_REQUIRE(m->getSize() == 1);
        m->deleteMovie(m->getMovieByTitle(movieTitle));
        BOOST_TEST(m->getSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerReportMovie) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        m->addMovie("Cat's Eye", startDate, endDate, "Horror", basePrice);
        BOOST_TEST_REQUIRE(m->getSize() == 2);
        std::ostringstream ss;
        ss << "1. Movie's title: Kedi. Genre: Documentary. Duration: 85 minutes. \n";
        ss << "The movie starts at: 2021-Jun-10 09:25:00 and ends at: 2021-Jun-10 10:50:00\n";
        ss << "2. Movie's title: Cat's Eye. Genre: Horror. Duration: 85 minutes. \n";
        ss << "The movie starts at: 2021-Jun-10 09:25:00 and ends at: 2021-Jun-10 10:50:00\n";
        BOOST_TEST(m->getMovies() == ss.str());
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerGetMovieByTitle) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        m->addMovie("Cat's Eye", startDate, endDate, "Horror", basePrice);
        BOOST_TEST_REQUIRE(m->getSize() == 2);
        BOOST_TEST(m->getMovieByTitle(movieTitle)->getTitle() == movieTitle);
        BOOST_TEST(m->getMovieByTitle("Cat's Eye")->getTitle() == "Cat's Eye");
    }

    BOOST_AUTO_TEST_CASE(TestMovieManagerGetMovieByGenre) {
        MovieManagerPtr m = std::make_shared<MovieManager>();
        BOOST_TEST_REQUIRE(m->getSize() == 0);
        m->addMovie(movieTitle, startDate, endDate, movieGenre, basePrice);
        m->addMovie("Cat's Eye", startDate, endDate, "Horror", basePrice);
        BOOST_TEST_REQUIRE(m->getSize() == 2);
        BOOST_TEST(m->getMovieByGenre(movieGenre)->getGenre() == movieGenre);
        BOOST_TEST(m->getMovieByGenre("Horror")->getGenre() == "Horror");
    }

BOOST_AUTO_TEST_SUITE_END()
