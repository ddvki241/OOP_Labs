#include <iostream>
#include "FileCopier.hpp"

using namespace std;

int main()
{
    cout << "=== Demonstration of FileCopier class ===\n";

    // 1) Конструктор з одним аргументом
    FileCopier f1("test.txt");
    cout << "Copying test.txt -> " << f1.GetCopyName() << endl;
    cout << (f1.CopyFile() ? "Success\n" : "Fail\n");

    // 2) Конструктор з двома аргументами
    FileCopier f2("test.txt", "newCopy.txt");
    cout << "Copying test.txt -> newCopy.txt\n";
    cout << (f2.CopyFile() ? "Success\n" : "Fail\n");

    // 3) Конструктор з трьома аргументами
    FileCopier f3("test.txt", "dirCopy.txt", "copies");
    cout << "Copying test.txt into /copies/\n";
    cout << (f3.CopyFile() ? "Success\n" : "Fail\n");

    // Визначення розміру
    cout << "Size of test.txt = " << f1.GetFileSize() << " bytes\n";

    return 0;
}
