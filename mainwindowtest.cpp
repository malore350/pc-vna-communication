#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //connect(ui->pushButtonSave,SIGNAL(pressed()),this,SLOT(saveData()));

    //Combo boxes
    LoadComboBoxLists();

    //Initialize setting parameters
    InitSettingPars(); // The init settings should be loaded from the last settings used.
    pnaProc = new pnaController((structSetting *)&settingInfo);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::saveData()
{
    pnaProc->saveData();
}
*/


void MainWindow::on_pushButtonConfigure_clicked()
{
    UpdateSettingParStruct();
    pnaProc->configure();
}

void MainWindow::LoadComboBoxLists()
{
    QStringList listPlaySpeed,listMeasType;

    ui->enumPnaSweepPoints->addItem("51");
    ui->enumPnaSweepPoints->addItem("201");
    ui->enumPnaSweepPoints->addItem("401");
    ui->enumPnaSweepPoints->addItem("801");

    ui->enumGatingShape->addItem("S11");
    ui->enumGatingShape->addItem("S12");
    ui->enumGatingShape->addItem("S21");
    ui->enumGatingShape->addItem("S22");

}

void MainWindow::InitSettingPars()
{
    //initialize frequency
    ui->lineEditPnaStartFreq->setText("8.2");
    ui->lineEditPnaStopFreq->setText("12.4");

    //initialize time
    ui->lineEditTimeStart->setText("-10");
    ui->lineEditTimeStop->setText("50");

    //initialize combobox
    ui->enumPnaSweepPoints->setCurrentIndex(3);
    ui->enumGatingShape->setCurrentIndex(0);
    UpdateSettingParStruct();
}

void MainWindow::UpdateSettingParStruct()
{
    settingInfo.PnaStartFreq       = ui->lineEditPnaStartFreq->text().toDouble();
    settingInfo.PnaStopFreq        = ui->lineEditPnaStopFreq->text().toDouble() ;
    settingInfo.PnaSweepPoints     = ui->enumPnaSweepPoints->currentText().toLong() ;

    settingInfo.TimeStart          = ui->lineEditTimeStart->text().toDouble() ;
    settingInfo.TimeStop           = ui->lineEditTimeStop->text().toDouble() ;
    settingInfo.GatingShapeindex   = ui->enumGatingShape->currentIndex() ;
}


void MainWindow::on_enumPnaSweepPoints_currentIndexChanged(int index)
{
    UpdateSettingParStruct();
    //if (pnaProc!=NULL)
    //pnaProc->configS11Meas();
}










