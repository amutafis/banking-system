#pragma once

#include "Person.h"

class Admin : public Person {
public:
    Admin(int id,
          std::string firstName,
          std::string lastName,
          std::string egn,
          std::string email,
          std::string phone);

    std::string role() const override;
};
