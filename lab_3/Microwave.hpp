#pragma once

#include <iostream>

enum Mode { MICRO = 0, GRILL = 1 };

class Microwave
{
private:
    bool Power;
    bool RadiatorOn;
    bool HeaterOn;
    bool DoorOpen;

    Mode CurrentMode;
    int MicroPower;
    int GrillPower;
    int Timer;

    void StopAll();

public:

    // === Конструктори ===
    Microwave();  // за замовчуванням
    Microwave(const Microwave& other); // копіювання
    Microwave(bool power, Mode mode, int microPower, int timer, bool door); // ініціалізація

    // === Деструктор ===
    ~Microwave();

    // === Методи ===
    void TurnOn();
    void TurnOff();
    void SetMode(Mode m);
    void SetTimer(int seconds);
    void StartHeating();
    void OpenDoor();
    void CloseDoor();
    double FinishHeating();

    // === Get ===
    bool GetPower() const;
    bool GetDoor() const;
    bool IsRadiatorOn() const;
    bool IsHeaterOn() const;
    int GetMicroPower() const;
    int GetTimer() const;
    Mode GetMode() const;
    int GetCurrentPower() const;
};
