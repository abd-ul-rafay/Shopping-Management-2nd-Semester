
#include "admin.h"

///////////////////////////////////////////////
////// Admin class Functions definitions //////
///////////////////////////////////////////////

Admin *Admin::GetInstance()
{
    return instance == nullptr ? new Admin() : instance;
}

Admin *Admin::instance;

void Admin::compare_password()
{
    this->name = "a";
    this->password = "me";

    string entered_name;
    string entered_password;

    up: // goto label

    cout << "\n\t Login First" << endl;

    cin.ignore();
    cout << "\t Enter Name: "; getline(cin, entered_name);
    cout << "\t Enter Password: "; cin >> entered_password;

    if ((entered_name != (*this).name) || (entered_password != (*this).password)) // if not
    {
        cout << "\t Wrong password entered! Try again" << endl;
        goto up;
    }

    else
    {
        cout << "\t Access Granted" << endl;
    }
}

void Admin::menu()
{
    int choice;

    do
    {
        system("cls");

        cout << "\n\t\t\t - - - - - W E L C O M E - - - - -" << endl;

        cout << "\n\t 1. Create Item"
                "\n\t 2. Display all Items"
                "\n\t 3. Modify an Item"
                "\n\t 4. Delete a Record"
                "\n\t 5. Delete all Record"
                "\n\t 6. See Costumers Records"
                "\n\t 7. Delete costumers Record"
                "\n\t 0. Exit" << endl;

        /*--------------------------------------------------*/


        cout << "\n\t Enter your choice --> "; cin >> choice;

        system("cls");
        switch (choice)
        {
            case 0:
                cout << "\n\t Exited";
                break;
            case 1:
                insert_item();
                break;
            case 2:
                display_all_items();
                break;
            case 3:
                modify_item();
                break;
            case 4:
                del_item();
                break;
            case 5:
                del_all_items();
                break;
            case 6:
                see_costumer_records();
                break;
            case 7:
                delete_costumer_records();
                break;

            default:
                cout << "\n\t Case not defined yet" << endl;
                break;
        }

        cout << "\n\t ";
        system("pause");

    } while (choice != 0);

}

void Admin::insert_item()
{
    new_item.setData();

    file.open(Product_file_path, ios::binary | ios::out | ios::app);

    if (!file.is_open())
    {
        file.open(Product_file_path, ios::binary | ios::out | ios::trunc);

        if (!file.is_open())
        {
            cout << endl << "\t Product file not opened!" << endl;
        }
    }

    else
    {
        file.write(((char *) &(new_item)), sizeof(new_item));
        cout << "\t Added successfully" << endl;

        file.close();
    }
}

void Admin::display_all_items()
{
    file.open(Product_file_path, ios::binary | ios::in);

    if (!file.is_open())
    {
        cout << endl << "\t Product file not opened!" << endl;
    }

    else
    {
        shop_products.clear();

        while(file.read(((char *)&(new_item)), sizeof(new_item)))
        {
            shop_products.push_back(new_item);
        }

        file.close();
    }

    cout << "\n\t\t\t\t Displaying all Items" << endl
         << endl;

    if (shop_products.size() == 0)
        cout << "\t No item" << endl;

    else
    {
        cout << left;
        cout << "\t " << setw(14) << "Name" << setw(12) << "ID" << setw(10) << "Price" << setw(8) << "Quantity" << endl;
        cout << "\t -----------------------------------------" << endl;

        // range based for loop
        for (auto i : shop_products)
        {
            i.display();
        }
    }
}

void Admin::modify_item()
{
    display_all_items(); // First displaying all items/products

    file.open(Product_file_path, ios::binary | ios::in | ios::out);

    if (!file.is_open())
    {
        cout << "\t Product file not opened!" << endl;
    }

    else
    {
        unsigned int _id;
        cout << "\n\t Enter the ID of item you want to modify: "; cin >> _id;
        bool is_present = false;

        while (file.read((char *)&(new_item), sizeof(new_item)))
        {
            if(new_item.get_id() == _id)
            {
                is_present = true;

                cout << "\n\t Enter new Data";
                new_item.setData();

                file.seekp(int(file.tellg()) - sizeof(new_item), ios::beg);
                file.write((char *)&(new_item), sizeof(new_item));

                cout << "\n\t Modified successfully" << endl;

                break;
            }
        }

        if (is_present == false)
        {
            cout << "\t ID doesn't exist" << endl;
        }

        file.close();
    }
}

void Admin::del_item()
{
    display_all_items(); // First displaying all items/products

    ofstream temp;
    file.open(Product_file_path, ios::binary | ios::in);
    temp.open(Temp_file_path, ios::binary);

    if (!file.is_open())
    {
        cout << "\t Product file not opened!" << endl;
    }

    else
    {
        unsigned int _id;
        cout << "\n\t Enter the ID of item you want to delete: "; cin >> _id;
        bool is_present = false;

        while (file.read((char *)&(new_item), sizeof(new_item)))
        {
            if(new_item.get_id() != _id)
            {
                temp.write((char *)&(new_item), sizeof(new_item));
            }
            else
            {
                is_present = true;
            }
        }

        file.close();
        temp.close();

        std::remove(Product_file_path);
        rename(Temp_file_path, Product_file_path);

        if (is_present == false)
        {
            cout << "\t ID doesn't exist" << endl;
            std::remove(Temp_file_path);
        }
        else
        {
            cout << "\t Deleted successfully" << endl;
        }
    }
}

void Admin::del_all_items()
{
    cout << "\n\t\t\t\t Deleting all items" << endl;

    cout << "\n\t Are you sure you want to delete all items (y/n): ";
    char ch; cin >> ch;

    switch (ch)
    {
        case 'y':
        case 'Y':
            std::remove(Product_file_path);
            file.open(Product_file_path, ios::binary | ios::out | ios::in | ios::trunc);
            shop_products.clear();
            cout << "\t All items are deleted successfully" << endl;
            break;
        
        default:
            cout << "\t Items not deleted" << endl;
            break;
    }
}

void Admin::see_costumer_records()
{
    file.open("DataBase/Costumers.bin", ios::binary | ios::in);

    if (!file.is_open())
    {
        cout << "\t Costumers file not opened!" << endl;
    }

    else
    {
        system("cls");
        cout << endl;
        while(file.read((char *)&(total_amount), sizeof(total_amount)))
        {
            total_amount.displayMembers();
        }
        file.close();
    }
}

void Admin::delete_costumer_records()
{
    cout << "\n\t\t\t\t Deleting all Costumer records" << endl;

    cout << "\n\t Are you sure you want to delete all record (y/n): ";
    char ch; cin >> ch;

    switch (ch)
    {
        case 'y':
        case 'Y':
            std::remove("DataBase/Costumers.bin");
            file.open("DataBase/Costumers.bin", ios::binary | ios::out | ios::in | ios::trunc);

            cout << "\t All costumer record are deleted successfully" << endl;
            break;
        
        default:
            cout << "\t Record not deleted" << endl;
            break;
    }

    cout << endl
         << endl
         << "\t File record cleared successfully" << endl;

    file.close();
}