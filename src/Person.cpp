#include "Person.h"
#include <iostream>

namespace banking {

Person::Person(int id,
               std::string firstName,
               std::string lastName,
               std::string egn,
               std::string email,
               std::string phone) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->egn = egn;
    this->email = email;
    this->phone = phone;
}

int Person::getId() const { return id; }
std::string Person::getFirstName() const { return firstName; }
std::string Person::getLastName() const { return lastName; }
std::string Person::getEgn() const { return egn; }
std::string Person::getEmail() const { return email; }
std::string Person::getPhone() const { return phone; }

void Person::setFirstName(std::string v) { firstName = v; }
void Person::setLastName(std::string v) { lastName = v; }
void Person::setEmail(std::string v) { email = v; }
void Person::setPhone(std::string v) { phone = v; }

void Person::print() const {
    std::cout << "[" << role() << "] #" << id
              << " " << firstName << " " << lastName
              << " | EGN: " << egn
              << " | email: " << email
              << " | tel: " << phone << "\n";
}

} // namespace banking
