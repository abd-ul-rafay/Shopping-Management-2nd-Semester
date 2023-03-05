
#include "costumer.h"

///////////////////////////////////////////////
//// Costumer class Functions definitions /////
///////////////////////////////////////////////

Costumer :: Costumer()
{
    cin.ignore();
    // value taken by user
    cout << "\n\t Pleae Enter Some Details" << endl;

    cout << "\t Your name: "; getline(cin, name);
    cout << "\t Your age: "; cin >> age;

}

void Costumer::menu()
{
    int choice = 1;
    unsigned int _id;
    bool is_present = false;

    do
    {
        system("cls");

        cout << "\n\t\t\t - - - - - W E L C O M E - - - - -" << endl;
        cout << "\n\t Here are all the items you can buy" << endl;

        
        file.open(Product_file_path, ios::binary | ios::in);

        if (!file.is_open())
        {
            cout << endl << "\t Product file not opened!" << endl;
        }

        else
        {
            all_products.clear();

            while(file.read(((char *)&(new_item)), sizeof(new_item)))
            {
                new_item.display();
                all_products.push_back(new_item);
            }
            

            cout << "\n\t\t\t\t Displaying all Items" << endl
                << endl;

            if (all_products.size() == 0)
            {
                cout << "\t No item" << endl;
            }

            else
            {
                total_amount.setData((this->name).c_str(), this->age);

                up1:

                cout << left;
                cout << "\t " << setw(14) << "Name" << setw(12) << "ID" << setw(10) << "Price" << setw(8) << "Quantity" << endl;
                cout << "\t --------------------------------------------" << endl;

                // range based for loop
                for (auto i : all_products)
                {
                    i.display();
                }

                file.close();

                file.open(Product_file_path, ios::binary | ios::in | ios::out);
                
                cout << "\n\t Enter ID of item you want to add to cart (0 to exit): ";
                cin >> _id;

                while (file.read((char *)&(new_item), sizeof(new_item)))
                {
                    if (new_item.get_id() == _id)
                    {
                        is_present = true;

                        if (new_item.get_quantity() <= 0)
                        {
                            cout << "\n\t Product not available \n\t Please select any other Product" << endl;
                            cout << "\n\t ";
                            system("pause"); system("cls");

                            goto up1;
                        }

                        up2:
                        system("cls");

                        cout << "\n\t\t\t\t\t You are buying a product" << endl << endl;

                        cout << "\t Product name: " << new_item.get_name() << endl;
                        cout << "\t Product Price: " << "Rs. " << new_item.get_price() << endl;
                        cout << "\t Product Quantity: " << new_item.get_quantity() << endl << endl;

                        cout << "\t How much " << new_item.get_name() << " do you want to buy: ";
                        int _quantity; cin >> _quantity;

                        if ((new_item - _quantity) < 0)
                        {
                            cout << "\n\t Not enough quantity" << endl;
                            cout << "\t You can buy only " << new_item.get_quantity() << " " << new_item.get_name() << endl << endl;

                            cout << "\t ";
                            system("pause");

                            goto up2;
                        }

                        else
                        {
                            new_item -= _quantity;
                            
                            file.seekp(int(file.tellg()) - sizeof(new_item), ios::beg);
                            file.write((char *)&(new_item), sizeof(new_item));

                            cout << "\n\t You bought " << _quantity << " " << new_item.get_name() << endl << endl;

                            total_amount.add_items_in_bill(new_item, _quantity);
                        }
                    }
                }

                file.close();
            }
        }

        if (_id != (0))
        {                
            if (is_present == false)
            {
                cout << "\t ID doesn't matched" << endl;
                choice = 1;

                cout << "\n\t ";
                system("pause");
            }

            else
            {
                cout << "\n\t Press 1 for more shopping"
                        "\n\t Else to see bill" << endl;

                char ch[1]; cout << "\t --> "; cin >> ch;
                choice = atoi(ch);

                if (choice != 1)
                {
                    total_amount.show_all_bought_items();
                    total_amount.give_bill();

                    cout << "\n\t Thanks For visiting" << endl;

                    file.open("DataBase/Costumers.bin", ios::binary | ios::in | ios::out | ios::app);

                    if (!file.is_open())
                    {
                        cout << "\t Costumers file not opened!" << endl;
                    }

                    else
                    {
                        file.write((char *)&(total_amount), sizeof(total_amount));

                        file.close();
                    }

                    cout << "\t ";
                    system("pause");
                }
            }
        }

        else
        {
            cout << "\n\t Thanks for visiting" << endl;

            cout << " \n\t";
            system("pause");

            choice = 0;
        }

    } while (choice == 1);
}
