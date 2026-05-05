#include "Admin.h"

Admin::Admin(int id,
             string firstName,
             string lastName,
             string egn,
             string email,
             string phone)
    : Person(id, firstName, lastName, egn, email, phone) {
}

string Admin::role() const {
    return "ADMIN";
}
