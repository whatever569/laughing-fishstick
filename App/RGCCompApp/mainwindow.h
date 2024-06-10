#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <appinitgamedata.h>
#include <vector>
#include <sstream>
#include <QString>
#include <string>
#include "QDoubleValidator"
#include "appwaypoint.h"
#include <iomanip>
#include <appinitgamedata.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_amountOfWaypointsSpinBox_valueChanged(int arg1);

    void on_userNameLineEdit_textChanged(const QString &arg1);

    void on_wayPointSelector_currentIndexChanged(int index);

    void on_latLineEdit_editingFinished();

    void on_longLineEdit_editingFinished();
    void on_wayPointPuzzleSelect_currentIndexChanged(int index);

    void on_recheckConnectionButton_clicked();

private:
    Ui::MainWindow *ui;

    void enableStuffAfterWaypointSpinBox(bool t);
    APPInitGameData initGameData;
    const int invalidCoordinateMessageTimeout = 5000;
    bool isValidLatitude(const std::string& str);
    bool isValidLongitude(const std::string& str);
    bool isValidFloat(const std::string& str);
    int tempWaypointIndex;
    bool boxIsConnected;
    void DataCompleteCheck();
};
#endif // MAINWINDOW_H

