#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    int id;
    string firstName;
    string lastName;
    string egn;
    string email;
    string phone;

public:
    Person(int id,
           string firstName,
           string lastName,
           string egn,
           string email,
           string phone);

    virtual ~Person() {}

    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    string getEgn() const;
    string getEmail() const;
    string getPhone() const;

    void setFirstName(string v);
    void setLastName(string v);
    void setEmail(string v);
    void setPhone(string v);

    // Чисто виртуален -> Person е абстрактен клас.
    virtual string role() const = 0;

    // Виртуален -> викането става полиморфно през Person*.
    virtual void print() const;
};

#endif
