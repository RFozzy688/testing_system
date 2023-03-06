#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include "Person.h"
#include "Admin.h"
#include "User.h"
#include "Registration.h"

class Edit : public Registration
{
    Person* person;
    User* user;
    string str;
    bool isChange = false;
    HANDLE hConsole;

public:
    Edit(Person* person);
    ~Edit() {};

    bool StartEdit();
    int PrintMenuEditUser();
    int PrintMenuEditAdmin();
    void EditSurName();
    void EditName();
    void EditPatronymic();
    void EditLogin();
    void EditPassword();
    void EditAdress();
    void EditPhone();

};

