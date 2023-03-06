#include "Registration.h"

bool IsValidCharacter(char ch)
{
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) || ch == 95)
        return true;
    else
        return false;
}

void Registration::LoadingData()
{
    load = new Load("dbpersons.txt");
    load->LoadDataPersons(person);
    load->CloseFile();
}

void Registration::SaveData()
{
    save = new Save("dbpersons.txt");
    save->SaveToFile(person);
    save->CloseFile();
}

bool Registration::CheckingLogin(string str)
{
    if (str.size() <= 3)
        return false;

    int size = count_if(begin(str), end(str), IsValidCharacter);

    if (str.size() != size)
        return false;

    for (auto it : person)
    {
        if (it->GetLogin() == str)
            return false;
    }

    return true;
}

void Registration::InputLogin(char* str, int size)
{
    COORD pos;

    while (true)
    {
        cout << " Логин: " << endl;
        cout << "\n       (не меньше 4 и не больше 20 символов)\n";
        cout << "       (Может содержать буквы латинского алфавита, цифры и нижнее подчеркивание)";
        pos.X = 8;
        pos.Y = 8;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(str, size);

        if (CheckingLogin(str))
        {
            pos.X = 8;
            pos.Y = 9;
            ClearScreen(pos);
            cout << "Проверено!";
            break;
        }
        else
        {
            pos.X = 8;
            pos.Y = 9;
            ClearScreen(pos);
            cout << "Ошибка!";

            pos.X = 0;
            pos.Y = 8;
            ClearScreen(pos);
        }
    }
}

bool Registration::CheckingPassword(string str)
{
    if (str.size() <= 3)
        return false;

    auto result = find(begin(str), end(str), ' ');

    if (result == end(str))
        return true;
    else
        return false;
}

void Registration::InputPassword(char* str, int size)
{
    COORD pos;

    while (true)
    {
        pos.X = 0;
        pos.Y = 12;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " Пароль: " << endl;
        cout << "\n        (не меньше 4 и не больше 20 символов)";
        cout << "\n        (не должен содержать пробелы)";

        pos.X = 9;
        pos.Y = 12;
        SetConsoleCursorPosition(hConsole, pos);
        cin.getline(str, size);

        if (CheckingPassword(str))
        {
            pos.X = 9;
            pos.Y = 13;
            ClearScreen(pos);
            cout << "Проверено!";
            break;
        } 
        else
        {
            pos.X = 9;
            pos.Y = 13;
            ClearScreen(pos);
            cout << "Ошибка!";

            pos.X = 0;
            pos.Y = 12;
            ClearScreen(pos);
        }
    }
}

void Registration::ClearScreen(COORD pos)
{
    DWORD count;
    DWORD cellCount;

    cellCount = 100;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, pos, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hConsole, pos);
}

void Registration::DeleteVector()
{
    for (auto iter = person.begin(); iter != person.end(); iter++)
    {
        if (*iter)
        {
            delete* iter;
            *iter = nullptr;
        }
    }

    if (!person.empty())
    {
        person.clear();
    }
}

void Registration::DeepCopy(User* obj)
{
    person.push_back(new User);

    User* temp;
    temp = (User*)person.back();
    
    temp->SetSurName(obj->GetSurName());
    temp->SetName(obj->GetName());
    temp->SetPatronymic(obj->GetPatronymic());
    temp->SetAdress(obj->GetAdress());
    temp->SetPhone(obj->GetPhone());
    temp->SetLogin(obj->GetLogin());
    temp->SetPassword(obj->GetPassword());
}

void Registration::CreateUserFolder(User* obj)
{
    string path;

    path = "users\\" + obj->GetLogin();
    filesystem::create_directory(path);

    path = path + "\\" + obj->GetLogin() + "_stat.txt";

    save = new Save(path);
    save->CloseFile();

    obj->SetPathStat(path);
}

Registration::Registration()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    load = nullptr;
    save = nullptr;
}

Registration::~Registration()
{
    if (load)
        delete load;

    if (save)
        delete save;

    DeleteVector();
}

bool Registration::RegistrationUser(User* obj)
{
    LoadingData();

    const int size = 100;
    char fio[size];
    char buf[size];

    cout << " Фамилия: ";
    cin.getline(fio, size);
    obj->SetSurName(fio);

    cout << " Имя: ";
    cin.getline(fio, size);
    obj->SetName(fio);

    cout << " Отчество: ";
    cin.getline(fio, size);
    obj->SetPatronymic(fio);

    cout << " Адрес: ";
    cin.getline(buf, size);
    obj->SetAdress(buf);

    cout << " Телефон: ";
    cin.getline(buf, size);
    obj->SetPhone(buf);

    const int size2 = 21;
    char str[size2];

    InputLogin(str, size2);
    obj->SetLogin(str);

    InputPassword(str, size2);
    obj->SetPassword(str);

    COORD pos;
    pos.X = 0;
    pos.Y = 16;
    SetConsoleCursorPosition(hConsole, pos);

    char choice;
    cout << " Сохранить? (y/n): ";
    choice = _getch();

    if (choice == 'y')
    {
        DeepCopy(obj);
        SaveData();
        CreateUserFolder(obj);
        return true;
    }
    else
        return false;
}