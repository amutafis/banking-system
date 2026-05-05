#include "Customer.h"

Customer::Customer(int id,
                   string firstName,
                   string lastName,
                   string egn,
                   string email,
                   string phone)
    : Person(id, firstName, lastName, egn, email, phone) {
}

string Customer::role() const {
    return "CUSTOMER";
}
