#include "sequence.hpp"
#include <iostream>

using namespace std;

// ==========================================
// Реалізація: FragmentSequence
// ==========================================

FragmentSequence::FragmentSequence() : size(0), data(nullptr) {
}

FragmentSequence::FragmentSequence(int n) : size(n) {
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = 0.0;
    }
    else {
        data = nullptr;
        size = 0;
    }
    cout << "[Base] Init Constructor" << endl;
}

FragmentSequence::FragmentSequence(const FragmentSequence& other) : size(other.size) {
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    else {
        data = nullptr;
    }
    cout << "[Base] Copy Constructor" << endl;
}

FragmentSequence::~FragmentSequence() {
    if (data) {
        delete[] data;
    }
    cout << "[Base] Destructor" << endl;
}

void FragmentSequence::Resize(int newSize) {
    if (data) {
        delete[] data;
    }
    size = newSize;
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = 0.0;
    }
    else {
        data = nullptr;
    }
    cout << "[Base] Resize executed" << endl;
}

int FragmentSequence::GetSize() {
    return size;
}

void FragmentSequence::PrintSequence() {
    cout << "Sequence: [ ";
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << "]" << endl;
}

// ==========================================
// Реалізація: ArithmeticProgression
// ==========================================

void ArithmeticProgression::Generate() {
    if (size > 0 && data != nullptr) {
        for (int i = 0; i < size; ++i) {
            data[i] = startElement + i * step;
        }
    }
}

ArithmeticProgression::ArithmeticProgression()
    : FragmentSequence(), startElement(0), step(0) {
}

ArithmeticProgression::ArithmeticProgression(int n, double start, double s)
    : FragmentSequence(n), startElement(start), step(s) {
    Generate();
    cout << "[Arith] Init Constructor" << endl;
}

ArithmeticProgression::ArithmeticProgression(const ArithmeticProgression& other)
    : FragmentSequence(other), startElement(other.startElement), step(other.step) {
    cout << "[Arith] Copy Constructor" << endl;
}

void ArithmeticProgression::ChangeParams(double newStart, double newStep) {
    startElement = newStart;
    step = newStep;
    Generate();
}

double ArithmeticProgression::GetElementAt(int index) {
    if (index >= 0 && index < size) return data[index];
    return 0.0;
}

double ArithmeticProgression::GetSum() {
    double sum = 0;
    for (int i = 0; i < size; ++i) sum += data[i];
    return sum;
}

// У нащадку ми просто оголошуємо функцію з таким самим ім'ям.
// Це називається перекриттям імен (hiding), а не поліморфізмом.
void ArithmeticProgression::Resize(int newSize) {
    // Викликаємо метод базового класу явно, щоб виділити пам'ять
    FragmentSequence::Resize(newSize);
    // Додаткова логіка нащадка
    Generate();
    cout << "[Arith] Resize (re-generated)" << endl;
}

// ==========================================
// Реалізація: FibonacciSequence
// ==========================================

void FibonacciSequence::Generate() {
    if (size > 0 && data != nullptr) {
        if (size >= 1) data[0] = 0;
        if (size >= 2) data[1] = 1;
        for (int i = 2; i < size; ++i) {
            data[i] = data[i - 1] + data[i - 2];
        }
    }
}

FibonacciSequence::FibonacciSequence() : FragmentSequence() {}

FibonacciSequence::FibonacciSequence(int n) : FragmentSequence(n) {
    Generate();
    cout << "[Fibo] Init Constructor" << endl;
}

FibonacciSequence::FibonacciSequence(const FibonacciSequence& other)
    : FragmentSequence(other) {
    cout << "[Fibo] Copy Constructor" << endl;
}

double FibonacciSequence::GetElementAt(int index) {
    if (index >= 0 && index < size) return data[index];
    return 0.0;
}

double FibonacciSequence::GetRatioToLeftNeighbor(int index) {
    if (index > 0 && index < size) {
        if (data[index - 1] != 0) {
            return data[index] / data[index - 1];
        }
    }
    return 0.0;
}

void FibonacciSequence::Resize(int newSize) {
    FragmentSequence::Resize(newSize);
    Generate();
    cout << "[Fibo] Resize (re-generated)" << endl;
}
