#ifndef PROJECT_NORMAL_H
#define PROJECT_NORMAL_H

#include "ClientType.h"

class Normal : public ClientType {
public:
    Normal();

    virtual ~Normal();

    virtual float applyDiscount(float price) override;
};


#endif //PROJECT_NORMAL_H