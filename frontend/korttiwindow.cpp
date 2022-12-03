#include "korttiwindow.h"
#include "qdebug.h"
#include "ui_korttiwindow.h"
#include "tilitapahtumat.h"

KorttiWindow::KorttiWindow(QString id_kortti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KorttiWindow)
{
    ui->setupUi(this);
    kortti=id_kortti;
    ui->labelidkortti->setText(kortti+" (Valikko)");
    ui->stackedWidget->setCurrentIndex(0);      //KorttiWindowin valikko
    ui->btnReturn->hide();
}

KorttiWindow::~KorttiWindow()
{
    delete ui;
    delete objectTilitapahtumat;
    objectTilitapahtumat = nullptr;
}

const QByteArray &KorttiWindow::getWebToken() const
{
    return webToken;
}

void KorttiWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void KorttiWindow::tulosta_Tilitapahtumat(QString tapahtumat,QString omistaja,QString saldo,QString tilinumero)
{
    //tähän slottiin lähetetään kaikki tilitapahtumien tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu tapahtumista";

    ui->textTilitapahtumat->setEnabled(false);
    ui->textTilitapahtumat->setText(tapahtumat);
    ui->label_tilitapahtumat->setText("Tilin omistaja: "+omistaja+" Saldo: "+saldo+" Tilinumero: "+tilinumero);
}

void KorttiWindow::on_btnTilitapahtumat_clicked()
{
    ui->labelidkortti->setText(kortti+" (Tilitapahtumat)");
    ui->stackedWidget->setCurrentIndex(2);
    ui->btnReturn->show();

    qDebug()<<webToken;

    objectTilitapahtumat = new Tilitapahtumat(kortti); //luodaan koosteyhteys tilitapahtumat luokkaan
    connect(this,SIGNAL(tilitapahtumat(QByteArray)),   //yhdistetään signaali tästä tilitapahtumien alustus slottiin, signaalin mukana webtoken
            objectTilitapahtumat, SLOT(tilitapahtumat_clicked(QByteArray)) );

    //yhdistetään signaali jonka mukana viedään tiedot tilitapahtumista tänne korttiwindowin tilitapahtumien tulostus slottiin
    connect(objectTilitapahtumat,SIGNAL(tilitapahtumat_nayta(QString,QString,QString,QString)),
            this, SLOT(tulosta_Tilitapahtumat(QString,QString,QString,QString)), Qt::DirectConnection);

    //lähetetään signaali tilitapahtumien alustus slottiin niin saadaan tilitapahtumien haku käyntiin
    emit tilitapahtumat(webToken);
    qDebug()<<"tilitapahtumat signal lähetetty";

}


void KorttiWindow::on_btnSaldo_clicked()
{
    ui->labelidkortti->setText(kortti+" (Saldo)");
    ui->stackedWidget->setCurrentIndex(1);
    ui->btnReturn->show();
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
        qDebug()<<"aktiivinen tili: "+aTili;
        ui->stackedWidget->setEnabled(1);
    }
    else{
    aTili=ui->comboTili->itemText(index);
    qDebug()<<"aktiivinen tili: "+aTili;
    }

    //Tarkistetaan onko valittu tili Credit vai Debit

    if(luotto[index]=="0"){
        ui->labelActiveTili->setText("DEBIT Tili:");
    }
    else{
        ui->labelActiveTili->setText("CREDIT Tili:");
    }
}

