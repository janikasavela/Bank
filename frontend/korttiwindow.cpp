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

void KorttiWindow::tulosta_Tilitapahtumat(QStringList lista)
{
    //tähän slottiin lähetetään kaikki tilitapahtumien tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu tapahtumista";
    uusi_lista=lista;
    ui->textTilitapahtumat->setEnabled(false);
    ui->btn_uudemmat->setEnabled(false);
    QString tulostus="";

    if (lista.length()>0) {

    if (uusi_lista.length()>i && uusi_lista.length()>max) {//tarkistetaan että tapahtumia on tarpeeksi jotta voidaan muodostaa uudempien 10 tapahtuman stringi
            for (int x=i; x<max; x++){              //muuten tulee error
                tulostus+=uusi_lista[x];  } }
    else if (lista.length()<10 && lista.length()>0) {
        for (int x=0; x<lista.length(); x++){
                    tulostus+=lista[x]; } }

        ui->textTilitapahtumat->setText(tulostus);
        ui->label_tilitapahtumat->setText("Tilin omistaja: "+tilin_omistaja+" Saldo: "+saldo_string+" Tilinumero: "+aTili);
    }


    else {
        //jos tilitapahtumia niin proceduuri päivittää credit tilin saldon, jos niitä ei näy niin saldo on 0
        //laitetaan tässä näkymään saldo siinätapauksessa käytettävissä olevana luoton määränä
        if (saldo_string == "0") { ui->label_tilitapahtumat->setText("Tilin omistaja: "+tilin_omistaja+" Tilin saldo: "+luotto_string); }
        else { ui->label_tilitapahtumat->setText("Tilin omistaja: "+tilin_omistaja+" Tilin saldo: "+saldo_string); }

        ui->btn_vanhemmat->setEnabled(false);
        ui->textTilitapahtumat->setText("Ei tilitapahtumia");
    }

}

void KorttiWindow::tulosta_saldo(QStringList lista)
{
    //tähän slottiin lähetetään kaikki saldo tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu saldosta";
    qDebug()<<lista.length();
    ui->textSaldo->setEnabled(false);

    QString tapahtumat;

    if (lista.length()>0) {

    if(lista.length()>4) {
    for (int x=0; x<5; x++){
                tapahtumat+=lista[x]; } }
    else if (lista.length()<5 && lista.length()>0) {
        for (int x=0; x<lista.length(); x++){
                    tapahtumat+=lista[x]; } }

    ui->textSaldo->setText("Tilin omistajan tiedot: \n"+omistaja_tiedot+"\n\n"+tapahtumat);
    ui->label_saldo->setText(" Saldo: "+saldo_string+" Tilinumero: "+aTili);  }

    else {   ui->textSaldo->setText("Tilin omistajan tiedot: \n"+omistaja_tiedot+"\n\nEi tilitapahtumia");

        if (saldo_string == "0") { ui->label_saldo->setText(" Saldo: "+luotto_string+" Tilinumero: "+aTili);   }
        else {ui->label_saldo->setText(" Saldo: "+saldo_string+" Tilinumero: "+aTili);}
    }
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
    connect(objectTilitapahtumat,SIGNAL(tilitapahtumat_nayta(QStringList)),
            this, SLOT(tulosta_Tilitapahtumat(QStringList)), Qt::DirectConnection);

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
    connect(objectSaldo,SIGNAL(saldo_nayta(QStringList)),
            this, SLOT(tulosta_saldo(QStringList)), Qt::DirectConnection);

    //lähetetään signaali tilitapahtumien alustus slottiin niin saadaan tilitapahtumien haku käyntiin
    emit saldo_signal(webToken,aTili);

    qDebug()<<"saldo signal lähetetty";

}


void KorttiWindow::on_btnNostaRahaa_clicked()
{
    ui->comboTili->setEnabled(false);
    ui->labelidkortti->setText(kortti+" (Nosto)");
    ui->label_tiliInfo->setText(" Saldo: "+saldo_string+" Tilinumero: "+aTili);
    ui->stackedWidget->setCurrentIndex(3);
    ui->btnReturn->show();
}


