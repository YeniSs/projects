#ifndef PROJECT_MOVIEMANAGER_H
#define PROJECT_MOVIEMANAGER_H

#include "typedefs.h"
#include "Repository.h"
#include "Movie.h"
#include <string>

using namespace std;


class MovieManager {
    Repository<MoviePtr> movieRepo;
public:
    MovieManager();

    virtual ~MovieManager();

    void addMovie(string title, pt::ptime startTime, pt::ptime endTime, string genre, float basePrice);

    void deleteMovie(MoviePtr movie);

    int getSize();

    string getMovies();

    MoviePtr getMovieByTitle(string title);

    MoviePtr getMovieByGenre(string genre);
};


#endif //PROJECT_MOVIEMANAGER_H