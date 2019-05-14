#define WFB_RESAMPLE_SEGMENTS 64

struct InstVoltage
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
};

struct Vrms
{
    int32_t a;
    int32_t b;
    int32_t c;
};

struct Irms
{
    int32_t a;
    int32_t b;
    int32_t c;
};

struct InstCurrent
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
};

struct FilterBasedCurrent
{
        int32_t a;
        int32_t b;
        int32_t c;
        int32_t n;
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

struct FundamentalReactivePower
{
    int32_t a;
    int32_t b;
    int32_t c;
};

struct PowerFactor
{
    int32_t regA;
    int32_t regB;
    int32_t regC;
    double valA;
    double valB;
    double valC;
};

struct Period
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

struct ResampledWFB
{
    int16_t Ia[WFB_RESAMPLE_SEGMENTS];
    int16_t Va[WFB_RESAMPLE_SEGMENTS];

    int16_t Ib[WFB_RESAMPLE_SEGMENTS];
    int16_t Vb[WFB_RESAMPLE_SEGMENTS];

    int16_t Ic[WFB_RESAMPLE_SEGMENTS];
    int16_t Vc[WFB_RESAMPLE_SEGMENTS];

    int16_t In[WFB_RESAMPLE_SEGMENTS];

    int16_t Empty[WFB_RESAMPLE_SEGMENTS];
};

struct LastReads
{
    struct InstVoltage instVoltage;
    struct Vrms vrms;
    struct InstCurrent instCurrent;
    struct Irms irms;
    struct FilterBasedCurrent filterBasedCurrent;
    struct WattHours wattHours;
    struct InstApparentPower instApparentPower;
    struct InstActivePower instActivePower;
    struct InstReactivePower instReactivePower;
    struct FundamentalReactivePower fundReactPower;
    struct PowerFactor powerFactor;
    struct Period period;
    struct Peak peak;
    struct ResampledWFB resampledData;
};
