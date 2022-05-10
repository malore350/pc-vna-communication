#ifndef PNACONTROLLER_H
#define PNACONTROLLER_H

#include <stdio.h>
#include "atlbase.h"
#include "objbase.h"
#include <iostream>
#include "combaseapi.h"
#include "structDef.h"
#include <QDebug>
#include <string.h>

using namespace std;


#import "C:/Program Files (x86)/Common Files/Agilent/Network Analyzer/835x.tlb" no_namespace, named_guids

class pnaController : public QObject
{
    Q_OBJECT

public:
    explicit pnaController(structSetting * settingInfoPtrArg);
    ~pnaController();

public slots:
    void configure();
    void saveData_Air();
    void saveData_Metal();

private:
    IUnknown* pUnk = 0;
    IApplication* pNA = 0;
    IApplication18* pNA18 =0;
    IChannel* pChan = 0;
    IMeasurement* pMeas = 0;
    IGating* pGate = 0;
    IGating2* pGate2 = 0;
    long selector =-1;
    HRESULT hr;
    structSetting * settingInfoPtr = NULL;

    char* floderpath = "c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/";
    char path[10];
    char Temp[10];

};







#endif // PNACONTROLLER_H
