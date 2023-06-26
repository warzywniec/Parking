#include "parking.h"

Parking::Parking(QWidget *parent): QMainWindow{parent}{

    setStyleSheet("QMainWindow { background-image: url(:/Parking.png);}");
//    QLabel * zdjontko = new QLabel(":/czerwony_samochodzik.jpg",this);
//    QPixmap pixmap(":/czerwony_samochodzik.jpg");
//    zdjontko->setPixmap(pixmap);
    miejsceParkingowe(QRect(0,0,132,200),"");
    miejsceParkingowe(QRect(144,0,150,200),"");
    miejsceParkingowe(QRect(306,0,139,200),"");
    miejsceParkingowe(QRect(457,0,132,200),"");
    miejsceParkingowe(QRect(742,0,131,200),"");
    miejsceParkingowe(QRect(885,0,150,200),"");
    miejsceParkingowe(QRect(1047,0,141,200),"");
    miejsceParkingowe(QRect(1200,0,150,200),"");
    miejsceParkingowe(QRect(0,400,132,200),"");
//    miejsceParkingowe(QRect(144,400,150,200),"");
//    miejsceParkingowe(QRect(306,400,139,200),"");
    miejsceParkingowe(QRect(457,400,132,200),"");
    miejsceParkingowe(QRect(742,400,131,200),"");
    miejsceParkingowe(QRect(885,400,150,200),"");
    miejsceParkingowe(QRect(1047,400,141,200),"");
    miejsceParkingowe(QRect(1200,400,150,200),"");
    disabled = new QPushButton("",this);
    disabled->setGeometry(QRect(144,400,150,200));
    disabled->setStyleSheet("backgound-color: transparent;border: none");
    disabled2 = new QPushButton("",this);
    disabled2->setGeometry(QRect(306,400,139,200));
    disabled2->setStyleSheet("backgound-color: transparent;border: none");
    setFixedSize(1350,600);
    setWindowTitle("Parking");
    //setMenuBar();
}

void Parking::miejsceParkingowe(const QRect& pole, const QString& nazwa){
    QPushButton * tmp = new QPushButton(nazwa,this);
    tmp->setGeometry(pole);
    tmp->setStyleSheet("backgound-color: transparent;border: none");
    miejsca_parkingowe.append(tmp);
}

//132,150,139,132, 153, 131,150,141,158
//12,230,400
