#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myurl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kierros = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectKorttiWindow;
    objectKorttiWindow = nullptr;
}


void MainWindow::on_pushButtonLogin_clicked()
{
    id_kortti=ui->lineEditIdKortti->text();
    kortit+=ui->lineEditIdKortti->text();
    QString pin_koodi=ui->lineEdit_2PinKoodi->text();

    qDebug()<<id_kortti;
    qDebug()<<kortit;

    QJsonObject jsonObj;
    jsonObj.insert("id_kortti",id_kortti);
    jsonObj.insert("pin_koodi",pin_koodi);

    QString site_url=MyUrl::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

}

void MainWindow::loginSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<response_data;

   int test=QString::compare(response_data,"false"); //compare funktio palauttaa 0 jos vertailu tosi, muuten -1.
    qDebug()<<test;

    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else {

        if(QString::compare(response_data,"-4078")==0){
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
        }
        else {
                   if(test==0) {
                       ui->lineEditIdKortti->clear();
                       ui->lineEdit_2PinKoodi->clear();
                       ui->labelInfo->setText("Tunnus ja pin-koodi eivät täsmää");
                       kierros++;
                       if (kierros == 2) {
                           if (kortit[0] == kortit [1]) { QMessageBox::warning(this,"Varoitus","Jos syötät pin-koodin vielä kerran väärin, kortti suljetaan!");}
                           else {
                                  QString kortti2 = kortit[1];
                                  kortit.clear();
                                  kortit+=kortti2;
                                  kierros=1; } }

                if (kierros==3){
                    if (kortit[1] == kortit[2]) {

                        kortit.clear();
                        kierros=0;
                   QMessageBox::warning(this,"Ilmoitus","Kortti suljettu!");

                    QJsonObject jsonObj;
                    jsonObj.insert("id_kortti",id_kortti);
                    QString site_url=MyUrl::getBaseUrl()+"/sulje_kortti/"+id_kortti;
                    QNetworkRequest request((site_url));

                    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                    loginManager = new QNetworkAccessManager(this);
                    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(deleted(QNetworkReply*)));

                    reply = loginManager->deleteResource(request); }

                    else if (kortit[1] != kortit[2]) {

                        QString kortti1=kortit[2];
                        qDebug()<<kortti1;
                        kortit.clear();
                        kortit+=kortti1;
                        kierros=1;
                    }

                    else {kortit.clear();
                          kierros=0;}

                } }
            else {
                       kortit.clear();
                       kierros=0;
                       objectKorttiWindow = new KorttiWindow(id_kortti); //jos sisäänkirjautuminen ok, luodaan koosteyhteys
                       objectKorttiWindow->setWebToken("Bearer " + response_data); //lähetetään webtoken korttiwindowille

                       connect(objectKorttiWindow,SIGNAL(timeout()),this,SLOT(timeoutSlot()));


                       QString site_url=MyUrl::getBaseUrl()+"/oikeudet/"+id_kortti;
                       QNetworkRequest request((site_url));
                       //WEBTOKEN ALKU
                       request.setRawHeader(QByteArray("Authorization"),(objectKorttiWindow->getWebToken()));
                       //WEBTOKEN LOPPU
                       loginManager = new QNetworkAccessManager(this);

                       connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(korttiSlot(QNetworkReply*)));

                       reply = loginManager->get(request);

        }

        }

    }

}

void MainWindow::timeoutSlot()
{
    this->show();
    ui->lineEditIdKortti->clear();
    ui->lineEdit_2PinKoodi->clear();
    ui->labelInfo->setText("Uloskirjautuminen suoritettu");
}


void MainWindow::deleted(QNetworkReply *reply)
{
     response_data=reply->readAll();
    qDebug()<<response_data;
    qDebug()<<"deleted";
}

void MainWindow::korttiSlot(QNetworkReply *reply)
{
   response_data=reply->readAll();
   qDebug()<<response_data;
    reply->deleteLater();
    loginManager->deleteLater();

    if (response_data != ""){

                  //Haetaan kaikki tilit joihin kortin haltijalla on oikeus

                  QString site_url=MyUrl::getBaseUrl()+"/tili/checkTilit/"+id_kortti;
                  QNetworkRequest request((site_url));
                  //WEBTOKEN ALKU
                  request.setRawHeader(QByteArray("Authorization"),(objectKorttiWindow->getWebToken()));
                  //WEBTOKEN LOPPU
                  loginManager = new QNetworkAccessManager(this);
                  connect(loginManager, SIGNAL(finished (QNetworkReply*)), objectKorttiWindow, SLOT(tilitSlot(QNetworkReply*)));
                  reply = loginManager->get(request);
                  this->hide();

                  objectKorttiWindow->show();

    }

    else {QMessageBox::warning(this,"Ilmoitus","Kortti on suljettu!");                                              }

}
