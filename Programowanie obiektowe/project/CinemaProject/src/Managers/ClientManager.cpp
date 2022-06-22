#include "ClientManager.h"
#include "ClientException.h"

using namespace std;


ClientManager::ClientManager() {

}

ClientManager::~ClientManager() = default;

void ClientManager::addClient(string firstName, string lastName, string personalID,
                                   ClientTypePtr clientType) {
    try {
        ClientPtr c(new Client(firstName, lastName, personalID, clientType));
        clientRepo.addObject(c);
    } catch (exception &e) {
        throw ClientException(e.what());
    }
}

void ClientManager::deleteClient(ClientPtr c) {
    clientRepo.removeObject(c);
}

int ClientManager::getSize() {
    return clientRepo.getSize();
}

ClientPtr ClientManager::getClient(string personalID) {
    ClientPredicate p = [personalID](ClientPtr c) { return personalID == c->getPersonalID(); };
    return clientRepo.find(p);
}