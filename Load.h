#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Admin.h"
#include "User.h"
#include "Question.h"
using namespace std;

class Load
{
    ifstream inf;

    string XorOperation(string inStr);

public:
    Load(string path);
    ~Load();

    void LoadDataPersons(vector<Person*>& users);
    void CloseFile();
    void OpenFile(string path);
    void LoadTest(vector<Question>& questions);
    void LoadingUserStat(vector<UserGrade>& userStat);
};

