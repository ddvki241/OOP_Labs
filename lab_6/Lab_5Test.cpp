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

		TEST_METHOD(TestPolymorphismArithmetic)
		{
			// Arrange
			// Створюємо вказівник на БАЗОВИЙ клас
			FragmentSequence* polyPointer = new ArithmeticProgression(5, 1.0, 2.0);
			// Очікувана послідовність: 1.0, 3.0, 5.0, 7.0, 9.0

			// Act
			// Викликаємо метод через базовий вказівник
			double val0 = polyPointer->GetElementAt(0);
			double val2 = polyPointer->GetElementAt(2);

			// Assert
			Assert::AreEqual(1.0, val0, 0.0001, L"Елемент [0] має бути 1.0");
			Assert::AreEqual(5.0, val2, 0.0001, L"Елемент [2] має бути 5.0");

			// Cleanup
			delete polyPointer; // Перевірка, що віртуальний деструктор не крашить програму
		}

		// Тест 2: Перевірка поліморфізму для Фібоначі
		TEST_METHOD(TestPolymorphismFibonacci)
		{
			// Arrange
			// Створюємо вказівник на БАЗОВИЙ клас
			FragmentSequence* polyPointer = new FibonacciSequence(8);
			// Очікувана послідовність: 0, 1, 1, 2, 3, 5, 8, 13

			// Act
			double val5 = polyPointer->GetElementAt(5); // Має бути 5
			double val7 = polyPointer->GetElementAt(7); // Має бути 13

			// Assert
			Assert::AreEqual(5.0, val5, 0.0001, L"Елемент [5] має бути 5.0");
			Assert::AreEqual(13.0, val7, 0.0001, L"Елемент [7] має бути 13.0");

			// Cleanup
			delete polyPointer;
		}

		// Тест 3: Перевірка методу Resize через поліморфізм
		TEST_METHOD(TestPolymorphismResize)
		{
			// Arrange
			FragmentSequence* polyPointer = new ArithmeticProgression(2, 10.0, 10.0); // 10, 20

			// Act
			// Викликаємо Resize через базовий вказівник. 
			// Якщо віртуальні функції працюють, має викликатися ArithmeticProgression::Resize
			// і перегенерувати дані.
			polyPointer->Resize(4); // Має стати: 10, 20, 30, 40

			// Assert
			Assert::AreEqual(4, polyPointer->GetSize(), L"Розмір має змінитись на 4");
			Assert::AreEqual(40.0, polyPointer->GetElementAt(3), 0.0001, L"Новий елемент має бути згенерований");

			delete polyPointer;
		}

		// Тест 4: Перевірка на вихід за межі масиву (Base implementation logic check)
		TEST_METHOD(TestOutOfBounds)
		{
			FragmentSequence* polyPointer = new FibonacciSequence(3); // 0, 1, 1

			// Спроба взяти 100-й елемент
			double errorVal = polyPointer->GetElementAt(100);

			// Очікуємо 0.0 (так прописано в нашому коді для помилки)
			Assert::AreEqual(0.0, errorVal, 0.0001, L"При виході за межі має повертатись 0.0");

			delete polyPointer;
		}
		TEST_METHOD(TestArithmeticSpecificMethods)
		{
			// Створюємо об'єкт конкретного класу
			ArithmeticProgression ap(5, 0.0, 5.0); // 0, 5, 10, 15, 20

			// Перевіряємо суму (метод GetSum є тільки в ArithmeticProgression)
			Assert::AreEqual(50.0, ap.GetSum(), 0.0001, L"Сума має бути 50.0");

			// Змінюємо параметри
			ap.ChangeParams(1.0, 1.0); // 1, 2, 3, 4, 5
			Assert::AreEqual(15.0, ap.GetSum(), 0.0001, L"Сума після зміни параметрів має бути 15.0");
		}

		// Тест 6: Перевірка специфічного методу GetRatio (Фібоначі)
		TEST_METHOD(TestFibonacciSpecificMethods)
		{
			FibonacciSequence fib(10); // ... 8, 13, 21, 34 ...

			// Перевіряємо золотий перетин на більших числах (34 / 21)
			double ratio = fib.GetRatioToLeftNeighbor(9);
			// 34 / 21 = 1.61904...
			Assert::AreEqual(1.619, ratio, 0.001, L"Відношення F9/F8 має бути ~1.619");
		}

		// Тест 7: Перевірка Resize на 0 (Очищення)
		TEST_METHOD(TestResizeToZero)
		{
			FragmentSequence* polyPointer = new ArithmeticProgression(5, 1.0, 1.0);

			// Зменшуємо розмір до 0
			polyPointer->Resize(0);

			Assert::AreEqual(0, polyPointer->GetSize(), L"Розмір має стати 0");

			// Спроба отримати елемент з порожнього масиву має бути безпечною (повернути 0.0)
			double val = polyPointer->GetElementAt(0);
			Assert::AreEqual(0.0, val, 0.0001, L"Доступ до елемента при size=0 має повертати 0.0");

			delete polyPointer;
		}

		// Тест 8: Перевірка від'ємного індексу
		TEST_METHOD(TestNegativeIndex)
		{
			FragmentSequence* polyPointer = new FibonacciSequence(5);

			// Спроба доступу за індексом -1
			double val = polyPointer->GetElementAt(-1);

			Assert::AreEqual(0.0, val, 0.0001, L"Індекс -1 має повертати помилку (0.0)");

			delete polyPointer;
		}

		// Тест 9: Перевірка конструктора копіювання через базовий клас
		// Це складніший тест, бо конструктор копіювання не віртуальний.
		// Ми перевіряємо, чи правильно копіюється об'єкт конкретного класу.
		TEST_METHOD(TestDeepCopyArithmetic)
		{
			// Arrange
			ArithmeticProgression original(3, 10.0, 10.0); // 10, 20, 30

			// Act
			ArithmeticProgression copy = original; // Копіюємо
			original.ChangeParams(0.0, 0.0);       // "Ламаємо" оригінал -> 0, 0, 0

			// Assert
			// Копія повинна залишитися 10, 20, 30
			Assert::AreEqual(10.0, copy.GetElementAt(0), 0.0001);
			Assert::AreEqual(20.0, copy.GetElementAt(1), 0.0001);
			Assert::AreEqual(30.0, copy.GetElementAt(2), 0.0001);
		}

		// Тест 10: Перевірка динамічного приведення типів (dynamic_cast)
		// Перевіряємо, чи дійсно вказівник вказує на правильний тип об'єкта
		TEST_METHOD(TestDynamicCast)
		{
			FragmentSequence* basePtr = new FibonacciSequence(5);

			// Спроба привести до ArithmeticProgression має провалитися (вернути nullptr)
			ArithmeticProgression* apPtr = dynamic_cast<ArithmeticProgression*>(basePtr);
			Assert::IsNull(apPtr, L"Вказівник на Fibonacci не має приводитись до Arithmetic");

			// Спроба привести до FibonacciSequence має вдатися
			FibonacciSequence* fibPtr = dynamic_cast<FibonacciSequence*>(basePtr);
			Assert::IsNotNull(fibPtr, L"Вказівник має успішно привестись до Fibonacci");

			delete basePtr;
		}
	};
}
