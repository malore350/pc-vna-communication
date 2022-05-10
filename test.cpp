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
    IApplication18* pNA18 = 0;
    IChannel* pChan = 0;
    INAWindow* pNAW=0;
    IMeasurement* pMeas = 0;
    IArrayTransfer* pTrans = 0;
    ITransform* pTran =0;
    long selector =-1;
    HRESULT hr;

    // Initialize the COM subsystem
    CoInitialize(NULL);
    CoInitializeSecurity( NULL, 0, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE,RPC_C_IMP_LEVEL_ANONYMOUS, 0, 0, 0);

    // Create an instance of the network analyzer
    // Request the NA's IUnknown interface
    hr = CoCreateInstance(CLSID_Application,0,CLSCTX_ALL, IID_IUnknown, (void**) &pUnk);

    //Up to this all is right

    if (!FAILED(hr))
    {
        // QueryInterface for the INetworkAnalyzer interface of the NetworkAnalyzer object
        hr = pUnk->QueryInterface(IID_IApplication,(void**)&pNA);
        if (!FAILED(hr))
        {
            // Reset the analyzer to instrument preset
            pNA->Reset();

            // Create S11 measurement
            switch(settingInfoPtr->GatingShapeindex)
            {
                case 0:
                    pNA->CreateSParameter(1,1,1,1);
                    break;
                case 1:
                    pNA->CreateSParameter(1,1,2,1);
                    break;
                case 2:
                    pNA->CreateSParameter(1,2,1,1);
                    break;
                case 3:
                    pNA->CreateSParameter(1,2,2,1);
                    break;
            }

            // Set pChan variable to point to the active channel
            pNA->get_ActiveChannel(&pChan);

            if (pChan) {
                // Setup the channel for a single trigger
                pChan->Hold(true);
                pNA->TriggerSignal = naTriggerManual;
                pChan->TriggerMode = naTriggerModeMeasurement;

                // Set channel parameters
                pChan->NumberOfPoints = settingInfoPtr->PnaSweepPoints;
                pChan->StartFrequency = GHz(settingInfoPtr->PnaStartFreq);
                pChan->StopFrequency = GHz(settingInfoPtr->PnaStopFreq);

                // Set pMeas variable to point to the active measurement
                pNA->get_ActiveMeasurement(&pMeas);

                if (pMeas) {
                    // Make the PNA application visible

                    pNA->put_Visible(true);
                    //pNA->State(true);
                    pMeas->get_Transform(&pTran);
                    pTran->put_State(true);
                    // Send a manual trigger to initiate a single sweep
                    pChan->Single(true);
                    pTran->Start = nsec(settingInfoPtr->TimeStart); //change the values for start
                    pTran->Stop = nsec(settingInfoPtr->TimeStop);   //change the values for stop
                    hr = pMeas->QueryInterface(IID_IArrayTransfer, (void **) &pTrans);


                    //QueryInterface(IID_IArrayTransfer, (void**)&pTrans);
                    if (!FAILED(hr)) {
                        pMeas->get_NAWindow(&pNAW);
                        pNAW->AutoScale(); //for autoscaling, this and upper line
                        hr = pNA->QueryInterface(IID_IApplication18, (void **) &pNA18);
                        pNA18->raw_SaveData((_bstr_t) "c:/Users/PNA-ADMIN/Desktop/HTcalibrationdata/S11.csv",
                                            (_bstr_t) "CSV Formatted Data", (_bstr_t) "Displayed", (_bstr_t) "RI",
                                            selector);

                        //pWin -> get_ActiveTrace(&pTrace);


                    }
                    pUnk->Release();
                    pMeas->Release();
                    pChan->Release();
                    pTrans->Release();
                    pNA->Release();
                    pNA18->Release();
                }
            }
        }
    }
    CoUninitialize();
}
