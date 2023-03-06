#include "Load.h"

string Load::XorOperation(string inStr)
{
    char encryptionKey = '/';
    string outStr;
    for (int i = 0; i < (int)inStr.length(); i++)
    {
        outStr += inStr[i] ^ encryptionKey;
    }
    return outStr;
}

Load::Load(string path)
{
    inf.open(path, ios::in);

    if (!inf)
    {
        cout << "Ошибка открытия файла " + path << endl;;
        exit(0);
    }
}

Load::~Load()
{
    CloseFile();
}

void Load::LoadDataPersons(vector<Person*>& person)
{
    if (inf.peek() == EOF)
    {
        return;
    }

    string str;
    User* user = nullptr;
    bool flag = false;
    Person* iter = nullptr;

    while (!inf.eof())
    {
        if (flag)
        {
            person.push_back(new User);
            iter = dynamic_cast<User*>(person.back());
            user = dynamic_cast<User*>(person.back());
        } 
        else
        {
            person.push_back(new Admin);
            iter = dynamic_cast<Admin*>(person.back());
        }

        getline(inf, str);
        iter->SetSurName(str);

        getline(inf, str);
        iter->SetName(str);

        getline(inf, str);
        iter->SetPatronymic(str);

        if (user)
        {
            getline(inf, str);
            user->SetAdress(str);

            getline(inf, str);
            user->SetPhone(str);
        } 

        getline(inf, str);
        iter->SetStatus(str);

        getline(inf, str);
        iter->SetLogin(XorOperation(str));

        getline(inf, str);
        iter->SetPassword(XorOperation(str));

        flag = true;
    }
}

void Load::CloseFile()
{
    inf.close();
}

void Load::OpenFile(string path)
{
    inf.open(path, ios::in);
}
