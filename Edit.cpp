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

    cout << "\n Редактировать:\n";
    cout << "\n 1 - Фамилию | 2 - Имя | 3 - Отчество | 4 - Логин | 5 - Пароль | 6 - Адрес | 7 - Телефон | Esc - Выход\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

    return key;
}

int Edit::PrintMenuEditAdmin()
{
    //system("cls");

    cout << "\n Редактировать:\n";
    cout << "\n 1 - Фамилию | 2 - Имя | 3 - Отчество | 4 - Логин | 5 - Пароль | Esc - Выход\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

    return key;
}

void Edit::EditSurName()
{
    cout << "\n\n Фамилия: ";
    getline(cin, str);

    person->SetSurName(str);
}

void Edit::EditName()
{
    cout << "\n\n Имя: ";
    getline(cin, str);

    person->SetName(str);
}

void Edit::EditPatronymic()
{
    cout << "\n\n Отчество: ";
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

    cout << "\n Редактировать:\n\n";

    while (true)
    {
        cout << " Логин: " << endl;
        cout << "\n       (не меньше 4 и не больше 20 символов)\n";
        cout << "       (Может содержать буквы латинского алфавита, цифры и нижнее подчеркивание)";
        pos.X = 8;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(buf, size);

        if (CheckingLogin(buf))
        {
            pos.X = 8;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "Проверено!";
            Sleep(2000);
            break;
        }
        else
        {
            pos.X = 8;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "Ошибка!";

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

    cout << "\n Редактировать:\n\n";

    while (true)
    {
        cout << " Пароль: " << endl;
        cout << "\n        (не меньше 4 и не больше 20 символов)";
        cout << "\n        (не должен содержать пробелы)";

        pos.X = 9;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(buf, size);

        if (CheckingPassword(buf))
        {
            pos.X = 9;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "Проверено!";
            Sleep(2000);
            break;
        }
        else
        {
            pos.X = 9;
            pos.Y = 4;
            ClearScreen(pos);
            cout << "Ошибка!";

            pos.X = 0;
            pos.Y = 3;
            ClearScreen(pos);
        }
    }

    person->SetPassword(buf);
}

void Edit::EditAdress()
{
    cout << "\n\n Адрес: ";
    getline(cin, str);

    user->SetAdress(str);
}

void Edit::EditPhone()
{
    cout << "\n\n Телефон: ";
    getline(cin, str);

    user->SetPhone(str);
}
