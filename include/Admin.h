#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

class Admin : public Person {
public:
    Admin(int id,
          string firstName,
          string lastName,
          string egn,
          string email,
          string phone);

    string role() const override;
};

#endif
