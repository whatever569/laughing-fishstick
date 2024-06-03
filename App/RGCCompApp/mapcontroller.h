#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <QDebug>

class MapController : public QObject {
    Q_OBJECT
public:
    explicit MapController(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void addMarker(double lat, double lon, const QString &color) {
        QString jsCode = QString("window.addMarker(%1, %2, '%3');").arg(lat).arg(lon).arg(color);
        emit runJavaScript(jsCode);
        qDebug() << "JavaScript code for addMarker:" << jsCode;
    }

    void drawPolyline(const QVariantList &coordinates) {
        QStringList coordStrs;
        for (const QVariant &coord : coordinates) {
            const QVariantList &pair = coord.toList();
            coordStrs << QString("[%1, %2]").arg(pair[0].toDouble()).arg(pair[1].toDouble());
        }
        QString jsCode = QString("window.drawPolyline([%1]);").arg(coordStrs.join(", "));
        emit runJavaScript(jsCode);
        qDebug() << "JavaScript code for drawPolyline:" << jsCode;
    }

signals:
    void runJavaScript(const QString &script);
};

#endif // MAPCONTROLLER_H
