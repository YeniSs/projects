#ifndef PROJECT_CLIENTTYPE_H
#define PROJECT_CLIENTTYPE_H


class ClientType {
public:
    ClientType();

    virtual ~ClientType();

    virtual float applyDiscount(float price) = 0;
};


#endif //PROJECT_CLIENTTYPE_H