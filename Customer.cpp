#include "Customer.h"

using namespace std;

bool Customer::follow(Person* p){
    following.push_back(p);
}

