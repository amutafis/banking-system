#pragma once

#include "Person.h"

class Customer : public Person {
public:
    Customer(int id,
             std::string firstName,
             std::string lastName,
             std::string egn,
             std::string email,
             std::string phone);

    std::string role() const override;
};
