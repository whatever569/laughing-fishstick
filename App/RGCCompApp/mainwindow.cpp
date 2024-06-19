#include "mainwindow.h"
#include "logcard.h"
#include "ui_mainwindow.h"
#include "datapc.h"
#include "/Users/mohammedalzuaa/Documents/HAN University Of Applied Sciences/Project/GitHub/laughing-fishstick/source/GameData.h"
#include "/Users/mohammedalzuaa/Documents/HAN University Of Applied Sciences/Project/GitHub/laughing-fishstick/source/GPSLocation.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    initGameData = APPInitGameData();
    ui->setupUi(this);
    connect(ui->latLineEdit, SIGNAL(editingFinished()), this,SLOT(on_latLineEdit_editingFinished()));
    connect(ui->longLineEdit, SIGNAL(editingFinished()), this, SLOT(on_longLineEdit_editingFinished()));
    QString userManualText = R"(
    <html>
    <head>
        <style>
            body { font-family: Arial, sans-serif; }
            h1 { color: #2E8B57; }
            h2 { color: #4682B4; }
            p { margin: 10px 0; }
            .section-title { font-weight: bold; font-size: 1.2em; margin-top: 20px; }
        </style>
    </head>
    <body>
        <h1>User Manual</h1>
        <p>This user manual will tell you the steps of how to set up a game, play it and finish it.</p>

        <div class="section-title">Starting Up:</div>
        <p>Press the power button to start your Adventure. A message will open telling you to set up a game. This is done with the companion app, to learn more about setting up the game and the companion app, look at the end of this manual. Once a game is set up a QR code will appear. This QR code leads to this user manual. You can continue by pressing the button C. This starts up the game, now you can go and look for your first waypoint.</p>

        <div class="section-title">Finding Waypoints:</div>
        <p>To get help finding waypoints a help button can be pressed. Press button D to see what direction the next waypoint is, this direction is relative to north, so turn the compass up before you press this button. Additionally, each time this button is pressed, the final score decreases, so part of the game is to use it as few times as possible. When the user is within 25 meters of the waypoint, the screen will show if you are getting closer (hotter) and it will show (colder) if the user moves further away. If the user reaches the waypoint, the "Simon Says" puzzle appears.</p>

        <div class="section-title">Playing the Puzzle:</div>
        <p>Starting the Game: After displaying a tutorial for three seconds, the game offers control instructions for a couple of seconds. The game displays a series of directions (such as UP, DOWN, and LEFT) which the user has to imitate by remembering the correct sequence.</p>
        <p>The player uses the matching buttons (A for UP, B for LEFT, C for RIGHT, D for DOWN) to duplicate the sequence. If done correctly the game is passed and a higher score is obtained before moving on to the next waypoint, else the user gets penalized on score but still moves on to the next waypoint.</p>
        <p>Once each waypoint has been reached the game ends and the box opens to reveal the hidden treasure inside of it. Now the box can be returned to the companion app to get the final score and view the route that has been taken.</p>

        <div class="section-title">Battery Access</div>
        <p>The battery can be accessed by opening the battery access slider. Make sure to keep the battery charged for continuous use, for charging use a USB wire to charge it. If one wishes to change the batteries, make sure to pay extra attention to the poles of the batteries, copy the directions on the battery holder.</p>
    </body>
    </html>
)";

    ui->userManualTextEdit->setHtml(userManualText);
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
        ui->latLineEdit->setEnabled(false);
        ui->longLineEdit->setEnabled(false);
        ui->wayPointPuzzleSelect->setEnabled(false);
    }

    tempWaypointIndex = 0;
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
    boxIsConnected = IsConnectedToMc();
    qDebug()<<boxIsConnected;
    DataCompleteCheck();
}


void MainWindow::on_newGameButton_clicked()
{
    boxIsConnected = IsConnectedToMc();
    DataCompleteCheck();
    vector<GameData::WayPoint> wps;
    for(APPWaypoint &wp : initGameData.getWaypoints())
    {
        GameData::WayPoint twp;
        twp.setWayPoint(GPSLocation(wp.getLocation().getLat(), wp.getLocation().getLon()), GameData::SimonSays);
        wps.push_back(twp);
    }
    if(gameDataInit(initGameData.getUserName(), wps))
    {
        qDebug()<<&wps;
        ui->homeLabel->setText("Game In Progress: " + QString::fromStdString(initGameData.getUserName()));
        ui->newGameButton->setEnabled(false);
        ui->recheckConnectionButton->setEnabled(false);
        ui->isDataCompleteLabel->setEnabled(false);
        ui->latLineEdit->setEnabled(false);
        ui->longLineEdit->setEnabled(false);
        ui->userNameLineEdit->setEnabled(false);
        ui->waypointStatusTextEdit->setEnabled(false);
        ui->amountOfWaypointsSpinBox->setEnabled(false);
        ui->wayPointSelector->setEnabled(false);
        ui->wayPointPuzzleSelect->setEnabled(false);

    }
    else
    {
        ui->statusbar->showMessage("Data transfer to microcontroller failed unexpectedly", 5000);
    }
}


void MainWindow::on_getLogDataPushButton_clicked()
{
    if(IsConnectedToMc())
    {
        LogData ld = GameDataReturn();

        QListWidgetItem *item = new QListWidgetItem(ui->logsListWidget);
        LogCard *logCard = new LogCard(ld);
        item->setSizeHint(logCard->sizeHint());
        ui->logsListWidget->setItemWidget(item, logCard);
        initGameData = APPInitGameData();
        ui->homeLabel->setText("Game In Progress: None");
        ui->newGameButton->setEnabled(false);
        ui->recheckConnectionButton->setEnabled(true);
        DataCompleteCheck();
        ui->isDataCompleteLabel->setEnabled(true);
        ui->latLineEdit->setEnabled(false);
        ui->longLineEdit->setEnabled(false);
        ui->userNameLineEdit->setEnabled(true);
        ui->waypointStatusTextEdit->setEnabled(true);
        ui->amountOfWaypointsSpinBox->setEnabled(true);
        ui->wayPointSelector->setEnabled(false);
        ui->wayPointPuzzleSelect->setEnabled(false);
    }
}

