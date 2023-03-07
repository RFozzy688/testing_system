#include "ModeAdmin.h"

int ModeAdmin::CheckInputIndex()
{
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    SetConsoleCursorPosition(hConsole, pos);

    int index;

    while (true) // цикл крутится пока не будет введено корректное значение т.е. цифровое значение
    {
        cout << "\n Введите порядковый номер пользователя:\n";
        cout << " > ";
        cin >> index;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();

            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);
        }
        else
            break;
    }

    return index;
}

void ModeAdmin::ClearScreen(COORD pos)
{
    DWORD count;
    DWORD cellCount;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cellCount = 100;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, pos, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hConsole, pos);
}

void ModeAdmin::DeleteVector()
{
    for (auto iter = person.begin(); iter != person.end(); iter++)
    {
        if (*iter)
        {
            delete *iter;
            *iter = nullptr;
        }
    }

    if (!person.empty())
    {
        person.clear();
    }
}

ModeAdmin::ModeAdmin(Admin* admin)
{
    this->admin = admin;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

ModeAdmin::~ModeAdmin()
{
    if (admin)
    {
        delete admin;
    }

    DeleteVector();
}

void ModeAdmin::StartMode()
{
    int key = 0;

    while (key != 27) // esc
    {
        key = PrintMainMenu();

        switch (key)
        {
        case 49: // 1 edit admin
        {
            Load load("dbpersons.txt");
            load.LoadDataPersons(person);
            load.CloseFile();

            Edit edit(admin);

            if (edit.StartEdit())
            {
                char choice;
                cout << "\n\n Сохранить? (y/n): ";
                choice = _getch();

                if (choice == 'y')
                {
                    iter = person.begin();
                    delete *iter;
                    *iter = admin;

                    Save save("dbpersons.txt");
                    save.SaveToFile(person);
                    save.CloseFile();

                    *iter = nullptr;
                    DeleteVector();
                }
            }
            break;
        }
        case 50: // 2 edit user
        {
            Load load("dbpersons.txt");
            load.LoadDataPersons(person);
            load.CloseFile();

            Edit edit(*ChoiceUser());

            if (edit.StartEdit())
            {
                char choice;
                cout << "\n\n Сохранить? (y/n): ";
                choice = _getch();

                if (choice == 'y')
                {
                    Save save("dbpersons.txt");
                    save.SaveToFile(person);
                    save.CloseFile();

                    DeleteVector();
                }
            }
            break;
        }
        case 51: // 3 create user
        {
            system("cls");

            cout << "\n Новый User";

            COORD pos;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            pos.X = 0;
            pos.Y = 3;
            SetConsoleCursorPosition(hConsole, pos);

            User obj;
            Registration reg;
            reg.RegistrationUser(&obj);
            break;
        }
        case 52: // 4
        {
            Load load("dbpersons.txt");
            load.LoadDataPersons(person);
            load.CloseFile();

            system("cls");
            int number;
            COORD pos;

            pos.Y = 7;
            pos.X = 0;
            SetConsoleCursorPosition(hConsole, pos);
            PrintUsers();

            pos.Y = 0;
            pos.X = 0;
            SetConsoleCursorPosition(hConsole, pos);

            cout << "\n Статистика\n";
            cout << "\n Номер пользователя: ";

            while (true)
            {
                cin >> number;

                if (cin.fail() || number <= 0 || number >= person.size())
                {
                    cin.clear();
                    cin.ignore();
                    pos.Y = 3;
                    pos.X = 21;
                    ClearScreen(pos);
                    SetConsoleCursorPosition(hConsole, pos);
                    continue;
                }
                else
                {
                    break;
                }
            }

            string path;
            path = "users\\" + person[number]->GetLogin() + "\\" + person[number]->GetLogin() + "_stat.txt";

            load.OpenFile(path);
            load.LoadingUserStat(userStat);
            load.CloseFile();

            PrintUserStat();

            DeleteVector();
            _getch();
            break;
        }
        case 53: // 5 Test Management
        {
            TestManagement testManagement;
            testManagement.StartTestManagement();
            break;
        }
        case 54: // 6 delete user
        {
            Load load("dbpersons.txt");
            load.LoadDataPersons(person);
            load.CloseFile();

            ChoiceUser();

            char choice;
            cout << "\n Удалить пользователя? (y/n): ";
            choice = _getch();

            if (choice == 'y')
            {
                DeleteUserFolder();
                person.erase(iter);

                Save save("dbpersons.txt");
                save.SaveToFile(person);
                save.CloseFile();

                DeleteVector();
            }

            break;
        }
        default:
            break;
        }
    }
}

int ModeAdmin::PrintMainMenu()
{
    system("cls");

    cout << "\n Режим администратора\n";
    cout << "\n 1 - Редактировать Admin | 2 - Редактировать Users | 3 Новый User | 4 -  Статистика | 5 - Управление тестами";
    cout << "\n 6 - Удалить User | Esc - Выход\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

    return key;
}

vector<Person*>::iterator ModeAdmin::ChoiceUser()
{
    system("cls");

    cout << "\n\n\n\n\n\n";

    int count = 1;
    User* obj;
    bool flag = true;
    for (auto it : person)
    {
        if (flag) // первый элемент это админ
        {
            flag = false;
            continue;
        }

        obj = dynamic_cast<User*>(it);
        cout << count++ << endl;
        obj->PrintUserInfo();
        cout << endl;
    }

    unsigned index;
    COORD pos;

    while (true)
    {
        index = CheckInputIndex();

        if (index >= person.size() || index < 0)
        {
            char ch;

            cout << "\n Пользователя под таким номером не существует. Продолжить(y/n): ";
            ch = _getch();

            if (ch == 'y')
            {
                pos.X = 0;
                pos.Y = 4;
                ClearScreen(pos);
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            iter = person.begin() + index;
            break;
        }
    }

    return iter;
}

void ModeAdmin::DeleteUserFolder()
{
    User* obj = dynamic_cast<User*>(*iter);

    if (obj)
    {
        string path = "users\\" + obj->GetLogin();
        filesystem::remove_all(path);
    }
}

void ModeAdmin::PrintUserStat()
{
    system("cls");

    cout << "\n Полная статистика\n\n";
    cout << "\t\t\t\t\t\tПравильные ответы\tПроцент правильных ответов\tОценка\n\n";

    string prevNameChapter = "";
    COORD pos;
    pos.Y = 5;

    for (auto it : userStat)
    {
        string temp;

        if (prevNameChapter != it.nameChapter)
        {
            cout << " " << it.nameChapter << endl;
            pos.Y += 1;
        }
        prevNameChapter = it.nameChapter;
        cout << "   " << it.nameTest;

        pos.X = 55;
        SetConsoleCursorPosition(hConsole, pos);
        cout << it.countTrueAnswer;
        pos.X += 25;
        SetConsoleCursorPosition(hConsole, pos);
        cout << it.percentTrueAnswer;
        pos.X += 26;
        SetConsoleCursorPosition(hConsole, pos);
        cout << it.grade << endl;

        pos.Y += 1;
    }
}

void ModeAdmin::PrintUsers()
{
    bool flag = true;
    int count = 1;

    for (auto it : person)
    {
        if (flag)
        {
            flag = false;
            continue;
        }

        cout << " " << count++ << ".";
        it->PrintInfoPerson();
        cout << endl;
    }
}
