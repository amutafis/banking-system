#include "Admin.h"

Admin::Admin(int id,
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

std::string Admin::role() const { return "ADMIN"; }
