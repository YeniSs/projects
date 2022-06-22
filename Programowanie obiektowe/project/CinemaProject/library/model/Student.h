#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H


#include "ClientType.h"

class Student : public ClientType {
public:
    Student();

    virtual ~Student();

    virtual float applyDiscount(float price) override;
};


#endif //PROJECT_STUDENT_H