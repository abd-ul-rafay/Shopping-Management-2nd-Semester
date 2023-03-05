
#pragma once
#include <cstring>
#include "user.h"

class Bill
{
    private:
        char name[20];
        int age;
        int quantity_chosen;
        std::vector<pair<Product, int>> all_items_bought;
        int total_bill;

    public:
        void setData(const char *name, int age);
        void add_items_in_bill(Product items, int quantity_chosen);
        void show_all_bought_items();
        void give_bill();
        void displayMembers();
};
