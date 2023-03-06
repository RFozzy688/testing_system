#include "func.h"

void DeleteVector(vector<Person*>& vec)
{
    for (auto it : vec)
    {
        delete it;
    }
}

bool IsValidCharacter(char ch)
{
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) || ch == 95)
        return true;
    else
        return false;
}