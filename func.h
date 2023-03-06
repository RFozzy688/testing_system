#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Person.h"
using namespace std;

//struct PSEUDO_SYMBOL
//{
//    char cornerLeftTop;
//    char cornerLeftBottom;
//    char cornerRightTop;
//    char cornerRightBottom;
//    char horizontalLine;
//    char verticalLine;
//    char separator;
//    char separatorTop;
//    char separatorBottom;
//};

//void CheckInput()
//{
//    pos.X = 0;
//    pos.Y = 8;
//    SetConsoleCursorPosition(hConsole, pos);
//    while (true) // цикл крутится пока не будет введено корректное значение т.е. цифровое значение
//    {
//
//        cout << " Введите номер события для редактирования: ";
//        cin >> index;
//        --index;
//
//        if (cin.fail())
//        {
//            cin.clear();
//            cin.ignore();
//        }
//        else
//            break;
//    }
//}

enum Mode
{
    _INDEFINED,
    _ADMIN,
    _CUSTOM
};

void DeleteVector(vector<Person*>& vec);

bool IsValidCharacter(char ch);

