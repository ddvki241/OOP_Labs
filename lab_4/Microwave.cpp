#include "Microwave.hpp"

// === КОНСТРУКТОР ЗА ЗАМОВЧУВАННЯМ ===
Microwave::Microwave()
{
    Power = false;
    RadiatorOn = false;
    HeaterOn = false;
    DoorOpen = false;

    CurrentMode = MICRO;
    MicroPower = 800;
    GrillPower = 1000;
    Timer = 0;
}

// === КОНСТРУКТОР КОПІЮВАННЯ ===
Microwave::Microwave(const Microwave& other)
{
    Power = other.Power;
    DoorOpen = other.DoorOpen;
    CurrentMode = other.CurrentMode;

    MicroPower = other.MicroPower;
    GrillPower = other.GrillPower;
    Timer = other.Timer;

    // КОПІЯ НЕ ПОВИННА НАГРІВАТИ
    RadiatorOn = false;
    HeaterOn = false;
}

// === КОНСТРУКТОР ІНІЦІАЛІЗАЦІЇ ===
Microwave::Microwave(bool power, Mode mode, int p, int timer, bool door)
{
    Power = power;
    DoorOpen = door;
    CurrentMode = mode;
    GrillPower = 1000;

    // НОРМАЛІЗАЦІЯ ПОТУЖНОСТІ

    if (p == 160 || p == 320 || p == 640 || p == 800)
        MicroPower = p;
    else if (p < 240)
        MicroPower = 160;
    else if (p < 480)
        MicroPower = 320;
    else if (p < 720)
        MicroPower = 640;
    else
        MicroPower = 800;

    // НОРМАЛІЗАЦІЯ ТАЙМЕРА
    if (timer >= 10 && timer <= 3600)
        Timer = timer;
    else
        Timer = 0;

    // НЕ ГРІЄМО ПРИ СТВОРЕННІ
    RadiatorOn = false;
    HeaterOn = false;
}

// === ДЕСТРУКТОР ===
Microwave::~Microwave() {}


// === ІНШІ МЕТОДИ ===

void Microwave::StopAll()
{
    RadiatorOn = false;
    HeaterOn = false;
}

void Microwave::TurnOn()
{
    Power = true;
    CurrentMode = MICRO;
    MicroPower = 800;
    Timer = 0;
    StopAll();
}

void Microwave::TurnOff()
{
    Power = false;
    StopAll();
}

void Microwave::SetMode(Mode m)
{
    if (RadiatorOn || HeaterOn) return;
    if (m == MICRO || m == GRILL)
        CurrentMode = m;
}

void Microwave::SetTimer(int seconds)
{
    if (seconds >= 10 && seconds <= 3600)
        Timer = seconds;
}

void Microwave::StartHeating()
{
    if (!Power || Timer == 0) return;

    if (CurrentMode == MICRO)
        RadiatorOn = true;
    else
        HeaterOn = true;
}

void Microwave::OpenDoor()
{
    StopAll();
    DoorOpen = true;
}

void Microwave::CloseDoor()
{
    DoorOpen = false;
    StopAll();
}

double Microwave::FinishHeating()
{
    double energy = 0.0;

    if (RadiatorOn)
        energy = (MicroPower / 1000.0) * (Timer / 3600.0);
    else if (HeaterOn)
        energy = (GrillPower / 1000.0) * (Timer / 3600.0);

    StopAll();
    Timer = 0;

    return energy;
}


// === GET ===
bool Microwave::GetPower() const { return Power; }
bool Microwave::GetDoor() const { return DoorOpen; }
bool Microwave::IsRadiatorOn() const { return RadiatorOn; }
bool Microwave::IsHeaterOn() const { return HeaterOn; }
int Microwave::GetMicroPower() const { return MicroPower; }
int Microwave::GetTimer() const { return Timer; }
Mode Microwave::GetMode() const { return CurrentMode; }

int Microwave::GetCurrentPower() const
{
    return (CurrentMode == MICRO ? MicroPower : GrillPower);
}

Microwave& Microwave::operator=(bool state)
{
    if (state)
        TurnOn();
    else
        TurnOff();
    return *this;
}

// Оператор "<<=" — встановлення потужності
int operator<<=(Microwave& m, int watts)
{
    if (m.RadiatorOn || m.HeaterOn)
        return m.MicroPower;

    if (watts < 240)      m.MicroPower = 160;
    else if (watts < 480) m.MicroPower = 320;
    else if (watts < 720) m.MicroPower = 640;
    else                  m.MicroPower = 800;

    return m.MicroPower;
}

// Оператор "^=" — встановлення часу
int operator^=(Microwave& m, int seconds)
{
    if (seconds >= 10 && seconds <= 3600)
        m.Timer = seconds;

    return m.Timer;
}
