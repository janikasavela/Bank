#include "korttiwindow.h"
#include "qdebug.h"
#include "ui_korttiwindow.h"
#include "tilitapahtumat.h"
#include "saldo.h"
#include "myurl.h"

KorttiWindow::KorttiWindow(QString id_kortti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KorttiWindow)
{
    ui->setupUi(this);
    kortti=id_kortti;
    ui->labelidkortti->setText(kortti+" (Valikko)");
    ui->stackedWidget->setCurrentIndex(0);      //KorttiWindowin valikko
    ui->btnReturn->hide();
    max = 10;
    i = 0;
}

KorttiWindow::~KorttiWindow()
{
    delete ui;
    delete objectTilitapahtumat;
    objectTilitapahtumat = nullptr;
    delete objectSaldo;
    objectSaldo = nullptr;
}

const QByteArray &KorttiWindow::getWebToken() const
{
    return webToken;
}

void KorttiWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void KorttiWindow::tulosta_Tilitapahtumat(QStringList lista,QString omistaja,QString saldo,QString tilinumero)
{
    //tähän slottiin lähetetään kaikki tilitapahtumien tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu tapahtumista";
    uusi_lista=lista;
    ui->textTilitapahtumat->setEnabled(false);
    ui->btn_uudemmat->setEnabled(false);
    QString tulostus="";

    if (uusi_lista.length()>i && uusi_lista.length()>max) {//tarkistetaan että tapahtumia on tarpeeksi jotta voidaan muodostaa uudempien 10 tapahtuman stringi
        for (int x=i; x<max; x++){              //muuten tulee error
            tulostus+=uusi_lista[x];
      }
        ui->textTilitapahtumat->setText(tulostus);
        ui->label_tilitapahtumat->setText("Tilin omistaja: "+omistaja+" Saldo: "+saldo+" Tilinumero: "+tilinumero);
    }

    else {
        ui->btn_vanhemmat->setEnabled(false);
        ui->label_tilitapahtumat->setText("Tilin omistaja: "+tilin_omistaja+" Tilin saldo: "+saldo_string);
        ui->textTilitapahtumat->setText("Ei tilitapahtumia");
    }

}

void KorttiWindow::tulosta_saldo(QStringList lista,QStringList omistaja,QString saldo,QString tilinumero)
{
    //tähän slottiin lähetetään kaikki saldo tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu saldosta";
    qDebug()<<lista.length();
    ui->textSaldo->setEnabled(false);

    QString tapahtumat,omistajan;

    if (lista.length()>0) {

    if(lista.length()>4) {
    for (int x=0; x<5; x++){
                tapahtumat+=lista[x]; } }
    else if (lista.length()<5 && lista.length()>0) {
        for (int x=0; x<lista.length(); x++){
                    tapahtumat+=lista[x]; } }
    omistajan+=omistaja[0];
    ui->textSaldo->setText("Tilin omistajan tiedot: \n"+omistajan+"\n\n"+tapahtumat);
    ui->label_saldo->setText(" Saldo: "+saldo+" Tilinumero: "+tilinumero);  }

    else {   ui->textSaldo->setText("Tilin omistajan tiedot: \n"+omistaja_tiedot+"\n\nEi tilitapahtumia");
        ui->label_saldo->setText(" Saldo: "+saldo_string+" Tilinumero: "+tilinumero);    }
}

void KorttiWindow::on_btnTilitapahtumat_clicked()
{   ui->comboTili->setEnabled(false);
    ui->labelidkortti->setText(kortti+" (Tilitapahtumat)");
    ui->stackedWidget->setCurrentIndex(2);
    ui->btnReturn->show();

    qDebug()<<webToken;

    objectTilitapahtumat = new Tilitapahtumat(kortti); //luodaan koosteyhteys tilitapahtumat luokkaan
    connect(this,SIGNAL(tilitapahtumat(QByteArray,QString)),   //yhdistetään signaali tästä tilitapahtumien alustus slottiin, signaalin mukana webtoken
            objectTilitapahtumat, SLOT(tilitapahtumat_clicked(QByteArray,QString)) );

    //yhdistetään signaali jonka mukana viedään tiedot tilitapahtumista tänne korttiwindowin tilitapahtumien tulostus slottiin
    connect(objectTilitapahtumat,SIGNAL(tilitapahtumat_nayta(QStringList,QString,QString,QString)),
            this, SLOT(tulosta_Tilitapahtumat(QStringList,QString,QString,QString)), Qt::DirectConnection);

    //lähetetään signaali tilitapahtumien alustus slottiin niin saadaan tilitapahtumien haku käyntiin
    emit tilitapahtumat(webToken,aTili);

    ui->btn_uudemmat->setEnabled(false);
    ui->btn_vanhemmat->setEnabled(true);
    qDebug()<<"tili signal lähetetty";


}


