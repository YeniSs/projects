#include "Client.h"
#include "ClientException.h"
#include "ClientType.h"
#include "Normal.h"
#include "Senior.h"
#include "Student.h"
#include <memory>
#include <string>


using namespace std;

Client::Client(std::string firstName, std::string lastName, std::string personalID, ClientTypePtr clientType) try
        : firstName(firstName), lastName(lastName), personalID(personalID), clientType(clientType) {
    if (firstName == "" || lastName == "" || personalID == "" || clientType == nullptr) {
        throw ClientException("You can't pass empty variables");
    }
} catch (std::exception &e) {
    throw ClientException("Can't construct a client");
}

Client::~Client() = default;

std::string Client::getFirstName() {
    return this->firstName;
}

std::string Client::getLastName() {
    return this->lastName;
}

std::string Client::getPersonalID() {
    return this->personalID;
}

std::string Client::getInfo() {
    string output;
    output = "Client " + getFirstName() + " " + getLastName() + " with client ID " + getPersonalID() + ". Ticket type: ";
    if (dynamic_pointer_cast<Senior>(getClientType())) {
        output += "Senior.";
    }
    if (dynamic_pointer_cast<Student>(getClientType())) {
        output += "Student.";
    }
    if (dynamic_pointer_cast<Normal>(getClientType())) {
        output +="Normal.";
    }
    return output;
}

ClientTypePtr Client::getClientType() {
    if (clientType == nullptr) {
        throw ClientException("Client must have a type!");
    }
    return this->clientType;
}