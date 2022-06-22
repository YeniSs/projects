#include "Senior.h"


Senior::Senior() {

}

Senior::~Senior() = default;

float Senior::applyDiscount(float price) {
    return price * 0.7;
}