#include "Customer.h"

Customer::Customer(int id,
                   std::string firstName,
                   std::string lastName,
                   std::string egn,
                   std::string email,
                   std::string phone)
    : Person(id,
             std::move(firstName),
             std::move(lastName),
             std::move(egn),
             std::move(email),
             std::move(phone)) {}

std::string Customer::role() const { return "CUSTOMER"; }
