#include "pch.h"
#include "CppUnitTest.h"
#include "..\Microwave\Microwave.hpp"
#include "..\Microwave\Microwave.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MicrovaweTest
{
	TEST_CLASS(MicrovaweTest)
	{
	public:

		TEST_METHOD(TestInit)
		{
			Microwave m;
			Microwave();

			Assert::IsFalse(m.GetPower());
			Assert::IsFalse(m.IsRadiatorOn());
			Assert::IsFalse(m.IsHeaterOn());
			Assert::IsFalse(m.GetDoor());
			Assert::AreEqual(800, m.GetMicroPower());
			Assert::AreEqual((int)MICRO, (int)m.GetMode());
			Assert::AreEqual(0, m.GetTimer());
		}
		TEST_METHOD(TestIfTurnOnWorksProperly)
		{
			Microwave m;
			Microwave();

			m.TurnOn();
			Assert::IsTrue(m.GetPower());
			Assert::AreEqual((int)MICRO, (int)m.GetMode());
			Assert::AreEqual(800, m.GetMicroPower());
			Assert::AreEqual(0, m.GetTimer());
		}
		TEST_METHOD(TestIfTurnOffWorksProperly)
			{
			Microwave m;
			Microwave();

			m.TurnOn();
			m.TurnOff();
			Assert::IsFalse(m.GetPower());
			Assert::IsFalse(m.IsHeaterOn());
			Assert::IsFalse(m.IsRadiatorOn());
		}

		TEST_METHOD(TestChangeSetModeIfHeatingOff)
		{
			Microwave m;
			Microwave();
			
			m.SetMode(GRILL);
			Assert::AreEqual((int)GRILL, (int)m.GetMode());
		}
		TEST_METHOD(TestNotChangeSetModeIfHeatingOn)
		{
			Microwave m;
			Microwave();
			
			m.TurnOn();	
			m.SetMode(GRILL);
			m.SetTimer(100);
			m.StartHeating();

			m.SetMode(MICRO);
			Assert::AreEqual((int)GRILL, (int)m.GetMode());
		}

		TEST_METHOD(TestInitializationPowerConfiguration)
		{
			// --- Валідні значення ---
			Microwave m1(true, MICRO, 160, 0, false);
			Assert::AreEqual(160, m1.GetMicroPower());

			Microwave m2(true, MICRO, 800, 0, false);
			Assert::AreEqual(800, m2.GetMicroPower());

			// --- Некоректні значення → мають нормалізуватися ---
			Microwave m3(true, MICRO, 123, 0, false);
			Assert::AreEqual(160, m3.GetMicroPower()); // нормалізація вниз

			Microwave m4(true, MICRO, 9999, 0, false);
			Assert::AreEqual(800, m4.GetMicroPower()); // нормалізація вверх

			// --- Перевірка що під час "нагріву" потужність все одно не змінюється ---
			Microwave m5(true, MICRO, 320, 100, false);
			m5.StartHeating();

			// якщо спробувати змінити — нічого не зміниться, бо SetPower() більше не існує
			Assert::AreEqual(320, m5.GetMicroPower());
		}
		TEST_METHOD(TestSetTimerIfNormal)
		{
			Microwave m;
			Microwave();

			m.SetTimer(100);
			Assert::AreEqual(100, m.GetTimer());

			m.SetTimer(3600);
			Assert::AreEqual(3600, m.GetTimer());
		}
		TEST_METHOD(TestSetTimerIfLess)
		{
			Microwave m;
			Microwave();

			m.SetTimer(5);
			Assert::AreEqual(0, m.GetTimer());
		}
		TEST_METHOD(TestSetTimerIfMore)
		{
			Microwave m;
			Microwave();

			m.SetTimer(4000);
			Assert::AreEqual(0, m.GetTimer());
		}

		TEST_METHOD(TestOpenDoorWorksProperly)
		{
			Microwave m;
			Microwave();
			m.TurnOn();
			m.SetTimer(100);
			m.StartHeating();

			Assert::IsTrue(m.IsRadiatorOn() || m.IsHeaterOn(), L"Assert 1");

			m.OpenDoor();

			Assert::IsFalse(m.IsRadiatorOn(), L"Assert 2");
			Assert::IsFalse(m.IsHeaterOn(), L"Assert 3");
			Assert::IsTrue(m.GetDoor(), L"Assert 4");
		}

		TEST_METHOD(TestIfCloseDoorWorksProperly)
		{
			Microwave m;
			Microwave();
			m.TurnOn();
			m.SetTimer(100);
			m.StartHeating();

			Assert::IsTrue(m.IsRadiatorOn() || m.IsHeaterOn(), L"Assert 1");

			m.CloseDoor();
			Assert::IsFalse(m.IsRadiatorOn(), L"Assert 2");
			Assert::IsFalse(m.IsHeaterOn(), L"Assert 3");
			Assert::IsFalse(m.GetDoor(), L"Assert 4");
		}

		TEST_METHOD(TestIfFinishHeatingWorksProperly)
		{
			Microwave m;
			Microwave();
			m.TurnOn();
			m.SetTimer(120);
			m.StartHeating();
			Assert::IsTrue(m.IsRadiatorOn() || m.IsHeaterOn());

			double energy = m.FinishHeating();
			double expected = 800.0 * (120.0 / 3600.0) / 1000.0;
			Assert::AreEqual(expected, energy);

			Assert::IsFalse(m.IsRadiatorOn());
			Assert::IsFalse(m.IsHeaterOn());
		}
	};

	TEST_CLASS(ConstructorTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			Microwave m;

			Assert::IsFalse(m.GetPower());
			Assert::IsFalse(m.IsRadiatorOn());
			Assert::IsFalse(m.IsHeaterOn());
			Assert::IsFalse(m.GetDoor());
			Assert::AreEqual(800, m.GetMicroPower());
			Assert::AreEqual((int)MICRO, (int)m.GetMode());
			Assert::AreEqual(0, m.GetTimer());
		}

		TEST_METHOD(TestInitializationConstructor)
		{
			Microwave m(true, GRILL, 640, 120, true);

			Assert::IsTrue(m.GetPower());
			Assert::AreEqual((int)GRILL, (int)m.GetMode());
			Assert::AreEqual(640, m.GetMicroPower());
			Assert::AreEqual(120, m.GetTimer());
			Assert::IsTrue(m.GetDoor());
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Microwave original(true, MICRO, 320, 90, false);

			Microwave copy(original);

			Assert::AreEqual(original.GetPower(), copy.GetPower());
			Assert::AreEqual((int)original.GetMode(), (int)copy.GetMode());
			Assert::AreEqual(original.GetMicroPower(), copy.GetMicroPower());
			Assert::AreEqual(original.GetTimer(), copy.GetTimer());
			Assert::AreEqual(original.GetDoor(), copy.GetDoor());
		}

		TEST_METHOD(TestDefaultConstructorConsistency)
		{
			Microwave m1;
			Microwave m2;

			Assert::AreEqual(m1.GetPower(), m2.GetPower());
			Assert::AreEqual((int)m1.GetMode(), (int)m2.GetMode());
			Assert::AreEqual(m1.GetMicroPower(), m2.GetMicroPower());
			Assert::AreEqual(m1.GetTimer(), m2.GetTimer());
			Assert::AreEqual(m1.GetDoor(), m2.GetDoor());
		}

		TEST_METHOD(TestInitializationConstructorInvalidValues)
		{
			Microwave m(false, MICRO, -200, -50, true);

			// Потужність має нормалізуватися або залишитись за замовчуванням
			Assert::IsTrue(m.GetMicroPower() >= 160);

			// Таймер не може бути меншим за 0
			Assert::IsTrue(m.GetTimer() >= 0);
		}

		TEST_METHOD(TestCopyConstructorIndependence)
		{
			Microwave m1(true, MICRO, 320, 90, false);

			Microwave m2(m1); // копія

			// --- Змінюємо ОРИГІНАЛ ---
			// Створимо новий об'єкт і присвоїмо його (імітація зміни потужності)
			m1 = Microwave(true, MICRO, 640, 200, true);

			// --- Переконуємося, що копія НЕ змінилася ---
			Assert::AreEqual(320, m2.GetMicroPower());
			Assert::AreEqual(90, m2.GetTimer());
			Assert::IsFalse(m2.GetDoor());
		}


		TEST_METHOD(TestCopyConstructorDoorState)
		{
			Microwave m1(true, GRILL, 800, 120, true); // двері відкриті

			Microwave m2(m1);

			Assert::IsTrue(m2.GetDoor());
			Assert::AreEqual((int)GRILL, (int)m2.GetMode());
			Assert::AreEqual(800, m2.GetMicroPower());
			Assert::AreEqual(120, m2.GetTimer());
		}

		TEST_METHOD(TestCopyConstructorDoesNotStartHeating)
		{
			Microwave m1;
			m1.TurnOn();
			m1.SetTimer(100);
			m1.StartHeating();

			Microwave m2(m1);

			// Копія НЕ повинна починати нагрів
			Assert::IsFalse(m2.IsRadiatorOn());
			Assert::IsFalse(m2.IsHeaterOn());
		}

	};
}
