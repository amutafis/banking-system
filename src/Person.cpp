#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(int id,
               string firstName,
               string lastName,
               string egn,
               string email,
               string phone) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->egn = egn;
    this->email = email;
    this->phone = phone;
}

int Person::getId() const { return id; }
string Person::getFirstName() const { return firstName; }
string Person::getLastName() const { return lastName; }
string Person::getEgn() const { return egn; }
string Person::getEmail() const { return email; }
string Person::getPhone() const { return phone; }

void Person::setFirstName(string v) { firstName = v; }
void Person::setLastName(string v) { lastName = v; }
void Person::setEmail(string v) { email = v; }
void Person::setPhone(string v) { phone = v; }

void Person::print() const {
    cout << "[" << role() << "] #" << id
         << " " << firstName << " " << lastName
         << " | EGN: " << egn
         << " | email: " << email
         << " | tel: " << phone << "\n";
}
