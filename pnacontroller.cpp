#include "pnacontroller.h"

pnaController::pnaController(structSetting * settingInfoPtrArg)
{
    settingInfoPtr      = settingInfoPtrArg;
    // Initialize the COM subsystem
    CoInitialize(NULL);
    CoInitializeSecurity( NULL, 0, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS, 0, 0, 0);
    // Request the NA's IUnknown interface
    // Create an instance of the network analyzer
    hr = CoCreateInstance(CLSID_Application,0,CLSCTX_ALL, IID_IUnknown, (void**) &pUnk);

}

pnaController::~pnaController()
{
    CoUninitialize();
}

void pnaController::configure()
{
    IUnknown* pUnk = 0;
    IApplication* pNA = 0;
    IChannel* pChan = 0;
    IMeasurement* pMeas = 0;
    IGating* pGate = 0;
    IGating2* pGate2 = 0;
    HRESULT hr;

    CoInitialize(NULL);
    CoInitializeSecurity( NULL, 0, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS, 0, 0, 0);
    // Request the NA's IUnknown interface
    // Create an instance of the network analyzer
    hr = CoCreateInstance(CLSID_Application,0,CLSCTX_ALL, IID_IUnknown, (void**) &pUnk);

    if (!FAILED(hr))
    {
    // QueryInterface for the INetworkAnalyzer interface of the NetworkAnalyzer object
        hr = pUnk->QueryInterface(IID_IApplication,(void**)&pNA);
        if (!FAILED(hr))
        {
            // Reset the analyzer to instrument preset
            pNA->Reset();

            // Create measurement
            pNA->CreateSParameter(1,1,1,1);
            pNA->CreateSParameter(1,2,1,2);
            pNA->CreateSParameter(1,1,2,3);
            pNA->CreateSParameter(1,2,2,4);

            // Set pChan variable to point to the active channel
            pNA->get_ActiveChannel(&pChan);

        if (pChan)
        {
            // Setup the channel for a single trigger
            pNA->TriggerSignal = naTriggerManual;
            pChan->TriggerMode = naTriggerModeMeasurement;

            // Set channel parameters

            pChan->NumberOfPoints = settingInfoPtr->PnaSweepPoints;
            pChan->StartFrequency = GHz(settingInfoPtr->PnaStartFreq);
            pChan->StopFrequency = GHz(settingInfoPtr->PnaStopFreq);

            // Set pMeas variable to point to the active measurement
            pNA->get_ActiveMeasurement(&pMeas);

        if(pMeas)
        {
            // Make the PNA application visible
            pNA->put_Visible(true);

            // Set pGate variable to point to the active Gating
            pMeas->get_Gating(&pGate);
            hr = pGate->QueryInterface(IID_IGating2,(void**)&pGate2);

        if(!FAILED(hr))
        {
            //trigger
            pChan->Single(true);

            // Set Gating parameters
            pGate2->put_CoupledParameters((long) 15);

            // Gating shape index to char
            switch(settingInfoPtr->GatingShapeindex)
            {
            case 0:
                pGate->Shape = naGateShapeMaximum;
                break;
            case 1:
                pGate->Shape = naGateShapeWide;
                break;
            case 2:
                pGate->Shape = naGateShapeNormal;
                break;
            case 3:
                pGate->Shape = naGateShapeMinimum;
                break;
            }
            pGate->Span = nsec(settingInfoPtr->GatingSpan);
            pGate->Center = nsec(settingInfoPtr->GatingCenter);
            pGate->put_State(true);

            //trigger
            //pChan->Single(true);
        }
        }
        }
            pUnk->Release();
            pMeas->Release();
            pChan->Release();
            pNA->Release();
            pGate->Release();
            pGate2->Release();
        }
    }
CoUninitialize();
}

void pnaController::saveData_Air()
{

    IUnknown* pUnk = 0;
    IApplication* pNA = 0;
    IApplication18* pNA18 =0;
    IChannel* pChan = 0;
    long selector =-1;

    HRESULT hr;

    // Initialize the COM subsystem
    CoInitialize(NULL);
    CoInitializeSecurity( NULL, 0, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS, 0, 0, 0);

    // Create an instance of the network analyzer
    // Request the NA's IUnknown interface
    hr = CoCreateInstance(CLSID_Application,0,CLSCTX_ALL, IID_IUnknown, (void**) &pUnk);
    if (!FAILED(hr))
    {
    // QueryInterface for the INetworkAnalyzer interface of the NetworkAnalyzer object
        hr = pUnk->QueryInterface(IID_IApplication,(void**)&pNA);
        if (!FAILED(hr))
        {
            pNA->get_ActiveChannel(&pChan);

        if (pChan)
        {
            pChan->Single(true);
            hr = pNA ->QueryInterface(IID_IApplication18, (void**)&pNA18);
            //qDebug()<<"temperature"<<settingInfoPtr->StdTemperature<<endl;
            //path = "c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/";
            //path = path+settingInfoPtr->StdTemperature;
            //"c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/Air"

            sprintf(Temp,"%f",settingInfoPtr->StdTemperature);

            if (!FAILED(hr))
            {
                pNA18->raw_SaveData((_bstr_t)"c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/Air", (_bstr_t)"CSV Formatted Data", (_bstr_t)"Displayed", (_bstr_t)"RI", selector);
            }
            pUnk->Release();
            pNA->Release();
            pNA18->Release();
            pChan->Release();
        }
        }
 }
 CoUninitialize();
}

void pnaController::saveData_Metal()
{

    IUnknown* pUnk = 0;
    IApplication* pNA = 0;
    IApplication18* pNA18 =0;
    IChannel* pChan = 0;
    long selector =-1;

    HRESULT hr;

    // Initialize the COM subsystem
    CoInitialize(NULL);
    CoInitializeSecurity( NULL, 0, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS, 0, 0, 0);

    // Create an instance of the network analyzer
    // Request the NA's IUnknown interface
    hr = CoCreateInstance(CLSID_Application,0,CLSCTX_ALL, IID_IUnknown, (void**) &pUnk);
    if (!FAILED(hr))
    {
    // QueryInterface for the INetworkAnalyzer interface of the NetworkAnalyzer object
        hr = pUnk->QueryInterface(IID_IApplication,(void**)&pNA);
        if (!FAILED(hr))
        {
            pNA->get_ActiveChannel(&pChan);

        if (pChan)
        {
            pChan->Single(true);
            hr = pNA ->QueryInterface(IID_IApplication18, (void**)&pNA18);

            if (!FAILED(hr))
            {
                pNA18->raw_SaveData((_bstr_t)"c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/Metal.csv", (_bstr_t)"CSV Formatted Data", (_bstr_t)"Displayed", (_bstr_t)"RI", selector);
            }
            pUnk->Release();
            pNA->Release();
            pNA18->Release();
            pChan->Release();
        }
        }
 }
 CoUninitialize();
}
