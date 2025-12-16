#include <iostream>
#include <windows.h>
#include "Microwave.hpp"

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Microwave m;
    int cmd;

    while (true)
    {
        cout << "\n=== Microwave State ===\n";
        cout << "Power: " << m.GetPower() << endl;
        cout << "Door: " << m.GetDoor() << endl;
        cout << "Mode: " << (m.GetMode() == MICRO ? "Micro" : "Grill") << endl;
        cout << "Power level: " << m.GetCurrentPower() << endl;
        cout << "Timer: " << m.GetTimer() << endl;
        cout << "Radiator: " << m.IsRadiatorOn() << endl;
        cout << "Heater: " << m.IsHeaterOn() << endl;

        cout << "\nCommands:\n";
        cout << "1 - Turn on\n";
        cout << "2 - Turn off\n";
        cout << "3 - Set mode\n";
        cout << "4 - Set microwave power\n";
        cout << "5 - Set timer\n";
        cout << "6 - Start heating\n";
        cout << "7 - Open door\n";
        cout << "8 - Close door\n";
        cout << "9 - Finish heating\n";
        cout << "0 - Exit\n";
        cin >> cmd;

        if (cmd == 0) break;

        if (cmd == 1)
            m = true;            // operator=

        if (cmd == 2)
            m = false;           // operator=

        if (cmd == 3)
        {
            int x;
            cout << "0 - micro, 1 - grill: ";
            cin >> x;

            if (cin.fail() || (x != 0 && x != 1))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: введіть 0 або 1!\n";
                continue;
            }

            m.SetMode((Mode)x); // режим НЕ перевантажували
        }

        if (cmd == 4)
        {
            int p;
            cout << "Power (160/320/640/800): ";
            cin >> p;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: введіть число!\n";
                continue;
            }

            m <<= p;             // operator<<=
        }

        if (cmd == 5)
        {
            int t;
            cout << "Введіть час у секундах: ";
            cin >> t;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: введіть число!\n";
                continue;
            }

            m ^= t;              
        }

        if (cmd == 6)
            m.StartHeating();

        if (cmd == 7)
            m.OpenDoor();

        if (cmd == 8)
            m.CloseDoor();

        if (cmd == 9)
        {
            double kwh = m.FinishHeating();
            cout << "Energy: " << kwh << " kWh\n";
        }
    }

    return 0;
}

