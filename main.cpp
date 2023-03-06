#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Authentication.h"
#include "Registration.h"
#include "ModeAdmin.h"
#include "ModeCustom.h"

using namespace std;

enum Mode
{
    _INDEFINED,
    _ADMIN,
    _CUSTOM
};

int main()
{
    setlocale(LC_ALL, "");

    Person* currentUser = nullptr;
    int key = 0;
    Mode EMode = /*Mode::*/_INDEFINED;

    while (key != 27) // Esc
    {
        system("cls");
        cout << "\n 1 - ���� | 2 - ����������� | ESC - �����\n";
        cout << " > ";
        key = _getch();

        switch (key)
        {
        case 49: // 1
        {
            SetConsoleCP(1251);
            Authentication authentication;
            authentication.LoadingData();

            while (true)
            {
                system("cls");

                authentication.PrintLoginScreen();
                authentication.InputLogin();
                authentication.InputPassword();

                if (authentication.CheckingData())
                {
                    User* temp = dynamic_cast<User*>(authentication.GetCurrentPerson());

                    if (temp)
                    {
                        currentUser = authentication.GetCurrentPerson();
                        EMode = Mode::_CUSTOM; // ����� ������������
                    } 
                    else
                    {
                        currentUser = authentication.GetCurrentPerson();
                        EMode = Mode::_ADMIN; // ����� ��������������
                    }

                    break;
                }
                else
                {
                    cout << "\n �� ������ ����� ��� ������!!!";
                    _getch();
                }
            }

            cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

            break;
        }
        case 50: // 2
        {
            SetConsoleCP(1251);
            system("cls");
            cout << "\n �����������\n\n";

            if (currentUser) delete currentUser;
            currentUser = new User;
            Registration reg;

            if (reg.RegistrationUser((User*)currentUser))
            {
                EMode = Mode::_CUSTOM;
                break;
            }
            else
            {
                continue;
            }
        }

        //default:
        //    break;
        }

        if (EMode == /*Mode::*/_CUSTOM)
        {
            User* user = dynamic_cast<User*>(currentUser);
            currentUser = nullptr;
            ModeCustom modeCustom(user);
            modeCustom.StartMode();
            EMode = _INDEFINED;
        } 
        else if (EMode == _ADMIN)
        {
            Admin* admin = dynamic_cast<Admin*>(currentUser);
            currentUser = nullptr;
            ModeAdmin modeAdmin(admin);
            modeAdmin.StartMode();
            EMode = /*Mode::*/_INDEFINED;
        }
    }

    if (currentUser)
    {
        delete currentUser;
    }

    return 0;
}