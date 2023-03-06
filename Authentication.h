#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "User.h"
#include "Admin.h"
#include "Load.h"
#include "Save.h"
#include "Person.h"
using namespace std;

class Authentication
{
    string login;
    string password;
    HANDLE hConsole;
    Load* load;
    Save* save;
    vector<Person*> person;
    Person* currentPerson;

    void DeleteVector();

public:
    Authentication();
    ~Authentication();

    void InputLogin();
    void InputPassword();
    void PrintLoginScreen();
    bool CheckingData();
    void LoadingData();
    Person* GetCurrentPerson();
};

