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
    FragmentSequence();
    FragmentSequence(int n);
    FragmentSequence(const FragmentSequence& other);

    // ВАЖЛИВО: Віртуальний деструктор
    // (гарантує правильне очищення пам'яті при видаленні через вказівник на base)
    virtual ~FragmentSequence();

    // ВАЖЛИВО: Поліморфний метод згідно варіанту 6
    // (Визначення елемента за його порядковим номером)
    virtual double GetElementAt(int index);

    // Інші методи
    virtual void Resize(int newSize);
    int GetSize() const;
    void PrintSequence() const;
};

// ==========================================
// ПОХІДНИЙ КЛАС 1: Арифметична прогресія
// ==========================================
class ArithmeticProgression : public FragmentSequence {
private:
    double startElement;
    double step;

    void Generate(); // Внутрішня логіка

public:
    ArithmeticProgression();
    ArithmeticProgression(int n, double start, double s);
    ArithmeticProgression(const ArithmeticProgression& other);

    // Специфічні методи нащадка
    void ChangeParams(double newStart, double newStep);
    double GetSum() const;

    // Перевизначення (override) віртуальних методів
    double GetElementAt(int index) override;
    void Resize(int newSize) override;
};

// ==========================================
// ПОХІДНИЙ КЛАС 2: Послідовність Фібоначі
// ==========================================
class FibonacciSequence : public FragmentSequence {
private:
    void Generate();

public:
    FibonacciSequence();
    FibonacciSequence(int n);
    FibonacciSequence(const FibonacciSequence& other);

    // Специфічний метод нащадка
    double GetRatioToLeftNeighbor(int index) const;

    // Перевизначення (override) віртуальних методів
    double GetElementAt(int index) override;
    void Resize(int newSize) override;
};

#endif // SEQUENCE_HPP