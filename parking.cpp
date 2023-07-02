#include "parking.h"


QList<QString> lista_samochodow = {
    ":/czerwony_samochodzik.png",
    ":/czarny_samochodzik.png",
    ":/zolty_samochodzik.png",
    ":/pomaranczowy_samochodzik.png",
    ":/zielony_samochodzik.png"
};

void Parking::wczytajMiejsca(){
    QFile file(":/miejsca.dat");
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5);
        while(!in.atEnd()){
            QRect tmp;
            in >> tmp;
            miejsca.append(tmp);
        }
        file.close();
    }
}

Parking::Parking(QWidget *parent): QMainWindow{parent}{

    setStyleSheet("QMainWindow { background-image: url(:/Parking.png);}");

    wczytajMiejsca();
    for(const QRect& a: miejsca)
        miejsceParkingowe(a,"",QRandomGenerator::global()->bounded(2));
    disabled = new QPushButton("",this);
    disabled->setGeometry(QRect(144,400,150,200));
    disabled->setStyleSheet("background-color: transparent;border: none");
    disabled2 = new QPushButton("",this);
    disabled2->setGeometry(QRect(306,400,139,200));
    disabled2->setStyleSheet("background-color: transparent;border: none");
    setFixedSize(1350,600);
    setWindowTitle("Parking");
    connect(disabled,QPushButton::clicked,this,Parking::pokazDisabledInfo);
    connect(disabled2,QPushButton::clicked,this,Parking::pokazDisabledInfo);
    //setMenuBar();
}

void Parking::miejsceParkingowe(const QRect& pole, const QString& nazwa,int random_number){
    if(random_number == 0){
        QPushButton * tmp = new QPushButton(nazwa,this);
        tmp->setGeometry(pole);
        tmp->setStyleSheet("background-color: transparent;border: none");
        tmp->setVisible(true);
        miejsca_parkingowe.append(tmp);
    }
    else{
        QLabel * zdjontko = new QLabel(lista_samochodow[rand()%5],this);
        QPixmap pixmap(lista_samochodow[rand()%5]);
        zdjontko->setPixmap(pixmap);
        zdjontko->setScaledContents(true);
        zdjontko->setGeometry(pole);
        zajete_miejsca.append(zdjontko);
    }
}

void Parking::pokazDisabledInfo(){

    Disabled *d = new Disabled;
    d->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    d->show();
}

Disabled::Disabled(QWidget * parent):QDialog(parent){

    setFixedSize(500,100);
    setWindowTitle("Informacja");
    setModal(true);


    QString s = "Nie możesz parkować na miejscu dla niepełnosprawnych.";

    QPushButton * przycisk = new QPushButton("Ok",this);
    QLabel *kupiony_bilet = new QLabel(s,this);

    QFont label("Times New Roman",16);
    kupiony_bilet->setFont(label);
    przycisk->setFont(label);

    QVBoxLayout *tmplayout = new QVBoxLayout();

    tmplayout->addWidget(kupiony_bilet,0,Qt::AlignHCenter);
    tmplayout->addWidget(przycisk,1,Qt::AlignHCenter);

    setLayout(tmplayout);

    connect(przycisk,&QPushButton::clicked,this,&Disabled::close);
}
