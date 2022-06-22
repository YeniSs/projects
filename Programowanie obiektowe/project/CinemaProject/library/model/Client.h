#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

#include <iostream>
#include "typedefs.h"
#include <string>

using namespace std;

class ClientType;

class Client {
    string firstName;
    string lastName;
    string personalID;
    ClientTypePtr clientType;
public:
    Client(string firstName, string lastName, string personalID, ClientTypePtr clientType);

    virtual ~Client();

    string getFirstName();

    string getLastName();

    string getPersonalID();

    string getInfo();

    ClientTypePtr getClientType();
};


#endif //PROJECT_CLIENT_H