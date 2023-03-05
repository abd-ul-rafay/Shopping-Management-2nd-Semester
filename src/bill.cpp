
#include "bill.h"

void Bill::setData(const char *name, int age)
{
    strcpy(this->name, name);
    this->age = age;
}

void Bill::add_items_in_bill(Product items, int quantity_chosen)
{
    all_items_bought.push_back(make_pair(items, quantity_chosen));
}

void Bill::show_all_bought_items()
{
    system("cls");

    cout << "\n\t\t\t\t - - - Your Bill - - -" << endl << endl;

    cout << "\t Name of costumer: " << name << endl
        << "\t Age of costumer: " << age << endl << endl;

    int index = 1;
    for (auto i : all_items_bought)
    {
        cout << "\t Product no." << index << endl;
        cout << "\t Product name: " << i.first.get_name() << endl;
        cout << "\t Product Price: " << i.first.get_price() << endl;
        cout << "\t Product quantity: " << i.second << endl << endl;
    }
}

void Bill::give_bill()
{
    total_bill = 0;

    for (auto i : all_items_bought)
    {
        total_bill += (i.first.get_price() * i.second);
    }

    cout << "\n\t Total bill is: Rs. " << total_bill << endl;
}

void Bill::displayMembers()
{
    cout << "\t " << "Name: " << name << "\t" << "Age: " << age << endl;

    cout << "\t Total bill: " << total_bill << endl;
    cout << "\t - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
}
