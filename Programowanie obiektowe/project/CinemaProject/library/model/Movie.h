#ifndef PROJECT_MOVIE_H
#define PROJECT_MOVIE_H

#include <iostream>
#include <boost/date_time.hpp>
#include <string>

using namespace std;

namespace pt = boost::posix_time;

class Movie {
    string title;
    pt::ptime startTime = pt::not_a_date_time;
    pt::ptime endTime = pt::not_a_date_time;
    string genre;
    float basePrice;
public:
    Movie(const string& title, pt::ptime startTime, pt::ptime endTime, string genre, float basePrice);

    virtual ~Movie();

    string getGenre();

    pt::ptime getStartTime();

    pt::ptime getEndTime();

    string getTitle();

    float getBasePrice() const;

    int getMovieTime();

    string getInfo();

};


#endif //PROJECT_MOVIE_H