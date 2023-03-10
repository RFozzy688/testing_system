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

    cin >> login;
    //login = "admin";
    //login = "fozzy";
}

void Authentication::InputPassword()
{
    COORD pos;
    pos.X = 9;
    pos.Y = 3;

    SetConsoleCursorPosition(hConsole, pos);

    cin >> password;
    //password = "admin";
    //password = "fozzy";
}

void Authentication::PrintLoginScreen()
{
    system("cls");

    cout << "\n ?????: ";
    cout << "\n\n ??????: ";
}

bool Authentication::CheckingData()
{
    for (auto it : person)
    {
        if (login == it->GetLogin() && password == it->GetPassword())
        {
            User* obj = dynamic_cast<User*>(it);

            if (obj)
            {
                string path = "users\\" + it->GetLogin() + "\\" + it->GetLogin() + "_stat.txt";
                obj->SetPathStat(path);
                currentPerson = obj;
            }
            else
            {
                currentPerson = it;
            }

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
