#include "kup_bilet.h"

std::vector<Bilet> bilety;
int currentIndex = 0;

void wczytajBilety(){

    // Plik bilety.csv został dodany do resource_files.qrc
    QFile file(":/bilety.csv");

    // sprawdzenie że plik się otworzył poprawnie
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Nie udało się otworzyć pliku CSV";
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    while (!in.atEnd())
    {
        line = in.readLine();
        QStringList fields = line.split(",");
        Bilet* a = new Bilet(fields[0],fields[1].toInt());
        bilety.push_back(*a);
        delete a;

        //      typ = fields[0];
        //      cena = fields[1].toInt();

        // Do something with the ticket information
        //qDebug() << "Type: " << typ << "Cost: " << cena;
    }

    file.close();
}

Cennik::Cennik(QWidget *parent): QDialog(parent){

    int height,i = 0;
    height = ((int)bilety.size() - 1) * 70;
    setStyleSheet("background-color: #FFECB3");
    setWindowTitle("Cennik");
    setGeometry(1200,300,400,height);


    nazwa = new QLabel("Cennik",this);
    for(Bilet a: bilety){
        bilet.push_back(zrobLabel(a.jakiTyp()));
        cena.push_back(zrobLabel(QString::number(a.jakaCena())));
    }

    QFont titleFont("TimesNewRoman", 20);
    QFont labelFont("TimesNewRoman", 12);
    nazwa->setFont(titleFont);
    for(QLabel *a: bilet){
        a->setFont(labelFont);
        a->setStyleSheet("border: 2px solid black; padding: 10px;");
    }
    for(QLabel *a: cena){
        a->setFont(labelFont);
        a->setStyleSheet("border: 2px solid black; padding: 10px;");
    }

    QVBoxLayout * newlayout = new QVBoxLayout();
    QGridLayout * layout = new QGridLayout();

    newlayout->addWidget(nazwa,0,Qt::AlignHCenter); // 0-środek, brak 0 - lewo
    for(QLabel *a: bilet){
        i++;
        layout->addWidget(a,i,0);
    }
    i = 0;
    for(QLabel *a: cena){
        i++;
        layout->addWidget(a,i,1,Qt::AlignRight);
    }

    newlayout->addLayout(layout);
    setLayout(newlayout);
}

Parkomat::Parkomat(QWidget *parent): QMainWindow(parent){

    setStyleSheet("background-color: #CCCCFF");
    setWindowTitle("Parkomat");
    setFixedSize(300,180);
    //nazwa = new QLabel("PARKOMAT",this);
    nazwa_biletu = new QLabel(bilety[currentIndex].jakiTyp(),this);
    nazwa_biletu->setObjectName("nazwa_biletu");
    kup_bilet = new QPushButton("Kup Bilet",this);
    up = new QPushButton("↑",this);
    down = new QPushButton("↓",this);

   // QFont titleFont("TimesNewRoman", 16, QFont::Bold);
    QFont labelFont("TimesNewRoman", 12);
    QFont buttonFont("TimesNewRoman", 12);
   // QFont resultFont("TimesNewRoman", 14);

    //nazwa->setFont(labelFont);
    nazwa_biletu->setFont(labelFont);
    kup_bilet->setFont(buttonFont);
    up->setFont(buttonFont);
    down->setFont(buttonFont);

    nazwa_biletu->setFixedSize(280, 50);
    nazwa_biletu->setAlignment(Qt::AlignCenter);
    nazwa_biletu->setStyleSheet("background-color: yellow; border: 5px solid purple; padding: 10px;");
    up->setStyleSheet("background-color: #4CAF50; color: white;");
    down->setStyleSheet("background-color: #f44336; color: white;");
    kup_bilet->setStyleSheet("background-color: #008CBA; color: white;");
    kup_bilet->setFixedSize(280, 50);
    up->setFixedSize(135, 50);
    down->setFixedSize(135, 50);

    main_layout = new QVBoxLayout();

    QWidget* containerWidget = new QWidget();
    containerWidget->setLayout(main_layout);

    layout = new QGridLayout(containerWidget);
    //layout->setSpacing(10);

    //layout->addWidget(nazwa,0,0);
    main_layout->addWidget(nazwa_biletu,0,Qt::AlignHCenter);
    main_layout->addWidget(kup_bilet,1);
    layout->addWidget(up,3,0);
    layout->addWidget(down,3,1);

    main_layout->addLayout(layout);

    setCentralWidget(containerWidget);
    connect(up,&QPushButton::clicked,this,&Parkomat::pokaBiletDown);
    connect(down,&QPushButton::clicked,this,&Parkomat::pokaBiletUp);
    connect(kup_bilet,&QPushButton::clicked,this,&Parkomat::zakupBiletu);
}

void Parkomat::pokaBiletUp(){
    if (currentIndex < (int)bilety.size() - 1)
        currentIndex++;
    else
        currentIndex = 0;

    nazwa_biletu->setText(bilety[currentIndex].jakiTyp());
}

void Parkomat::pokaBiletDown(){
    if (currentIndex > 0)
        currentIndex--;
    else
        currentIndex = bilety.size() - 1;

    nazwa_biletu->setText(bilety[currentIndex].jakiTyp());
}

void Parkomat::zakupBiletu(){
    emit exitCennik();
    BiletKupiony *s = new BiletKupiony();
    s->show();
    this->close();
}

BiletKupiony::BiletKupiony(QWidget * parent):QDialog(parent){

    setFixedSize(500,100);
    setWindowTitle("Informacja");

    QString s = bilety[currentIndex].jakiTyp() + " został kupiony.";

    QPushButton * przycisk = new QPushButton("Ok",this);
    QLabel *kupiony_bilet = new QLabel(s,this);

    QFont label("Times New Roman",16);
    kupiony_bilet->setFont(label);
    przycisk->setFont(label);

    QVBoxLayout *tmplayout = new QVBoxLayout();

    tmplayout->addWidget(kupiony_bilet,0,Qt::AlignHCenter);
    tmplayout->addWidget(przycisk,1,Qt::AlignHCenter);

    setLayout(tmplayout);

    connect(przycisk,&QPushButton::clicked,this,&BiletKupiony::close);
}
