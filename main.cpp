#include "kup_bilet.h"
#include "parking.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]){

    wczytajBilety();

    QApplication a(argc, argv);
    Parking parking;
    Parkomat w;
    Cennik c;

    QObject::connect(&w, &Parkomat::exitCennik, &c, &Cennik::exitCennik);
    //QObject::connect(parking.kupBilet(), SIGNAL ((clicked)), &w, &Parkomat::show);

    for(QPushButton * przycisk: parking.miejsca_parkingowe){
        QObject::connect(przycisk, &QPushButton::clicked, &w, &Parkomat::show);
        QObject::connect(przycisk, &QPushButton::clicked, &c, &Cennik::show);
    }

    parking.show();
//    c.show();
//    w.show();
    return a.exec();
}

