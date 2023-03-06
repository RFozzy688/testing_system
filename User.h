#pragma once
#include "Person.h"

class User : public Person
{
    string phone;
    string adress;

public:
    User();
    ~User();

    void SetPhone(string phone);
    string GetPhone() const;

    void SetAdress(string adress);
    string GetAdress();

    void PrintUserInfo();
};

