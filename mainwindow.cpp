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


void MainWindow::on_pushButtonSave_Air_clicked()
{
    UpdateSettingStandardParStruct();
    pnaProc->saveData_Air();
}

void MainWindow::on_pushButtonSave_Metal_clicked()
{
    UpdateSettingStandardParStruct();
    pnaProc->saveData_Metal();
}

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

    ui->enumGatingShape->addItem("Maximum");
    ui->enumGatingShape->addItem("Wide");
    ui->enumGatingShape->addItem("Normal");
    ui->enumGatingShape->addItem("Minimum");

}

void MainWindow::InitSettingPars()
{
    //initialize frequency
    ui->lineEditPnaStartFreq->setText("8.2");
    ui->lineEditPnaStopFreq->setText("12.4");

    //initialize gating
    ui->lineEditGatingCenter->setText("28.3");
    ui->lineEditGatingSpan->setText("1");

    //initialize combobox
    ui->enumPnaSweepPoints->setCurrentIndex(3);
    ui->enumGatingShape->setCurrentIndex(2);
    UpdateSettingParStruct();

    //initialize Standard Saving
    ui->lineEditStdTemperature->setText("");
    ui->lineEditStdThickness->setText("");
}

void MainWindow::UpdateSettingParStruct()
{
    settingInfo.PnaStartFreq       = ui->lineEditPnaStartFreq->text().toDouble();
    settingInfo.PnaStopFreq        = ui->lineEditPnaStopFreq->text().toDouble() ;
    settingInfo.PnaSweepPoints     = ui->enumPnaSweepPoints->currentText().toLong() ;

    settingInfo.GatingCenter       = ui->lineEditGatingCenter->text().toDouble() ;
    settingInfo.GatingSpan         = ui->lineEditGatingSpan->text().toDouble() ;
    settingInfo.GatingShapeindex   = ui->enumGatingShape->currentIndex() ;
}

void MainWindow::UpdateSettingStandardParStruct()
{
    settingInfo.StdTemperature      = ui->lineEditStdTemperature->text().toFloat();
    settingInfo.StdThickness        = ui->lineEditStdThickness->text().toFloat() ;
}

void MainWindow::on_enumPnaSweepPoints_currentIndexChanged(int index)
{
   UpdateSettingParStruct();
   //if (pnaProc!=NULL)
    //pnaProc->configS11Meas();
}










