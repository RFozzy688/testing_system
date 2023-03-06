#pragma once
#include <conio.h>
#include <windows.h>
#include <vector>
#include <filesystem>
#include "Admin.h"
#include "Edit.h"
#include "Save.h"
#include "Load.h"
#include "TestManagement.h"

class ModeAdmin
{
    Admin* admin;
    vector<Person*> person;
    vector<Person*>::iterator iter;
    HANDLE hConsole;

    int CheckInputIndex();
    void ClearScreen(COORD pos);
    void DeleteVector();

public:
    ModeAdmin(Admin* admin);
    ~ModeAdmin();

    void StartMode();
    int PrintMainMenu();
    vector<Person*>::iterator ChoiceUser();
    void DeleteUserFolder();
};

