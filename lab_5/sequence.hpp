#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

// ==========================================
// БАЗОВИЙ КЛАС: Фрагмент послідовності
// ==========================================
class FragmentSequence {
protected:
    int size;       // Розмір
    double* data;   // Динамічне сховище значень

public:
    // Конструктори
    FragmentSequence();                             // За замовчуванням
    FragmentSequence(int n);                        // Ініціалізації
    FragmentSequence(const FragmentSequence& other);// Копіювання

    // Деструктор (не віртуальний, як у прикладі лаб. 5)
    ~FragmentSequence();

    // Методи
    void Resize(int newSize); // Зміна розміру
    int GetSize();
    void PrintSequence();     // Допоміжний вивід
};

// ==========================================
// ПОХІДНИЙ КЛАС 1: Арифметична прогресія
// ==========================================
class ArithmeticProgression : public FragmentSequence {
private:
    double startElement; // Початковий елемент
    double step;         // Крок

    // Допоміжний метод для заповнення масиву
    void Generate();

public:
    // Конструктори
    ArithmeticProgression();
    ArithmeticProgression(int n, double start, double s);
    ArithmeticProgression(const ArithmeticProgression& other);

    // Специфічні методи
    void ChangeParams(double newStart, double newStep);
    double GetElementAt(int index);
    double GetSum();

    // Перекриття методу базового класу (без virtual/override)
    void Resize(int newSize);
};

// ==========================================
// ПОХІДНИЙ КЛАС 2: Послідовність Фібоначі
// ==========================================
class FibonacciSequence : public FragmentSequence {
private:
    // Допоміжний метод для генерації чисел
    void Generate();

public:
    // Конструктори
    FibonacciSequence();
    FibonacciSequence(int n);
    FibonacciSequence(const FibonacciSequence& other);

    // Специфічні методи
    double GetElementAt(int index);
    double GetRatioToLeftNeighbor(int index);

    // Перекриття методу базового класу (без virtual/override)
    void Resize(int newSize);
};

#endif // SEQUENCE_HPP