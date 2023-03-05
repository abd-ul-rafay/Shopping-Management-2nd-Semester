
#pragma once
#include "user.h"

///////////////////////////////////////
//////// Admin Drived Class ///////////
///////////////////////////////////////

class Admin : private User // Singleton class
{
    private:
        static Admin *instance;

        std::string password;
        Product new_item;
        std::vector<Product> shop_products;
        std::fstream file;
        Bill total_amount;

    public:
        static Admin *GetInstance();

        void compare_password();
        void menu() override;

        void insert_item();
        void display_all_items();
        void modify_item();
        void del_item();
        void del_all_items();
        void see_costumer_records();
        void delete_costumer_records();
};
