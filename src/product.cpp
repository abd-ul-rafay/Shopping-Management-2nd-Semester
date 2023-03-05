
#include "product.h"

void Product::setData()
{
    cout << "\n\t\t\t\t Enter the information of item" << endl << endl;

    cin.ignore();
    cout << "\t Item name: "; cin.get(name, 20);
    cout << "\t Item ID: ";
    string _id; cin >> _id;
    id = stoi(_id);
    cout << "\t Item price: "; cin >> price;
    cout << "\t Item quantity: "; cin >> quantity;
}

string Product::get_name() const
{
    return name;
}

unsigned int Product::get_id() const
{
    return id;
}

double Product::get_price() const
{
    return price;
}

int Product::get_quantity() const
{
    return quantity;
}

int Product::operator-(int quantity)
{
    return (this->quantity - quantity);
}

Product Product::operator-=(int quantity)
{
    this->quantity = (this->quantity - quantity);
    return (*this);
}

void Product::display() const
{
    cout << left;
    cout << "\t " << setw(14) << name << setw(12) << id << setw(10) << price << setw(8) << quantity << endl;
}
