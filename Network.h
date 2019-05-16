#ifndef NETWORK_H
#define NETWORK_H
#include "Publisher.h"
#include "Customer.h"
#include "Film.h"
#include "Exception.h"

class Network{





private:

    std::vector<Publisher> publishers;
    std::vector<Customer> custumers;
    std::vector<Film> films;
    int money;


};









#endif