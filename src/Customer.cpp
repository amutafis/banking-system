#include "Customer.h"

namespace banking {

Customer::Customer(int id,
                   std::string firstName,
                   std::string lastName,
                   std::string egn,
                   std::string email,
                   std::string phone)
    : Person(id, firstName, lastName, egn, email, phone) {
}

std::string Customer::role() const {
    return "CUSTOMER";
}

} // namespace banking
