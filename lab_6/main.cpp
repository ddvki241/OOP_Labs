#include <iostream>
#include <windows.h>
#include "sequence.hpp"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Ukr");

    cout << "=== ЛАБОРАТОРНА РОБОТА No6 (Варіант 6: Поліморфізм) ===\n" << endl;

    // Оголошуємо вказівник на базовий клас
    FragmentSequence* polyPointer = nullptr;

    // --- Сценарій 1: Працюємо як з Арифметичною прогресією ---
    cout << ">>> Створення Арифметичної прогресії (динамічно)..." << endl;
    // new ArithmeticProgression(...) повертає вказівник, який ми зберігаємо в polyPointer
    polyPointer = new ArithmeticProgression(5, 1.0, 2.0); // 1, 3, 5, 7, 9

    polyPointer->PrintSequence();

    cout << "Демонстрація поліморфного методу GetElementAt(2):" << endl;
    // Викликається метод саме класу ArithmeticProgression, хоча вказівник типу FragmentSequence*
    cout << "Значення: " << polyPointer->GetElementAt(2) << endl;

    cout << "Видалення об'єкта..." << endl;
    delete polyPointer; // Тут спрацює віртуальний деструктор ArithmeticProgression -> FragmentSequence
    polyPointer = nullptr;


    // --- Сценарій 2: Працюємо як з Послідовністю Фібоначі ---
    cout << "\n>>> Створення Послідовності Фібоначі (динамічно)..." << endl;
    polyPointer = new FibonacciSequence(8); // 0, 1, 1, 2, 3, 5, 8, 13

    polyPointer->PrintSequence();

    cout << "Демонстрація поліморфного методу GetElementAt(6):" << endl;
    // Тепер той самий рядок коду викликає метод класу FibonacciSequence
    cout << "Значення: " << polyPointer->GetElementAt(6) << endl;

    cout << "Видалення об'єкта..." << endl;
    delete polyPointer;
    polyPointer = nullptr;

    cout << "\n>>> Робота завершена." << endl;
    return 0;
}
