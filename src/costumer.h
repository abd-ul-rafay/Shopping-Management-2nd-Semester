
#pragma once
#include "user.h"

///////////////////////////////////////
/////// Costumer Drived Class /////////
///////////////////////////////////////

class Costumer : private User
{
    private:
        int id;
        Product new_item;
        std::fstream file;
        std::vector<Product> all_products;
        Bill total_amount;

    public:
        Costumer();
        void menu() override;
};
