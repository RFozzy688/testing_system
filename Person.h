#pragma once
#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 30

class Person
{
    string surName;
    string name;
    string patronymic;
    string login;
    string password;
    string status;

public:
    void SetSurName(string surName);
    string GetSurName() const;

    void SetName(string name);
    string GetName() const;

    void SetPatronymic(string patronymic);
    string GetPatronymic() const;

    void SetLogin(string login);
    string GetLogin() const;

    void SetPassword(string password);
    string GetPassword() const;

    void SetStatus(string status);
    string GetStatus() const;

    void PrintInfoPerson();
    void PrintInfoAuthentication();
    virtual ~Person() = 0;
};

