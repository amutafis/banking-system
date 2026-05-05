#include "Admin.h"

namespace banking {

Admin::Admin(int id,
             std::string firstName,
             std::string lastName,
             std::string egn,
             std::string email,
             std::string phone)
    : Person(id, firstName, lastName, egn, email, phone) {
}

std::string Admin::role() const {
    return "ADMIN";
}

} // namespace banking
