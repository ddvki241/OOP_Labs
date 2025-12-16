#include <iostream>
#include <windows.h>
#include "sequence.hpp"

using namespace std;



int main() {
    // Налаштування консолі
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== ЛАБОРАТОРНА РОБОТА No5 (Варіант 6) ===" << endl;

    // --- ТЕСТ 1: Арифметична прогресія ---
    cout << "\n>>> Створення Арифметичної Прогресії (5 елементів):" << endl;
    ArithmeticProgression ap(5, 1.0, 2.0);
    ap.PrintSequence();

    cout << "Сума елементів: " << ap.GetSum() << endl;

    cout << "\n>>> Зміна параметрів (старт=10, крок=5):" << endl;
    ap.ChangeParams(10.0, 5.0);
    ap.PrintSequence();

    cout << "\n>>> Зміна розміру до 7 (виклик Resize класу ArithmeticProgression):" << endl;
    ap.Resize(7);
    ap.PrintSequence();

    cout << "\n>>> Тест конструктора копіювання:" << endl;
    ArithmeticProgression apCopy = ap;
    cout << "Копія:    "; apCopy.PrintSequence();

    // --- ТЕСТ 2: Послідовність Фібоначі ---
    cout << "\n>>> Створення Послідовності Фібоначі (10 елементів):" << endl;
    FibonacciSequence fib(10);
    fib.PrintSequence();

    cout << "Елемент [8]: " << fib.GetElementAt(8) << endl;
    cout << "Відношення [8]/[7]: " << fib.GetRatioToLeftNeighbor(8) << endl;

    cout << "\n>>> Зміна розміру до 12:" << endl;
    fib.Resize(12);
    fib.PrintSequence();

    cout << "\n>>> Завершення роботи." << endl;

    return 0;
}