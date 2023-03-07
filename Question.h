#pragma once
#include <iostream>
using namespace std;

struct Question
{
    string question;
    string answer_1;
    string answer_2;
    string answer_3;
    string answer_4;
    int trueAnswer;
};

struct UserGrade
{
    string nameTest;
    int countTrueAnswer;
    int percentTrueAnswer;
    int grade;
};
