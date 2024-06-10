#include "mainwindow.h"
#include "logcard.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    initGameData = APPInitGameData();
    ui->setupUi(this);
    connect(ui->latLineEdit, SIGNAL(editingFinished()), this,SLOT(on_latLineEdit_editingFinished()));
    connect(ui->longLineEdit, SIGNAL(editingFinished()), this, SLOT(on_longLineEdit_editingFinished()));
    boxIsConnected = true; //CHANGE THIS WHEN YOU ADD THE BOX CONNECTION CODE
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_amountOfWaypointsSpinBox_valueChanged(int arg1)
{
    if(arg1 > 0)
    {
        enableStuffAfterWaypointSpinBox(true);
    }
    else
    {
        enableStuffAfterWaypointSpinBox(false);
    }

    ui->wayPointSelector->clear();
    initGameData.getWaypoints().clear();
    for(int i = 0; i < arg1; i++)
    {
        ostringstream oss;
        oss << "Waypoint: " << i + 1;
        ui->wayPointSelector->addItem(QString::fromStdString(oss.str()));
        initGameData.getWaypoints().push_back(APPWaypoint());
    }
    DataCompleteCheck();
    QListWidgetItem *item = new QListWidgetItem(ui->logsListWidget);
    LogCard *logCard = new LogCard(LogData());
    item->setSizeHint(logCard->sizeHint());
    ui->logsListWidget->setItemWidget(item, logCard);
}

void MainWindow::enableStuffAfterWaypointSpinBox(bool t)
{
    if(t)
    {
        ui->wayPointSelector->setEnabled(true);
    }
    else
    {
        ui->wayPointSelector->setEnabled(false);
    }
}

void MainWindow::on_userNameLineEdit_textChanged(const QString &arg1)
{
    initGameData.setUserName(arg1.toStdString());
    DataCompleteCheck();
}


void MainWindow::on_wayPointSelector_currentIndexChanged(int index)
{
    tempWaypointIndex = index;

    ui->latLineEdit->setEnabled(true);
    ui->longLineEdit->setEnabled(true);
    ui->wayPointPuzzleSelect->setEnabled(true);

    ui->wayPointPuzzleSelect->clear();
    ui->latLineEdit->clear();
    ui->longLineEdit->clear();
    for(int i = 0; i<static_cast<int>(COUNT); i++)
    {
        ostringstream oss;
        Puzzles puzzle = static_cast<Puzzles>(i);
        oss << getPuzzleName(puzzle);
        ui->wayPointPuzzleSelect->addItem(QString::fromStdString(oss.str()));
    }
    DataCompleteCheck();
}



void MainWindow::on_latLineEdit_editingFinished()
{
    qDebug() << "Lat line edit finished, checking input...";
    if(isValidLatitude(ui->latLineEdit->text().toStdString()))
    {
        qDebug() << "Latitude input is acceptable";
        initGameData.getWaypoints()[tempWaypointIndex].getLocation().setLat(ui->latLineEdit->text().toFloat());
    }else
    {
        qDebug() << "Latitude input is invalid";
        ui->statusbar->showMessage("Invalid latitude coordinate", invalidCoordinateMessageTimeout);
        ui->latLineEdit->clear();
    }
    DataCompleteCheck();
}


void MainWindow::on_longLineEdit_editingFinished()
{
    qDebug() << "Lon line edit finished, checking input...";
    if(isValidLongitude(ui->longLineEdit->text().toStdString()))
    {
        qDebug() << "Longitude input is acceptable";
        initGameData.getWaypoints()[tempWaypointIndex].getLocation().setLon(ui->longLineEdit->text().toFloat());
    }else
    {
        qDebug() << "Longitude input is invalid";
        ui->statusbar->showMessage("Invalid longitude coordinate", invalidCoordinateMessageTimeout);
        ui->longLineEdit->clear();
    }
    DataCompleteCheck();
}

