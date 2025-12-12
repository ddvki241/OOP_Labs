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
			m.Init();

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
			m.Init();

			m.TurnOn();
			Assert::IsTrue(m.GetPower());
			Assert::AreEqual((int)MICRO, (int)m.GetMode());
			Assert::AreEqual(800, m.GetMicroPower());
			Assert::AreEqual(0, m.GetTimer());
		}
		TEST_METHOD(TestIfTurnOffWorksProperly)
			{
			Microwave m;
			m.Init();

			m.TurnOn();
			m.TurnOff();
			Assert::IsFalse(m.GetPower());
			Assert::IsFalse(m.IsHeaterOn());
			Assert::IsFalse(m.IsRadiatorOn());
		}

		TEST_METHOD(TestChangeSetModeIfHeatingOff)
		{
			Microwave m;
			m.Init();
			
			m.SetMode(GRILL);
			Assert::AreEqual((int)GRILL, (int)m.GetMode());
		}
		TEST_METHOD(TestNotChangeSetModeIfHeatingOn)
		{
			Microwave m;
			m.Init();
			
			m.TurnOn();	
			m.SetMode(GRILL);
			m.SetTimer(100);
			m.StartHeating();

			m.SetMode(MICRO);
			Assert::AreEqual((int)GRILL, (int)m.GetMode());
		}

		TEST_METHOD(TestSetPower)
		{
			Microwave m;
			m.Init();

			// Валідні значення
			m.SetPower(160);
			Assert::AreEqual(160, m.GetMicroPower());

			m.SetPower(800);
			Assert::AreEqual(800, m.GetMicroPower());

			// Некоректне значення — ігнор
			m.SetPower(123);
			Assert::AreEqual(160, m.GetMicroPower());

			// Під час нагріву змінювати не можна
			m.TurnOn();
			m.SetTimer(100);
			m.StartHeating();
			m.SetPower(160);
			Assert::AreEqual(800, m.GetMicroPower());
		}

		TEST_METHOD(TestSetTimerIfNormal)
		{
			Microwave m;
			m.Init();

			m.SetTimer(100);
			Assert::AreEqual(100, m.GetTimer());

			m.SetTimer(3600);
			Assert::AreEqual(3600, m.GetTimer());
		}
		TEST_METHOD(TestSetTimerIfLess)
		{
			Microwave m;
			m.Init();

			m.SetTimer(5);
			Assert::AreEqual(0, m.GetTimer());
		}
		TEST_METHOD(TestSetTimerIfMore)
		{
			Microwave m;
			m.Init();

			m.SetTimer(4000);
			Assert::AreEqual(0, m.GetTimer());
		}

		TEST_METHOD(TestOpenDoorWorksProperly)
		{
			Microwave m;
			m.Init();
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
			m.Init();
			m.TurnOn();
			m.SetTimer(100);
			m.StartHeating();

			Assert::IsTrue(m.IsRadiatorOn() || m.IsHeaterOn());

			m.CloseDoor();
			Assert::IsFalse(m.IsRadiatorOn());
			Assert::IsFalse(m.IsHeaterOn());
			Assert::IsFalse(m.GetDoor());
		}

		TEST_METHOD(TestIfFinishHeatingWorksProperly)
		{
			Microwave m;
			m.Init();
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
}
