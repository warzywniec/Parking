#ifndef PARKING_H
#define PARKING_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QRect>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QRandomGenerator>
#include <QDialog>
#include <QVBoxLayout>
#include <QEventLoop>

class Disabled: public QDialog{
    Q_OBJECT

public:
    Disabled(QWidget * parent = nullptr);

};

class Parking: public QMainWindow{
    Q_OBJECT

private:
    QList<QRect> miejsca;
    QPushButton * disabled;
    QPushButton * disabled2;
    void miejsceParkingowe(const QRect& pole, const QString& nazwa, int random_number);

public:
    QList<QPushButton*> miejsca_parkingowe;
    QList<QLabel*> zajete_miejsca;
    explicit Parking(QWidget * parent = nullptr);
    void wczytajMiejsca();

private slots:
    void pokazDisabledInfo();

};

#endif // PARKING_H
