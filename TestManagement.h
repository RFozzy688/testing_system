#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <map>
#include <filesystem>
#include "Question.h"
#include "Save.h"
#include "Load.h"
using namespace std;

class TestManagement
{
    const string rootCatalog = "catalog";
    string chapter;
    string currentTest;
    int numberTest;
    vector<string> tests;
    map<string, vector<string>> testsTree;
    HANDLE hConsole;
    vector<Question> questions;

    void ClearScreen(COORD pos);

public:
    TestManagement();
    ~TestManagement();
    int PrintMenuTestManagement();
    void StartTestManagement();
    void LoadingTestsTree(map<string, vector<string>>& paths, const string& current_path);
    void PrintTestsTree();
    int PrintMenuCreateTest();
    void CreateChapter();
    void CreateTest();
    bool IsChapter(string str);
    void AddTestToMap(string str);
    string InputNameTest();
    bool IsNameTest(string nameTest);
    void ChoiceChapter();
    void ChoiceTest();
    void DeleteTest();
};

