#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QString pin_koodi=ui->lineEdit_2PinKoodi->text();

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

    /* if lauseen voi tehdä kahdella tapaa. toimis myös näin, if(response_data.length() > 5) ja perään sitten mitä tehdään jos token toimii, eli
     * päittäin nuo if/else lohkojen sisällöt. Tässä siis verrataan pituutta false sanan pituuteen joka palautuu vääristä tunnareista */

   int test=QString::compare(response_data,"false");
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

            }
            else {

                objectKorttiWindow = new KorttiWindow(id_kortti);
                objectKorttiWindow->setWebToken("Bearer " + response_data);
                objectKorttiWindow->show();
                connect(objectKorttiWindow,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
                //QMainWindow::setEnabled(false);
                this->hide();

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