void KorttiWindow::on_btnSiirraRahaa_clicked()
{
    ui->comboTili->setEnabled(false);
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
    //tilioperaatioiden alustus
    //objectTilioperaatio = new tilioperaatio(aTili);
    //connect(this,SIGNAL(hae_tiliInfo(QByteArray,QString)),objectTilioperaatio, SLOT(tilioperaatio_info(QByteArray,QString)));
    //connect(objectTilioperaatio,SIGNAL(vie_asiakas_info(QString,QString)), this, SLOT(tuo_asiakas_info(QString,QString)));
    //connect(ui->btnNosta,SIGNAL(clicked()),objectTilioperaatio, SLOT(nostoSlot(QNetworkReply *reply)));
    //tilioperaatioiden alustus END

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
          luotto_string=luotto[0];
      }
      if(kerrat==1){
          ui->comboTili->addItem(tilinumero[0]);
          on_comboTili_activated(0);
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
        luotto_string=luotto[index];
        qDebug()<<"aktiivinen tili: "+aTili;
        ui->stackedWidget->setEnabled(1);
    }
    else{
    aTili=ui->comboTili->itemText(index);
    saldo_string=saldo[index];
    luotto_string=luotto[index];
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

void KorttiWindow::on_btn20e_clicked(){nostoMaaraPaivitys("20");}
void KorttiWindow::on_btn40e_clicked(){nostoMaaraPaivitys("40");}
void KorttiWindow::on_btn60e_clicked(){nostoMaaraPaivitys("60");}
void KorttiWindow::on_btn100e_clicked(){nostoMaaraPaivitys("100");}
void KorttiWindow::on_btn200e_clicked(){nostoMaaraPaivitys("200");}
void KorttiWindow::on_btn500e_clicked(){nostoMaaraPaivitys("500");}

void KorttiWindow::on_btnXe_clicked()
{
    bool ok;
    int ii = QInputDialog::getInt(this,"Nosto","0-"+saldo_string, 1, 1, saldo_string.toInt(), 1, &ok);
    if (ok){nostoMaaraPaivitys(QString::number(ii));}
}

void KorttiWindow::on_btnTyhjenna_clicked()
{
    ui->lineNostoMaara->clear();
    ui->btnNosta->setDisabled(1);
    ui->btnTyhjenna->setDisabled(1);
}

void KorttiWindow::on_btnNosta_clicked()
{
    qDebug()<<"nostetaan "+ui->lineNostoMaara->text();
    //
    //nosto osuus
    qDebug()<<kortti;
    qDebug()<<aTili;
    QJsonObject jsonObj;
    jsonObj.insert("id_kortti",kortti);
    jsonObj.insert("id_tilinumero",aTili);
    jsonObj.insert("maara",ui->lineNostoMaara->text());
    QString site_url=MyUrl::getBaseUrl()+"/tili/nosto/";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(this->getWebToken()));
    //WEBTOKEN LOPPU
    korttiManager = new QNetworkAccessManager(this);
    connect(korttiManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tiliOperaatio(QNetworkReply*)));
    reply = korttiManager->post(request, QJsonDocument(jsonObj).toJson());
    //
    on_btnTyhjenna_clicked();
}

void KorttiWindow::nostoMaaraPaivitys(QString maara)
{
    ui->lineNostoMaara->setText(maara);
    ui->btnNosta->setEnabled(1);
    ui->btnTyhjenna->setEnabled(1);
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

void KorttiWindow::tiliOperaatio(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

   //int test=1; //compare funktio palauttaa 0 jos vertailu tosi, muuten -1.
    if(QString::compare(response_data,"true")==0){
        on_btnReturn_clicked();
        QMessageBox msgBox;
        msgBox.setText("Tilisiirto suoritettu onnistuneesti!");
        msgBox.exec();
    }
}

