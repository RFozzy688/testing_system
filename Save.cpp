#include "Save.h"

string Save::XorOperation(string inStr)
{
    char encryptionKey = '/';
    string outStr;
    for (int i = 0; i < (int)inStr.length(); i++)
    {
        outStr += inStr[i] ^ encryptionKey;
    }
    return outStr;
}

Save::Save(string path)
{
    outf.open(path, ios::out);
}

Save::~Save()
{
    CloseFile();
}

void Save::SaveToFile(const vector<Person*>& person)
{
    User* obj;
    bool flag = false;

    if (outf)
    {
        for (auto elem : person)
        {
            if (outf.tellp())
                outf << "\n";

            outf << elem->GetSurName() << "\n";
            outf << elem->GetName() << "\n";
            outf << elem->GetPatronymic() << "\n";

            if (flag)
            {
                obj = dynamic_cast<User*>(elem);
                outf << obj->GetAdress() << "\n";
                outf << obj->GetPhone() << "\n";
            }

            outf << elem->GetStatus() << "\n";
            outf << XorOperation(elem->GetLogin()) << "\n";
            outf << XorOperation(elem->GetPassword());

            flag = true;
        }
    } 
    else
    {
        cout << "Ошибка записи в файл!\n";
    }

}

void Save::CloseFile()
{
    outf.close();
}

void Save::OpenFile(string path)
{
    outf.open(path, ios::out);
}

void Save::SaveTest(const vector<Question> questions)
{
    for (auto elem : questions)
    {
        if (outf.tellp())
            outf << "\n";

        outf << elem.question << endl;
        outf << elem.answer_1 << endl;
        outf << elem.answer_2 << endl;
        outf << elem.answer_3 << endl;
        outf << elem.answer_4 << endl;
        outf << elem.trueAnswer;
    }
}