void KorttiWindow::on_btnSaldo_clicked()
{   ui->comboTili->setEnabled(false);
    ui->labelidkortti->setText(kortti+" (Saldo)");
    ui->stackedWidget->setCurrentIndex(1);
    ui->btnReturn->show();

    objectSaldo = new Saldo(kortti); //luodaan koosteyhteys tilitapahtumat luokkaan
    connect(this,SIGNAL(saldo_signal(QByteArray,QString)),   //yhdistetään signaali tästä tilitapahtumien alustus slottiin, signaalin mukana webtoken
            objectSaldo, SLOT(saldo_clicked(QByteArray,QString)) );

    //yhdistetään signaali jonka mukana viedään tiedot tilitapahtumista tänne korttiwindowin tilitapahtumien tulostus slottiin
    connect(objectSaldo,SIGNAL(saldo_nayta(QStringList,QStringList,QString,QString)),
            this, SLOT(tulosta_saldo(QStringList,QStringList,QString,QString)), Qt::DirectConnection);

    //lähetetään signaali tilitapahtumien alustus slottiin niin saadaan tilitapahtumien haku käyntiin
    emit saldo_signal(webToken,aTili);

    qDebug()<<"saldo signal lähetetty";

}


void KorttiWindow::on_btnNostaRahaa_clicked()
{
    ui->labelidkortti->setText(kortti+" (Nosto)");
    ui->stackedWidget->setCurrentIndex(3);
    ui->btnReturn->show();
}


void KorttiWindow::on_btnSiirraRahaa_clicked()
{
    ui->labelidkortti->setText(kortti+" (Siirto)");
    ui->stackedWidget->setCurrentIndex(4);
    ui->btnReturn->show();
}


void KorttiWindow::on_btnReturn_clicked()
{
    ui->labelidkortti->setText(kortti+" (Valikko)");
    ui->stackedWidget->setCurrentIndex(0);
    ui->btnReturn->hide();
    ui->textTilitapahtumat->clear();
    ui->textSaldo->clear();
    ui->comboTili->setEnabled(true);
    i=0;
    max=10;
}

void KorttiWindow::on_btnLogout_clicked()
{
    qDebug()<<"logout signal";
    emit timeout();
    this->close();
}

void KorttiWindow::tilitSlot(QNetworkReply *reply)
{
   //Haetaan kaikki tilit johon kortin haltijalla on oikeus

   QByteArray response_data=reply->readAll();
   QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
   QJsonArray json_array = json_doc.array();
   int kerrat=0;

  //siirretään haetut tiedot QStringListiin
      foreach (const QJsonValue &value, json_array) {
          QJsonObject json_obj = value.toObject();
          luotto+=QString::number(json_obj["luottoraja"].toInt());
          saldo+=QString::number(json_obj["saldo"].toInt());
          tilinumero+=QString::number(json_obj["id_tilinumero"].toInt());
          kerrat+=1;    //lasketaan tilien määrä
      }

      if(kerrat>1){
          qDebug()<<"useampi tili löydetty";
      }
      else{
          qDebug()<<"yksi tili löydetty";
          saldo_string=saldo[0];
      }
      if(kerrat==1){
          if(luotto[0]=="0"){
              ui->labelActiveTili->setText("DEBIT Tili:");
          ui->comboTili->addItem(tilinumero[0]);
          ui->comboTili->setDisabled(1);
          aTili=ui->comboTili->itemText(0);
          }
          else{
              ui->labelActiveTili->setText("CREDIT Tili:");
              ui->comboTili->addItem(tilinumero[0]);
              ui->comboTili->setDisabled(1);
              aTili=ui->comboTili->itemText(0);
          }
          }


      else{
          ui->comboTili->addItem("VALITSE TILI");
          ui->labelActiveTili->setText("Valitse Tili");
          ui->stackedWidget->setDisabled(1);
          for(int i= 0; i < kerrat; i++){
          if(luotto[i]==0){
          ui->comboTili->addItem(tilinumero[i]);
      }
          else{
              ui->comboTili->addItem(tilinumero[i]);
          }}}
}

