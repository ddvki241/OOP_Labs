#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_5-OOP/sequence.hpp"
#include "../Lab_5-OOP/lab_5-OOP.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab5Test
{
	TEST_CLASS(SequenceTests)
	{
	public:

		// --- ТЕСТИ ДЛЯ АРИФМЕТИЧНОЇ ПРОГРЕСІЇ ---

		TEST_METHOD(TestArithmeticInitialization)
		{
			// Arrange: Створюємо прогресію: 5 елементів, старт 1.0, крок 2.0
			// Очікуємо: 1.0, 3.0, 5.0, 7.0, 9.0
			int size = 5;
			double start = 1.0;
			double step = 2.0;
			ArithmeticProgression ap(size, start, step);

			// Act & Assert
			// Assert::AreEqual(очікуване, реальне, допуск)
			Assert::AreEqual(1.0, ap.GetElementAt(0), 0.0001, L"Перший елемент має бути 1.0");
			Assert::AreEqual(5.0, ap.GetElementAt(2), 0.0001, L"Третій елемент має бути 5.0");
			Assert::AreEqual(9.0, ap.GetElementAt(4), 0.0001, L"Останній елемент має бути 9.0");
		}

		TEST_METHOD(TestArithmeticSum)
		{
			// Arrange: 1, 2, 3 (сума 6)
			ArithmeticProgression ap(3, 1.0, 1.0);

			// Act
			double sum = ap.GetSum();

			// Assert
			Assert::AreEqual(6.0, sum, 0.0001, L"Сума елементів 1+2+3 має бути 6.0");
		}

		TEST_METHOD(TestArithmeticChangeParams)
		{
			// Arrange
			ArithmeticProgression ap(3, 0.0, 0.0); // 0, 0, 0

			// Act: Змінюємо на старт 10, крок 5
			ap.ChangeParams(10.0, 5.0); // Має стати 10, 15, 20

			// Assert
			Assert::AreEqual(10.0, ap.GetElementAt(0), 0.0001);
			Assert::AreEqual(15.0, ap.GetElementAt(1), 0.0001);
		}

		// --- ТЕСТИ ДЛЯ ПОСЛІДОВНОСТІ ФІБОНАЧІ ---

		TEST_METHOD(TestFibonacciGeneration)
		{
			// Arrange: 7 елементів
			// Очікуємо: 0, 1, 1, 2, 3, 5, 8
			FibonacciSequence fib(7);

			// Assert
			Assert::AreEqual(0.0, fib.GetElementAt(0), 0.0001);
			Assert::AreEqual(1.0, fib.GetElementAt(1), 0.0001);
			Assert::AreEqual(1.0, fib.GetElementAt(2), 0.0001);
			Assert::AreEqual(5.0, fib.GetElementAt(5), 0.0001);
			Assert::AreEqual(8.0, fib.GetElementAt(6), 0.0001);
		}

		TEST_METHOD(TestFibonacciRatio)
		{
			// Arrange: Числа 0, 1, 1, 2, 3, 5, 8
			FibonacciSequence fib(7);

			// Act: Відношення 8 / 5 = 1.6
			double ratio = fib.GetRatioToLeftNeighbor(6);

			// Assert
			Assert::AreEqual(1.6, ratio, 0.0001, L"Відношення 8 до 5 має бути 1.6");
		}

		// --- ЗАГАЛЬНІ ТЕСТИ (Resize, Copy) ---

		TEST_METHOD(TestResize)
		{
			// Arrange
			ArithmeticProgression ap(2, 1.0, 1.0); // 1, 2

			// Act
			ap.Resize(4); // Має стати 1, 2, 3, 4

			// Assert
			Assert::AreEqual(4, ap.GetSize(), L"Розмір має стати 4");
			Assert::AreEqual(4.0, ap.GetElementAt(3), 0.0001, L"Четвертий елемент після ресайзу має бути 4.0");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// Arrange
			ArithmeticProgression original(3, 10.0, 10.0); // 10, 20, 30

			// Act
			ArithmeticProgression copy = original; // Виклик конструктора копіювання
			original.ChangeParams(0.0, 0.0); // Псуємо оригінал (0, 0, 0)

			// Assert
			// Копія має залишитися старою (10, 20, 30), якщо працює глибинне копіювання
			Assert::AreEqual(10.0, copy.GetElementAt(0), 0.0001, L"Копія не повинна змінитися при зміні оригіналу");
		}
	};
}
