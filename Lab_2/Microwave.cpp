#include "Microwave.hpp"

void Microwave::Init()
{
    Power = false;
    RadiatorOn = false;
    HeaterOn = false;
    DoorOpen = false;
    CurrentMode = MICRO;
    MicroPower = 800;
    Timer = 0;
}

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
    if (m != MICRO && m != GRILL)
        return;

    if (RadiatorOn || HeaterOn) return; 
    CurrentMode = m;
}

void Microwave::SetPower(int p)
{
    if (RadiatorOn || HeaterOn) return;

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
}

void Microwave::SetTimer(int seconds)
{
    if (seconds >= 10 && seconds <= 3600)
        Timer = seconds;
    if (seconds < 10 || seconds > 3600)
        return;
}

void Microwave::StartHeating()
{
    if (Timer == 0 || Power == false) return;

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
    if (RadiatorOn || HeaterOn) {
        RadiatorOn = false;
        HeaterOn = false;
    }
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

int Microwave::GetCurrentPower() const
{
    if (CurrentMode == MICRO)
        return MicroPower;
    else
        return GrillPower;
}

