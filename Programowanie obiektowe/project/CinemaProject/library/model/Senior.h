#ifndef PROJECT_SENIOR_H
#define PROJECT_SENIOR_H


#include "ClientType.h"

class Senior : public ClientType {
public:
    Senior();

    virtual ~Senior();

    virtual float applyDiscount(float price) override;
};


#endif //PROJECT_SENIOR_H