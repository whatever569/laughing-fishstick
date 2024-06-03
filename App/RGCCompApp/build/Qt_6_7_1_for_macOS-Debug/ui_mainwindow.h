/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *homeTab;
    QGridLayout *gridLayout;
    QLabel *homeLabel;
    QWidget *newGameTab;
    QVBoxLayout *verticalLayout_2;
    QLabel *isDataCompleteLabel;
    QLineEdit *userNameLineEdit;
    QSpinBox *amountOfWaypointsSpinBox;
    QComboBox *wayPointSelector;
    QLineEdit *latLineEdit;
    QLineEdit *longLineEdit;
    QComboBox *wayPointPuzzleSelect;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *waypointStatusTextEdit;
    QPushButton *newGameButton;
    QSpacerItem *verticalSpacer;
    QWidget *logsTab;
    QVBoxLayout *verticalLayout_3;
    QListWidget *logsListWidget;
    QWidget *userManualTab;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(221, 201, 239, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(247, 245, 250, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(238, 228, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(111, 100, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(147, 134, 159, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush7(QColor(252, 233, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush8(QColor(182, 131, 251, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush8);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush10(QColor(0, 0, 0, 127));
        brush10.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        QBrush brush11(QColor(244, 237, 253, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Accent, brush11);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Accent, brush11);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush12(QColor(111, 100, 120, 127));
        brush12.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush12);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::Accent, brush11);
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush13(QColor(234, 178, 242, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush13);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush6);
        QBrush brush14(QColor(244, 216, 248, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush14);
        QBrush brush15(QColor(117, 89, 121, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush15);
        QBrush brush16(QColor(156, 119, 161, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush16);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush13);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette1.setBrush(QPalette::Active, QPalette::Accent, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush15);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush16);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush10);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Accent, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush16);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush17(QColor(117, 89, 121, 127));
        brush17.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush17);
#endif
        QBrush brush18(QColor(254, 247, 255, 255));
        brush18.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Accent, brush18);
        tabWidget->setPalette(palette1);
        QFont font;
        font.setFamilies({QString::fromUtf8("SF Mono")});
        font.setWeight(QFont::DemiBold);
        font.setItalic(false);
        font.setKerning(true);
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideRight);
        tabWidget->setTabBarAutoHide(false);
        homeTab = new QWidget();
        homeTab->setObjectName("homeTab");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("SF Mono")});
        font1.setBold(true);
        font1.setItalic(false);
        font1.setKerning(true);
        homeTab->setFont(font1);
        gridLayout = new QGridLayout(homeTab);
        gridLayout->setObjectName("gridLayout");
        homeLabel = new QLabel(homeTab);
        homeLabel->setObjectName("homeLabel");
        QPalette palette2;
        QBrush brush19(QColor(56, 52, 46, 255));
        brush19.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush19);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush19);
        homeLabel->setPalette(palette2);
        homeLabel->setAutoFillBackground(false);
        homeLabel->setAlignment(Qt::AlignCenter);
        homeLabel->setWordWrap(true);

        gridLayout->addWidget(homeLabel, 0, 0, 1, 1);

        tabWidget->addTab(homeTab, QString());
        newGameTab = new QWidget();
        newGameTab->setObjectName("newGameTab");
        verticalLayout_2 = new QVBoxLayout(newGameTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        isDataCompleteLabel = new QLabel(newGameTab);
        isDataCompleteLabel->setObjectName("isDataCompleteLabel");
        isDataCompleteLabel->setAutoFillBackground(false);
        isDataCompleteLabel->setTextFormat(Qt::AutoText);

        verticalLayout_2->addWidget(isDataCompleteLabel);

        userNameLineEdit = new QLineEdit(newGameTab);
        userNameLineEdit->setObjectName("userNameLineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userNameLineEdit->sizePolicy().hasHeightForWidth());
        userNameLineEdit->setSizePolicy(sizePolicy);
        userNameLineEdit->setMinimumSize(QSize(179, 21));
        userNameLineEdit->setMaximumSize(QSize(179, 21));
        userNameLineEdit->setMaxLength(16);
        userNameLineEdit->setClearButtonEnabled(false);

        verticalLayout_2->addWidget(userNameLineEdit);

        amountOfWaypointsSpinBox = new QSpinBox(newGameTab);
        amountOfWaypointsSpinBox->setObjectName("amountOfWaypointsSpinBox");
        sizePolicy.setHeightForWidth(amountOfWaypointsSpinBox->sizePolicy().hasHeightForWidth());
        amountOfWaypointsSpinBox->setSizePolicy(sizePolicy);
        amountOfWaypointsSpinBox->setMinimumSize(QSize(179, 20));
        amountOfWaypointsSpinBox->setMaximumSize(QSize(179, 21));
        amountOfWaypointsSpinBox->setMaximum(10);

        verticalLayout_2->addWidget(amountOfWaypointsSpinBox);

        wayPointSelector = new QComboBox(newGameTab);
        wayPointSelector->setObjectName("wayPointSelector");
        wayPointSelector->setEnabled(false);
        sizePolicy.setHeightForWidth(wayPointSelector->sizePolicy().hasHeightForWidth());
        wayPointSelector->setSizePolicy(sizePolicy);
        wayPointSelector->setMinimumSize(QSize(230, 20));
        wayPointSelector->setMaximumSize(QSize(230, 21));

        verticalLayout_2->addWidget(wayPointSelector);

        latLineEdit = new QLineEdit(newGameTab);
        latLineEdit->setObjectName("latLineEdit");
        latLineEdit->setEnabled(false);
        sizePolicy.setHeightForWidth(latLineEdit->sizePolicy().hasHeightForWidth());
        latLineEdit->setSizePolicy(sizePolicy);
        latLineEdit->setMinimumSize(QSize(179, 0));
        latLineEdit->setMaximumSize(QSize(179, 16777215));
        latLineEdit->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        verticalLayout_2->addWidget(latLineEdit);

        longLineEdit = new QLineEdit(newGameTab);
        longLineEdit->setObjectName("longLineEdit");
        longLineEdit->setEnabled(false);
        longLineEdit->setMinimumSize(QSize(179, 0));
        longLineEdit->setMaximumSize(QSize(179, 16777215));

        verticalLayout_2->addWidget(longLineEdit);

        wayPointPuzzleSelect = new QComboBox(newGameTab);
        wayPointPuzzleSelect->setObjectName("wayPointPuzzleSelect");
        wayPointPuzzleSelect->setEnabled(false);
        sizePolicy.setHeightForWidth(wayPointPuzzleSelect->sizePolicy().hasHeightForWidth());
        wayPointPuzzleSelect->setSizePolicy(sizePolicy);
        wayPointPuzzleSelect->setMinimumSize(QSize(230, 21));
        wayPointPuzzleSelect->setMaximumSize(QSize(16777215, 21));
        wayPointPuzzleSelect->setEditable(false);

        verticalLayout_2->addWidget(wayPointPuzzleSelect);

        scrollArea_2 = new QScrollArea(newGameTab);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 728, 119));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        waypointStatusTextEdit = new QTextEdit(scrollAreaWidgetContents_2);
        waypointStatusTextEdit->setObjectName("waypointStatusTextEdit");
        waypointStatusTextEdit->setReadOnly(true);

        verticalLayout_6->addWidget(waypointStatusTextEdit);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea_2);

        newGameButton = new QPushButton(newGameTab);
        newGameButton->setObjectName("newGameButton");
        newGameButton->setEnabled(false);
        newGameButton->setMinimumSize(QSize(179, 0));
        newGameButton->setMaximumSize(QSize(179, 16777215));

        verticalLayout_2->addWidget(newGameButton, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(newGameTab, QString());
        logsTab = new QWidget();
        logsTab->setObjectName("logsTab");
        verticalLayout_3 = new QVBoxLayout(logsTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        logsListWidget = new QListWidget(logsTab);
        logsListWidget->setObjectName("logsListWidget");

        verticalLayout_3->addWidget(logsListWidget);

        tabWidget->addTab(logsTab, QString());
        userManualTab = new QWidget();
        userManualTab->setObjectName("userManualTab");
        verticalLayout_4 = new QVBoxLayout(userManualTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        scrollArea = new QScrollArea(userManualTab);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 728, 486));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");

        verticalLayout_5->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        tabWidget->addTab(userManualTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        homeLabel->setText(QCoreApplication::translate("MainWindow", "Game In Progress: None. Start new game with the new game tab or look at past games in the logs tab.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(homeTab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        isDataCompleteLabel->setText(QCoreApplication::translate("MainWindow", "Data Not Complete Yet", nullptr));
#if QT_CONFIG(tooltip)
        userNameLineEdit->setToolTip(QCoreApplication::translate("MainWindow", "Maximum length of 16 characters", nullptr));
#endif // QT_CONFIG(tooltip)
        userNameLineEdit->setText(QString());
        userNameLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "User Name (Max.: 16)", nullptr));
#if QT_CONFIG(tooltip)
        amountOfWaypointsSpinBox->setToolTip(QCoreApplication::translate("MainWindow", "How many waypoints do you want for the game", nullptr));
#endif // QT_CONFIG(tooltip)
        amountOfWaypointsSpinBox->setPrefix(QCoreApplication::translate("MainWindow", "Waypoints: ", nullptr));
#if QT_CONFIG(tooltip)
        wayPointSelector->setToolTip(QCoreApplication::translate("MainWindow", "Select the waypoint that you want to edit", nullptr));
#endif // QT_CONFIG(tooltip)
        wayPointSelector->setPlaceholderText(QCoreApplication::translate("MainWindow", "Select Waypoint To Edit", nullptr));
#if QT_CONFIG(tooltip)
        latLineEdit->setToolTip(QCoreApplication::translate("MainWindow", "Use decimal degrees in the following format: Correct: 41.40338, 2.17403. Incorrect: 41,40338, 2,17403.", nullptr));
#endif // QT_CONFIG(tooltip)
        latLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Latitude", nullptr));
#if QT_CONFIG(tooltip)
        longLineEdit->setToolTip(QCoreApplication::translate("MainWindow", "Use decimal degrees in the following format: Correct: 41.40338, 2.17403. Incorrect: 41,40338, 2,17403.", nullptr));
#endif // QT_CONFIG(tooltip)
        longLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Longitude", nullptr));
#if QT_CONFIG(tooltip)
        wayPointPuzzleSelect->setToolTip(QCoreApplication::translate("MainWindow", "Choose the puzzle to be played at the waypoint", nullptr));
#endif // QT_CONFIG(tooltip)
        wayPointPuzzleSelect->setPlaceholderText(QCoreApplication::translate("MainWindow", "Waypoint Puzzle", nullptr));
        waypointStatusTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'SF Mono'; font-size:13pt; font-weight:600; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        newGameButton->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newGameTab), QCoreApplication::translate("MainWindow", "New Game", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(logsTab), QCoreApplication::translate("MainWindow", "Logs", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(userManualTab), QCoreApplication::translate("MainWindow", "User Manual", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
