#ifndef PROJECT_SEATSMANAGER_H
#define PROJECT_SEATSMANAGER_H

#include "typedefs.h"
#include "Repository.h"
#include "Seats.h"
#include <string>

using namespace std;


class SeatsManager {
    Repository<SeatsPtr> seatsRepo;
public:
    SeatsManager();

    virtual ~SeatsManager();

    void addSeats(int row, int column);

    void deleteSeats(SeatsPtr c);

    int getSize();

    SeatsPtr getSeats(string seatsID);
};


#endif //PROJECT_SEATSMANAGER_H