void KorttiWindow::on_comboTili_activated(int index)    //Kun comboboxissa tehdään valinta
{
    //Poistetaan väliaikainen arvo (varmaan parempikin tapa olemassa mutta tämä toimii tällä hetkellä)
    if(ui->comboTili->itemText(0)==("VALITSE TILI")){
        ui->comboTili->removeItem(0);
        index-=1;
        if(index<0){index=0;}
        aTili=ui->comboTili->itemText(index);
        saldo_string=saldo[index];
        qDebug()<<"aktiivinen tili: "+aTili;
        ui->stackedWidget->setEnabled(1);
    }
    else{
    aTili=ui->comboTili->itemText(index);
    saldo_string=saldo[index];
    qDebug()<<"aktiivinen tili: "+aTili;
    }

    //Tarkistetaan onko valittu tili Credit vai Debit

    if(luotto[index]=="0"){
        ui->labelActiveTili->setText("DEBIT Tili:");
    }
    else{
        ui->labelActiveTili->setText("CREDIT Tili:");
    }

    QString site_url=MyUrl::getBaseUrl()+"/tili/checkOmistaja/"+aTili;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(this->getWebToken()));
    //WEBTOKEN LOPPU
    korttiManager = new QNetworkAccessManager(this);
    connect(korttiManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getOmistajaSlot(QNetworkReply*)));
    reply = korttiManager->get(request);
}


void KorttiWindow::on_btn_uudemmat_clicked() //tilitapahtumian < nuoli
{
    ui->btn_vanhemmat->setEnabled(true);
    max -=10;
    i-=10;

    if (max == 10 && i == 0) {
        ui->btn_uudemmat->setEnabled(false); }

    QString tulostus="";

    if (uusi_lista.length()>i && uusi_lista.length()>max) //tarkistetaan että tapahtumia on tarpeeksi jotta voidaan muodostaa uudempien 10 tapahtuman stringi
        for (int x=i; x<max; x++){              //muuten tulee error
            tulostus+=uusi_lista[x];
      }


    ui->textTilitapahtumat->setText(tulostus);
}

void KorttiWindow::on_btn_vanhemmat_clicked() //tilitapahtumien > nuoli
{
   ui->btn_uudemmat->setEnabled(true);
   max +=10;
   i+=10;


   int pituus = uusi_lista.length();
   int loput = max-pituus;
   int uusi_max=max-loput;
   QString tulostus="";
   int y= 1;
   if (uusi_lista.length()>i && uusi_lista.length()>max) //tarkistetaan että tapahtumia on tarpeeksi jotta voidaan muodostaa uudempien 10 tapahtuman stringi
       for (int x=i; x<max; x++){              //muuten tulee error
           tulostus+=uusi_lista[x];
           y=0;
     }

   else if(y == 1) {
       for (int x=i; x<uusi_max; x++){
           tulostus+=uusi_lista[x];
   } ui->btn_vanhemmat->setEnabled(false);
    }



   ui->textTilitapahtumat->setText(tulostus);
}

void KorttiWindow::getOmistajaSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
       QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
       QJsonArray json_array = json_doc.array();

       QStringList tilin_omistaja_tiedot = {""};
       tilin_omistaja_tiedot.clear();
   //siirretään haetut tiedot muuttujiin
       foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           tilin_omistaja=json_obj["tilin omistaja"].toString();
           tilin_omistaja_tiedot+=json_obj["tilin omistaja"].toString()+"\n"+json_obj["osoite"].toString()+"\n"+json_obj["puhnum"].toString();
       }

       omistaja_tiedot=tilin_omistaja_tiedot[0];
       reply->deleteLater();
       korttiManager->deleteLater();
}

