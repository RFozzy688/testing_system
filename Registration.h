#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "User.h"
#include "Admin.h"
#include "Load.h"
#include "Save.h"
#include "Person.h"
using namespace std;

class Registration
{
    HANDLE hConsole;
    Load* load;
    Save* save;
    vector<Person*> person;

protected:
    void LoadingData();
    void SaveData();
    bool CheckingLogin(string str);
    void InputLogin(char* str, int size);
    bool CheckingPassword(string str);
    void InputPassword(char* str, int size);
    void ClearScreen(COORD pos);
    void DeleteVector();
    void DeepCopy(User* obj);
public:
    Registration();
    ~Registration();
    bool RegistrationUser(User* obj);
    void RegistrationAdmin(Admin* obj);

};

