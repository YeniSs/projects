#ifndef PROJECT_CLIENTMANAGER_H
#define PROJECT_CLIENTMANAGER_H

#include "typedefs.h"
#include "Repository.h"
#include "Client.h"

using namespace std;


class ClientManager {
    Repository<ClientPtr> clientRepo;
public:
    ClientManager();
    
    virtual ~ClientManager();

    void addClient(string firstName, string lastName, string personalID, ClientTypePtr clientType);

    void deleteClient(ClientPtr c);

    int getSize();

    ClientPtr getClient(string personalID);
};


#endif //PROJECT_CLIENTMANAGER_H