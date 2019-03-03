struct InstVoltage
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
};

struct Vrms
{
    double a;
    double b;
    double c;
};

struct Irms
{
    double a;
    double b;
    double c;
};

struct InstCurrent
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
};

struct WattHours
{
    double a;
    double b;
    double c;
};

struct InstApparentPower
{
    int32_t a;
    int32_t b;
    int32_t c;
};

struct InstActivePower
{
        int32_t a;
        int32_t b;
        int32_t c;
};

struct InstReactivePower
{
        int32_t a;
        int32_t b;
        int32_t c;
};

struct Peak
{
    uint32_t Vpeak;
    uint32_t Ipeak;
};

struct LastReads
{
    struct InstVoltage instVoltage;
    struct Vrms vrms;
    struct InstCurrent instCurrent;
    struct Irms irms;
    struct WattHours wattHours;
    struct InstApparentPower instApparentPower;
    struct InstActivePower instActivePower;
    struct InstReactivePower instReactivePower;
    struct Peak peak;
};
