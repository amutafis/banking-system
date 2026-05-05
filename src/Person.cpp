#include "Person.h"

#include <iostream>
#include <utility>

Person::Person(int id,
               std::string firstName,
               std::string lastName,
               std::string egn,
               std::string email,
               std::string phone)
    : id(id),
      firstName(std::move(firstName)),
      lastName(std::move(lastName)),
      egn(std::move(egn)),
      email(std::move(email)),
      phone(std::move(phone)) {}

int Person::getId() const { return id; }
const std::string& Person::getFirstName() const { return firstName; }
const std::string& Person::getLastName() const { return lastName; }
const std::string& Person::getEgn() const { return egn; }
const std::string& Person::getEmail() const { return email; }
const std::string& Person::getPhone() const { return phone; }

void Person::setFirstName(const std::string& v) { firstName = v; }
void Person::setLastName(const std::string& v) { lastName = v; }
void Person::setEmail(const std::string& v) { email = v; }
void Person::setPhone(const std::string& v) { phone = v; }

void Person::print() const {
    std::cout << "[" << role() << "] #" << id
              << " " << firstName << " " << lastName
              << " | EGN: " << egn
              << " | email: " << email
              << " | tel: " << phone << "\n";
}
