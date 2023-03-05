
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "product.h"
#include "bill.h"
using namespace std;

///////////////////////////////////////
////////// User Base Class ////////////
///////////////////////////////////////

class User
{
    protected:
        std::string name;
        unsigned int age;

        const char* Product_file_path = "Database/Products.bin";
        const char* Temp_file_path = "Database/temp.bin";

        virtual void menu() = 0;
};
