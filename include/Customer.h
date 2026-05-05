#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

namespace banking {

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

} // namespace banking

#endif
