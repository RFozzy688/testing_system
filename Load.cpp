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

void Load::LoadTest(vector<Question>& questions)
{
    if (inf.peek() == EOF)
    {
        return;
    }

    questions.clear();
    Question testQuestion;
    string str;
    int number;

    while (!inf.eof())
    {
        questions.push_back(testQuestion);

        getline(inf, questions.back().question);
        getline(inf, questions.back().answer_1);
        getline(inf, questions.back().answer_2);
        getline(inf, questions.back().answer_3);
        getline(inf, questions.back().answer_4);
        getline(inf, str);
        number = stoi(str);
        questions.back().trueAnswer = number;
    }
}

void Load::LoadingUserStat(vector<UserGrade>& userStat)
{
    if (inf.peek() == EOF)
    {
        return;
    }

    UserGrade userGrade;
    userStat.clear();
    string str;
    int number;

    while (!inf.eof())
    {
        userStat.push_back(userGrade);

        getline(inf, userStat.back().nameChapter);
        getline(inf, userStat.back().nameTest);
        getline(inf, str);
        number = stoi(str);
        userStat.back().countTrueAnswer;
        getline(inf, str);
        number = stoi(str);
        userStat.back().percentTrueAnswer;
        getline(inf, str);
        number = stoi(str);
        userStat.back().grade;
    }
}
