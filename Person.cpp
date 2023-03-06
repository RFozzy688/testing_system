#include "Person.h"

Person::~Person() {};

void Person::SetSurName(string surName) { this->surName = surName; }
string Person::GetSurName() const { return surName; }

void Person::SetName(string name) { this->name = name; }
string Person::GetName() const { return name; }

void Person::SetPatronymic(string patronymic) { this->patronymic = patronymic; }
string Person::GetPatronymic() const { return patronymic; }

void Person::SetLogin(string login) { this->login = login; }
string Person::GetLogin() const { return login; }

void Person::SetPassword(string password) { this->password = password; }
string Person::GetPassword() const { return password; }

void Person::SetStatus(string status) { this->status = status; }
string Person::GetStatus() const { return status; }

void Person::PrintInfoPerson()
{
    cout << " ФИО: " << surName + " " + name + " " + patronymic << endl;
    cout << " Статус: " << status << endl;
}

void Person::PrintInfoAuthentication()
{
    cout << " Логин: " << login << endl;
    cout << " Пароль: " << password << endl;
}
