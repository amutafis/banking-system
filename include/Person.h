#ifndef PERSON_H
#define PERSON_H

#include <string>

namespace banking {

class Person {
protected:
    int id;
    std::string firstName;
    std::string lastName;
    std::string egn;
    std::string email;
    std::string phone;

public:
    Person(int id,
           std::string firstName,
           std::string lastName,
           std::string egn,
           std::string email,
           std::string phone);

    virtual ~Person() {}

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getEgn() const;
    std::string getEmail() const;
    std::string getPhone() const;

    void setFirstName(std::string v);
    void setLastName(std::string v);
    void setEmail(std::string v);
    void setPhone(std::string v);

    // Чисто виртуален -> Person е абстрактен клас.
    virtual std::string role() const = 0;

    // Виртуален -> викането става полиморфно през Person*.
    virtual void print() const;
};

} // namespace banking

#endif
