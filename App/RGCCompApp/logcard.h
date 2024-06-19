 #ifndef LOGCARD_HPP
#define LOGCARD_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QWebEngineView>

#include "QtWidgets/qpushbutton.h"
#include "logdata.h"

class LogCard : public QWidget {
    Q_OBJECT

public:
    explicit LogCard(const LogData &logData, QWidget *parent = nullptr);

private slots:
    void onMoreInfoClicked();

private:
    LogData logData;
    QVBoxLayout *mainLayout;
    QWebEngineView *mapView;
    QLabel *boldLabel;
    QLabel *additionalTextLabel;
    QPushButton *moreInfoButton;

    void setupUi();
    void applyStyles();
};

#endif // LOGCARD_HPP

