#include "logcard.h"
#include "mapcontroller.h"
#include <QPalette>
#include <QWebEngineSettings>
#include <QFrame>
#include <QDebug>
#include <QWebChannel>
#include <QDialog>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDateTime>

LogCard::LogCard(const LogData &logData, QWidget *parent)
    : QWidget(parent), logData(logData), mainLayout(new QVBoxLayout(this)),
    mapView(new QWebEngineView(this)), boldLabel(new QLabel(this)),
    additionalTextLabel(new QLabel(this)), moreInfoButton(new QPushButton("More Info", this)) {
    setupUi();
    applyStyles();
}

void LogCard::setupUi() {
    // Create a frame to hold the content and apply rounded corners
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::NoFrame);
    QPalette mainPalette = this->palette();
    QColor backgroundColor = mainPalette.color(QPalette::Window);
    frame->setStyleSheet(QString("background-color: %1; border-radius: 15px;")
                             .arg(backgroundColor.name()));

    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

    // Configure the map view
    mapView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    mapView->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    mapView->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    mapView->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    mapView->setUrl(QUrl::fromLocalFile("/Users/mohammedalzuaa/Documents/HAN University Of Applied Sciences/Project/GitHub/laughing-fishstick/App/RGCCompApp/map.html"));

    mapView->setMinimumHeight(200);
    mapView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mapView->setStyleSheet("border-top-left-radius: 15px; border-top-right-radius: 15px;");

    frameLayout->addWidget(mapView);

    // Set up the map controller and web channel
    MapController *controller = new MapController(this);
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("controller"), controller);
    mapView->page()->setWebChannel(channel);

    connect(controller, &MapController::runJavaScript, [this](const QString &script) {
        mapView->page()->runJavaScript(script, [](const QVariant &result) {
            qDebug() << "JavaScript execution result:" << result;
            if (result.isValid()) {
                qDebug() << "JavaScript execution succeeded:" << result.toString();
            } else {
                qDebug() << "JavaScript execution failed";
            }
        });
    });

    // Configure the bold text label
    boldLabel->setText(QString::fromStdString(logData.getUserName()));
    QFont boldFont = boldLabel->font();
    boldFont.setBold(true);
    boldLabel->setFont(boldFont);
    boldLabel->setAlignment(Qt::AlignLeft); // Left-align the bold label
    frameLayout->addWidget(boldLabel);

    // Configure the additional text label
    additionalTextLabel->setText("Score: 1245p");
    QPalette additionalTextPalette = additionalTextLabel->palette();
    additionalTextPalette.setColor(QPalette::WindowText, QColor(255, 255, 255, 128)); // Less visible
    additionalTextLabel->setPalette(additionalTextPalette);
    additionalTextLabel->setAlignment(Qt::AlignLeft); // Left-align the additional text label
    frameLayout->addWidget(additionalTextLabel);

    // Configure the "More Info" button
    QColor buttonColor = backgroundColor.darker(150); // Darker shade of the background color
    moreInfoButton->setStyleSheet(QString("background-color: %1; color: white; border-radius: 5px; padding: 8px 16px;")
                                      .arg(buttonColor.name()));
    connect(moreInfoButton, &QPushButton::clicked, this, &LogCard::onMoreInfoClicked);
    frameLayout->addWidget(moreInfoButton, 0, Qt::AlignLeft);

    // Add frame to the main layout
    mainLayout->addWidget(frame);
    setLayout(mainLayout);
}

void LogCard::applyStyles() {
    // Set the background color to match the main window's palette
    QPalette palette = this->palette();
    QColor backgroundColor = palette.color(QPalette::Window);
    palette.setColor(QPalette::Window, backgroundColor);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void LogCard::onMoreInfoClicked() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("More Information");

    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);

    // Create a time-temperature graph using Qt Charts
    QLineSeries *series = new QLineSeries();

    // Example temperature data
    QList<QPointF> temperatureData = {
        QPointF(0, 20.5), QPointF(1, 21.0), QPointF(2, 19.8),
        QPointF(3, 22.1), QPointF(4, 23.4), QPointF(5, 25.0),
        QPointF(6, 24.5), QPointF(7, 23.9), QPointF(8, 22.0)
    };

    for (const QPointF &point : temperatureData) {
        series->append(point);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Time-Temperature Graph");
    chart->createDefaultAxes();

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time");
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Temperature (°C)");
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800,400);
    dialogLayout->addWidget(chartView);

    dialog->setLayout(dialogLayout);
    dialog->exec();
}