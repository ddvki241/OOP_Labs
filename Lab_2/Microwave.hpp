#ifndef MICROWAVE_HPP
#define MICROWAVE_HPP

enum Mode { MICRO, GRILL };

class Microwave
{
private:
    bool Power;
    bool RadiatorOn;
    bool HeaterOn;
    bool DoorOpen;

    Mode CurrentMode;

    int MicroPower;
    const int GrillPower = 1000;

    int Timer;

    // приватний метод: вимикає всі пристрої
    void StopAll();

public:
    void Init();

    // Методи доступу
    bool GetPower() const { return Power; }
    bool GetDoor() const { return DoorOpen; }
    bool IsRadiatorOn() const { return RadiatorOn; }
    bool IsHeaterOn() const { return HeaterOn; }
    Mode GetMode() const { return CurrentMode; }
    int GetCurrentPower() const;
    int GetMicroPower() const { return MicroPower; }
    int GetTimer() const { return Timer; }

    // Основні методи
    void TurnOn();
    void TurnOff();

    void SetMode(Mode m);
    void SetPower(int p);
    void SetTimer(int seconds);

    void StartHeating();
    void OpenDoor();
    void CloseDoor();

    double FinishHeating(); // повертає кВт·год
};
#endif
#pragma once
