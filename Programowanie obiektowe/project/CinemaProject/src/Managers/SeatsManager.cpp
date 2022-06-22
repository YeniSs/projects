#include "SeatsManager.h"
#include "SeatsException.h"

using namespace std;


SeatsManager::SeatsManager() {

}

SeatsManager::~SeatsManager() = default;

void SeatsManager::addSeats(int row, int column){
    try {
        SeatsPtr s(new Seats(row, column));
        if (getSeats(s->getSeatID()))
            throw SeatsException("This seat is already taken!");
        seatsRepo.addObject(s);
    } catch (exception &e) {
        throw SeatsException(e.what());
    }
}

void SeatsManager::deleteSeats(SeatsPtr s) {
    if (s == nullptr) throw SeatsException("This seat doesn't exist");
    seatsRepo.removeObject(s);
}

int SeatsManager::getSize() {
    return seatsRepo.getSize();
}

SeatsPtr SeatsManager::getSeats(string seatsID) {
    SeatsPredicate p = [seatsID](SeatsPtr s) { return seatsID == s->getSeatID(); };
    return seatsRepo.find(p);
}