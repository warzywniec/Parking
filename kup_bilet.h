#ifndef KUP_BILET_H
#define KUP_BILET_H

#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <vector>


void wczytajBilety();

class BiletKupiony: public QDialog{
    Q_OBJECT

public:
    BiletKupiony(QWidget * parent = nullptr);

};

class Bilet{

private:
    QString typ;
    int cena;

public:
    Bilet(QString &typ, int cena): typ(typ), cena(cena){}
    QString jakiTyp(){return typ;}
    int jakaCena(){return cena;}
    friend void wczytajBilety();

};

class Cennik: public QDialog{
    Q_OBJECT

private:
    QLabel * nazwa;
    std::vector<QLabel *> bilet;
    std::vector<QLabel *> cena;

public:
    friend class Parkomat;
    Cennik(QWidget * parent = nullptr);
    QLabel *zrobLabel(QString a){QLabel *label = new QLabel(a,this); return label;}

public slots:
    void exitCennik(){this->close();}

};


class Parkomat: public QMainWindow{
    Q_OBJECT

private:
    QLabel * nazwa;
    QLabel * nazwa_biletu;
    QPushButton * kup_bilet;
    QPushButton * up;
    QPushButton * down;
    QVBoxLayout * main_layout;
    QGridLayout * layout;

public:
    Parkomat(QWidget *parent = nullptr);
    ~Parkomat(){}

private slots:
    void pokaBiletUp();
    void pokaBiletDown();
    void zakupBiletu();

signals:
    void exitCennik();

};
#endif // KUP_BILET_H
