#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

class Customer : public Person {
public:
    Customer(int id,
             string firstName,
             string lastName,
             string egn,
             string email,
             string phone);

    string role() const override;
};

#endif
