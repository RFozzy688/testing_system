#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <cmath>
#include "User.h"
#include "TestManagement.h"
#include "Load.h"
#include "Save.h"
#include "Question.h"

class ModeCustom
{
    User* user;
    HANDLE hConsole;
    vector<Question> questions;
    vector<int> userAnswer;
    string fullNameTest;
    UserGrade userGrade;

    void ClearScreen(COORD pos);

public:
    ModeCustom(User* user);
    ~ModeCustom();

    void StartMode();
    int PrintMainMenu();
    void Testing();
    void ResultTest();
    void PrintResult();
};

