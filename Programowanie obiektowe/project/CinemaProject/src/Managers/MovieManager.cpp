#include "MovieManager.h"
#include "MovieException.h"

using namespace std;


MovieManager::MovieManager() {

}

MovieManager::~MovieManager() = default;

void MovieManager::addMovie(string title, pt::ptime startTime, pt::ptime endTime, string genre,
                               float basePrice) {
    try {
        MoviePtr f(new Movie(title, startTime, endTime, genre, basePrice));
        movieRepo.addObject(f);
    } catch (exception &e) {
        throw MovieException(e.what());
    }

}

string MovieManager::getMovies() {
    return movieRepo.getObjects();
}

int MovieManager::getSize() {
    return movieRepo.getSize();
}

void MovieManager::deleteMovie(MoviePtr movie) {
    movieRepo.removeObject(movie);
}

MoviePtr MovieManager::getMovieByTitle(string title) {
    MoviePredicate p = [title](MoviePtr f) { return title == f->getTitle(); };
    return movieRepo.find(p);
}

MoviePtr MovieManager::getMovieByGenre(string genre) {
    MoviePredicate p = [genre](MoviePtr f) { return genre == f->getGenre(); };
    return movieRepo.find(p);
}