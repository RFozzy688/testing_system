#include "Authentication.h"

void Authentication::DeleteVector()
{
    for (auto it : person)
    {
        if (it != currentPerson)
        {
            delete it;
        }
    }
}

Authentication::Authentication() 
{ 
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    load = nullptr;
    save = nullptr;
    currentPerson = nullptr;
}

Authentication::~Authentication()
{
    if (load)
        delete load;

    if (save)
        delete save;

    DeleteVector();
}

void Authentication::InputLogin()
{
    COORD pos;
    pos.X = 8;
    pos.Y = 1;

    SetConsoleCursorPosition(hConsole, pos);

    //cin >> login;
    login = "admin";
}

void Authentication::InputPassword()
{
    COORD pos;
    pos.X = 9;
    pos.Y = 3;

    SetConsoleCursorPosition(hConsole, pos);

    //cin >> password;
    password = "admin";
}

void Authentication::PrintLoginScreen()
{
    system("cls");

    cout << "\n Логин: ";
    cout << "\n\n Пароль: ";
}

bool Authentication::CheckingData()
{
    for (auto it : person)
    {
        if (login == it->GetLogin() && password == it->GetPassword())
        {
            currentPerson = it;
            return true;
        }
    }

    return false;
}

void Authentication::LoadingData()
{
    load = new Load("dbpersons.txt");
    load->LoadDataPersons(person);
    load->CloseFile();
}

Person* Authentication::GetCurrentPerson()
{
    return currentPerson;
}