bool MainWindow::isValidFloat(const std::string& str) {
    std::istringstream iss(str);
    float f;
    char c;
    if (!(iss >> f) || iss.get(c)) {
        return false; // Not a valid float
    }
    return true;
}

bool MainWindow::isValidLongitude(const std::string& str) {
    if (!isValidFloat(str)) {
        return false;
    }
    float longitude = std::stof(str);
    return longitude >= -180.0 && longitude <= 180.0;
}

bool MainWindow::isValidLatitude(const std::string& str) {
    if (!isValidFloat(str)) {
        return false;
    }
    float latitude = std::stof(str);
    return latitude >= -90.0 && latitude <= 90.0;
}

void MainWindow::on_wayPointPuzzleSelect_currentIndexChanged(int index)
{
    cout<<"index: " <<index <<endl;
    if(index == -1) {index = 1;}
    initGameData.getWaypoints()[tempWaypointIndex].setPuzzle(static_cast<Puzzles>(index));
    DataCompleteCheck();
}

void MainWindow::DataCompleteCheck()
{
    bool condition = initGameData.isDataComplete() && boxIsConnected;
    ui->newGameButton->setEnabled(condition);
    ui->isDataCompleteLabel->clear();
    if (condition)
    {
        ui->isDataCompleteLabel->setText("Data is complete and box is connected, press new game to start data transfer to the box.");
    }
    else
    {
        ui->isDataCompleteLabel->setText("Data isn't complete yet, set coordinates and puzzles for all waypoints and connect the box!");
    }

    QString waypointInfo;
    waypointInfo += "<h3 style='color: #8E44AD; margin-bottom: 10px;'>Waypoints data completion status</h3>";

    if (initGameData.getWaypoints().size() == 0)
    {
        waypointInfo += "<h4 style='color: #C0392B;'>Add some waypoints, there are none :(</h4>";
    }
    else
    {
        int counter = 1;
        for (APPWaypoint& wp : initGameData.getWaypoints())
        {
            QString latInfo;
            QString longInfo;
            QString status;

            if (wp.getLocation().getLat() == APPGPSLocation::defaultLatitude)
            {
                latInfo = "<span style='color: #E74C3C;'>UNINITIALIZED</span>";
            }
            else
            {
                latInfo = QString("&#x1F4CD; ") + QString::number(wp.getLocation().getLat(), 'f', 6);
            }

            if (wp.getLocation().getLon() == APPGPSLocation::defaultLongitude)
            {
                longInfo = "<span style='color: #E74C3C;'>UNINITIALIZED</span>";
            }
            else
            {
                longInfo = QString("&#x1F4CD; ") + QString::number(wp.getLocation().getLon(), 'f', 6);
            }

            if (wp.getIsComplete())
            {
                status = "<span style='color: #27AE60;'>Complete</span>";
            }
            else
            {
                status = "<span style='color: #D35400;'>Incomplete</span>";
            }

            waypointInfo += QString("<div style='padding: 10px; background-color: %1; border: 1px solid #EAECEE; margin-bottom: 10px;'>")
                                .arg((counter % 2 == 0) ? "#F8F9F9" : "#FBFCFC")
                            + QString("<p style='font-size: 14px; color: #5D6D7E; margin: 0 0 5px 0;'><strong>Waypoint %1</strong></p>").arg(counter)
                            + QString("<p style='margin: 0 0 5px 20px;'><strong>Coordinates:</strong> %1, %2</p>").arg(latInfo).arg(longInfo)
                            + QString("<ul style='margin: 0 0 0 20px;'>")
                            + QString("<li><strong>Puzzle:</strong> %1</li>").arg(QString::fromStdString(getPuzzleName(wp.getPuzzle())))
                            + QString("<li><strong>Status:</strong> %1</li>").arg(status)
                            + QString("</ul>")
                            + QString("</div>");
            counter++;
        }
    }

    ui->waypointStatusTextEdit->setHtml(waypointInfo);
}

void MainWindow::on_recheckConnectionButton_clicked()
{

}

