#include "Edit.h"

Edit::Edit(Person* person)
{
    this->person = person;
    user = dynamic_cast<User*>(person);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool Edit::StartEdit()
{
    COORD pos;
    int key = 0;

    while (key != 27) // esc
    {
        if (user)
        {
            system("cls");

            pos.X = 0;
            pos.Y = 8;
            SetConsoleCursorPosition(hConsole, pos);

            user->PrintUserInfo();

            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);

            key = PrintMenuEditUser();
        }
        else
        {
            system("cls");

            pos.X = 0;
            pos.Y = 8;
            SetConsoleCursorPosition(hConsole, pos);

            person->PrintInfoPerson();
            person->PrintInfoAuthentication();

            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);

            key = PrintMenuEditAdmin();
        }

        switch (key)
        {
        case 49: // 1
        {
            EditSurName();
            isChange = true;
            break;
        }
        case 50: // 2
        {
            EditName();
            isChange = true;
            break;
        }
        case 51: // 3
        {
            EditPatronymic();
            isChange = true;
            break;
        }
        case 52: // 4
        {
            EditLogin();
            isChange = true;
            break;
        }
        case 53: // 5
        {
            EditPassword();
            isChange = true;
            break;
        }
        default:
            break;
        }

        if (user)
        {
            switch (key)
            {
            case 54: // 6
            {
                EditAdress();
                isChange = true;
                break;
            }
            case 55: // 7
            {
                EditPhone();
                isChange = true;
                break;
            }
            default:
                break;
            }
        }
    }

    return isChange;
}

int Edit::PrintMenuEditUser()
{
    //system("cls");

    cout << "\n �������������:\n";
    cout << "\n 1 - ������� | 2 - ��� | 3 - �������� | 4 - ����� | 5 - ������ | 6 - ����� | 7 - ������� | Esc - �����\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    return key;
}

int Edit::PrintMenuEditAdmin()
{
    //system("cls");

    cout << "\n �������������:\n";
    cout << "\n 1 - ������� | 2 - ��� | 3 - �������� | 4 - ����� | 5 - ������ | Esc - �����\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    return key;
}

void Edit::EditSurName()
{
    cout << "\n\n �������: ";
    getline(cin, str);

    person->SetSurName(str);
}

void Edit::EditName()
{
    cout << "\n\n ���: ";
    getline(cin, str);

    person->SetName(str);
}

void Edit::EditPatronymic()
{
    cout << "\n\n ��������: ";
    getline(cin, str);

    person->SetPatronymic(str);
}

void Edit::EditLogin()
{
    system("cls");
    COORD pos;
    
    const int size = 21;
    char buf[size];
    LoadingData();

    cout << "\n �������������:\n\n";

    while (true)
    {
        cout << " �����: " << endl;
        cout << "\n       (�� ������ 4 � �� ������ 20 ��������)\n";
        cout << "       (����� ��������� ����� ���������� ��������, ����� � ������ �������������)";
        pos.X = 8;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(buf, size);

        if (CheckingLogin(buf))
        {
            pos.X = 8;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "���������!";
            Sleep(2000);
            break;
        }
        else
        {
            pos.X = 8;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "������!";

            pos.X = 0;
            pos.Y = 3;
            ClearScreen(pos);
        }
    }

    person->SetLogin(buf);
}

void Edit::EditPassword()
{
    system("cls");
    COORD pos;

    const int size = 21;
    char buf[size];

    cout << "\n �������������:\n\n";

    while (true)
    {
        cout << " ������: " << endl;
        cout << "\n        (�� ������ 4 � �� ������ 20 ��������)";
        cout << "\n        (�� ������ ��������� �������)";

        pos.X = 9;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(buf, size);

        if (CheckingPassword(buf))
        {
            pos.X = 9;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "���������!";
            Sleep(2000);
            break;
        }
        else
        {
            pos.X = 9;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "������!";

            pos.X = 0;
            pos.Y = 3;
            ClearScreen(pos);
        }
    }

    person->SetPassword(buf);
}

void Edit::EditAdress()
{
    cout << "\n\n �����: ";
    getline(cin, str);

    user->SetAdress(str);
}

void Edit::EditPhone()
{
    cout << "\n\n �������: ";
    getline(cin, str);

    user->SetPhone(str);
}
