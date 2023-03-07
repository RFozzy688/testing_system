#pragma once
//#include <iostream>
#include <fstream>
#include <vector>
#include "Admin.h"
#include "User.h"
#include "Question.h"
using namespace std;

class Save
{
    ofstream outf;

    string XorOperation(string inStr);

public:    
    Save(string path);
    ~Save();

    void SaveToFile(const vector<Person*>& person);
    void CloseFile();
    void OpenFile(string path);
    void SaveTest(const vector<Question>& questions);
    void SavingUserStat(const vector<UserGrade>& userStat);
};

