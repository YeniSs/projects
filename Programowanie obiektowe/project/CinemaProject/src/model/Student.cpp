#include "Student.h"


Student::Student() {

}

Student::~Student() = default;

float Student::applyDiscount(float price) {
    return price * 0.5;
}