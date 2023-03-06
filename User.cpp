#include "User.h"

User::User() { SetStatus("user"); }
User::~User() {}

void User::SetPhone(string phone) { this->phone = phone; }
string User::GetPhone() const { return phone; }

void User::SetAdress(string adress) { this->adress = adress; }
string User::GetAdress() { return adress; }

void User::PrintUserInfo()
{
    PrintInfoPerson();
    cout << " �����: " << adress << endl;
    cout << " �������: " << phone << endl;
    PrintInfoAuthentication();
}
