#pragma once
#include "Person.h"

class User : public Person
{
    string phone;
    string adress;
    string pathStat;

public:
    User();
    ~User();

    void SetPhone(string phone);
    string GetPhone() const;

    void SetAdress(string adress);
    string GetAdress();

    void SetPathStat(string pathStat);
    string GetPathStat();

    void PrintUserInfo();
};

