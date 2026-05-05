#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

namespace banking {

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

} // namespace banking

#endif
