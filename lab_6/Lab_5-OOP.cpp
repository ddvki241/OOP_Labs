#include "sequence.hpp"
#include <iostream>

using namespace std;

// === FragmentSequence (Базовий) ===

FragmentSequence::FragmentSequence() : size(0), data(nullptr) {}

FragmentSequence::FragmentSequence(int n) : size(n) {
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = 0.0;
    }
    else {
        data = nullptr;
        size = 0;
    }
}

FragmentSequence::FragmentSequence(const FragmentSequence& other) : size(other.size) {
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
    else {
        data = nullptr;
    }
}

FragmentSequence::~FragmentSequence() {
    if (data) delete[] data;
    cout << "[Base] Destructor called" << endl;
}

// Базова реалізація поліморфного методу
double FragmentSequence::GetElementAt(int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    cout << "Error: Index out of bounds (Base)" << endl;
    return 0.0;
}

void FragmentSequence::Resize(int newSize) {
    if (data) delete[] data;
    size = newSize;
    if (size > 0) {
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = 0.0;
    }
    else {
        data = nullptr;
    }
}

int FragmentSequence::GetSize() const { return size; }

void FragmentSequence::PrintSequence() const {
    cout << "[ ";
    for (int i = 0; i < size; ++i) cout << data[i] << " ";
    cout << "]" << endl;
}

// === ArithmeticProgression ===

void ArithmeticProgression::Generate() {
    if (size > 0 && data) {
        for (int i = 0; i < size; ++i) data[i] = startElement + i * step;
    }
}

ArithmeticProgression::ArithmeticProgression() : FragmentSequence(), startElement(0), step(0) {}

ArithmeticProgression::ArithmeticProgression(int n, double start, double s)
    : FragmentSequence(n), startElement(start), step(s) {
    Generate();
}

ArithmeticProgression::ArithmeticProgression(const ArithmeticProgression& other)
    : FragmentSequence(other), startElement(other.startElement), step(other.step) {
}

void ArithmeticProgression::ChangeParams(double newStart, double newStep) {
    startElement = newStart;
    step = newStep;
    Generate();
}

double ArithmeticProgression::GetSum() const {
    double sum = 0;
    for (int i = 0; i < size; ++i) sum += data[i];
    return sum;
}

// Поліморфний метод: повертає значення (для прогресії логіка така ж, як у бази, але явно вказуємо)
double ArithmeticProgression::GetElementAt(int index) {
    // Можна додати специфічну перевірку, але поки користуємося даними масиву
    if (index >= 0 && index < size) return data[index];
    return 0.0;
}

void ArithmeticProgression::Resize(int newSize) {
    FragmentSequence::Resize(newSize);
    Generate();
}

// === FibonacciSequence ===

void FibonacciSequence::Generate() {
    if (size > 0 && data) {
        if (size >= 1) data[0] = 0;
        if (size >= 2) data[1] = 1;
        for (int i = 2; i < size; ++i) data[i] = data[i - 1] + data[i - 2];
    }
}

FibonacciSequence::FibonacciSequence() : FragmentSequence() {}

FibonacciSequence::FibonacciSequence(int n) : FragmentSequence(n) {
    Generate();
}

FibonacciSequence::FibonacciSequence(const FibonacciSequence& other) : FragmentSequence(other) {}

double FibonacciSequence::GetRatioToLeftNeighbor(int index) const {
    if (index > 0 && index < size && data[index - 1] != 0) {
        return data[index] / data[index - 1];
    }
    return 0.0;
}

double FibonacciSequence::GetElementAt(int index) {
    if (index >= 0 && index < size) return data[index];
    return 0.0;
}

void FibonacciSequence::Resize(int newSize) {
    FragmentSequence::Resize(newSize);
    Generate();
}
