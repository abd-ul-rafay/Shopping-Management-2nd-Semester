
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Product
{
    private:
        char name[20];
        unsigned int id;
        double price;
        int quantity;

    public:
        void setData();
        unsigned int get_id() const;
        std::string get_name() const;
        double get_price() const;
        int get_quantity() const;
        void display() const;

        int operator-(int);
        Product operator-=(int);
};
