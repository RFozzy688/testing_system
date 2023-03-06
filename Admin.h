#pragma once
#include "Person.h"

class Admin : public Person
{
public:
    Admin() { SetStatus("admin"); }
    ~Admin() {};
};

