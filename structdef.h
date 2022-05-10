#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#define GHz(x) x*1e9
#define nsec(x) x*1e-9

#include <QString>

enum measType
{
    er      = 0,
    ei      = 1,
    ur      = 2,
    ui      = 3,
    s11Mag  = 4,
    s21Mag  = 5,
    noOfMeas= 6,
};

struct structSetting
{
    int scanHeight;
    int scanWidth;
    float scanInterval;
    int ScanPoints;
    int xLength;
    int yLength;

    double PnaStartFreq;
    double PnaStopFreq;
    long   PnaSweepPoints;
    double GatingCenter;
    double GatingSpan;
    int  GatingShapeindex;

    float StdTemperature;
    float StdThickness;

    double PnaFreqStepSize;
    float PnaPower;
    float PnaIFBW;
    float PnametalPlateThickness;
    float PnadistToSample;
    float PnasampleThickness;
    int selectedMeas;
};


#endif // STRUCTDEF_H
