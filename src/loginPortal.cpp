
#include "loginPortal.h"

void Layout()
{
    system("cls");
              cout << "\n\t\t\t\t\t\t W E L C O M E   T O" << endl;
    cout << "\t\t\t\t S H O P P I N G   M A N A G M E N T   S Y S T E M" << endl << endl;
}

void Login()
{    
    int key;
    char ch[1];

    do
    {
        system("cls");
        Layout();

        cout << "\t Please enter your choice" << endl
            << "\t 1. Login as Admin" << endl
            << "\t 2. Visit as Costumer" << endl
            << "\t Else to Exit" << endl;

        cout << "\t --> "; cin >> ch;
        key = atoi(ch);

        switch (key)
        {
            case 1:
                {
                    Admin::GetInstance()->compare_password(); // Singleton class to avoid creating more than one instance
                    Admin::GetInstance()->menu();
                }
                break;

            case 2:
                {
                    Costumer *cos1 = new Costumer;
                    cos1->menu();
                }
                break;

            default:
                cout << "\n\t Exited successfully" << endl;
                exit(0);
                break;
        }

    } while (true);
}
