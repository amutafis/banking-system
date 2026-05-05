#pragma once

#include <string>

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

    virtual ~Person() = default;

    int getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getEgn() const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;

    void setFirstName(const std::string& v);
    void setLastName(const std::string& v);
    void setEmail(const std::string& v);
    void setPhone(const std::string& v);

    virtual std::string role() const = 0;
    virtual void print() const;
};
