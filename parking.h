#ifndef PARKING_H
#define PARKING_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QRect>
#include <QString>

class Parking: public QMainWindow{
    Q_OBJECT
private:
    QPushButton * disabled;
    QPushButton * disabled2;
    void miejsceParkingowe(const QRect& pole, const QString& nazwa);
public:
    QList<QPushButton*> miejsca_parkingowe;
    explicit Parking(QWidget * parent = nullptr);
public slots:

signals:

};

#endif // PARKING_H
