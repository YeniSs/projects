#include "Movie.h"
#include "MovieException.h"
#include <utility>//#
#include <string>
using namespace std;

Movie::Movie(const string& title, pt::ptime startTime, pt::ptime endTime, string genre, float basePrice)
try: title(title), startTime(startTime), endTime(endTime), genre(genre), basePrice(basePrice) {
    if (basePrice < 0) {
        throw MovieException("Base price is too low");
    }
    if (endTime < startTime || startTime == pt::not_a_date_time || endTime == pt::not_a_date_time) {
        throw MovieException("Bad date");
    }
    if (title.empty() || genre.empty()) {
        throw MovieException("You cannot pass empty variables");
    }
} catch (exception &e) {
    throw MovieException(e.what());
}

Movie::~Movie() = default;

string Movie::getTitle() {
    return this->title;
}

pt::ptime Movie::getStartTime() {
    return this->startTime;
}

pt::ptime Movie::getEndTime() {
    return this->endTime;
}

string Movie::getGenre() {
    return this->genre;
}

float Movie::getBasePrice() const {
    return this->basePrice;
}

int Movie::getMovieTime() {
    pt::time_period period(this->startTime, this->endTime);
    return period.length().hours() * 60 + period.length().minutes();
}

string Movie::getInfo() {
    string output;
    output = "Movie's title: " + getTitle() + ". Genre: " + getGenre() + ". Duration: " + to_string(getMovieTime()) + " minutes. ";
    stringstream stream;
    stream << getStartTime();
    output += "\nThe movie starts at: " + stream.str() + " and ends at: " ;
    stream.str("");
    stream << getEndTime();
    output += stream.str();
    return output;
}