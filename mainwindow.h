#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <pnacontroller.h>
#include <structdef.h>
#include <QDebug>

#include <QMainWindow>
#include <QMessageBox>
#include "qtextedit.h"
#include <QScrollArea>
#include <QShortcut>
#include "vfw.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void saveData();
    void on_pushButtonConfigure_clicked();
    void on_pushButtonSave_Air_clicked();
    void on_pushButtonSave_Metal_clicked();

    void on_enumPnaSweepPoints_currentIndexChanged(int index);
    void UpdateSettingParStruct();
    void UpdateSettingStandardParStruct();

private:
    Ui::MainWindow *ui;

    pnaController* pnaProc;
    structSetting settingInfo;

    void LoadComboBoxLists();
    void InitSettingPars();
};

#endif // MAINWINDOW_H
