#include "korttiwindow.h"
#include "qdebug.h"
#include "ui_korttiwindow.h"
#include "tilitapahtumat.h"
#include <QStringList>

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
{   //tätä voi kutsua jos tarvii johonkin uuteen tauluun saada sen webtokenin. vielä ei olla tarvittu tätä mihinkään..
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


    //alustetaan muuttujiin 50 uusinta tapahtumaa. jos tapahtumia ei riitä joka sivulle niin stringin arvoksi tulee "ei aiempia tilitapahtumia"
    QString sivu1, sivu2, sivu3, sivu4, sivu5, sivu6;
    sivu1=alustaSivut(lista,0,10);
    sivu2=alustaSivut(lista,10,20);
    sivu3=alustaSivut(lista,20,30);
    sivu4=alustaSivut(lista,30,40);
    sivu5=alustaSivut(lista,40,50);

    ui->textTilitapahtumat->setEnabled(false);
    ui->textTilitapahtumat->setText(sivu1);
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
    connect(objectTilitapahtumat,SIGNAL(tilitapahtumat_nayta(QStringList,QString,QString,QString)),
            this, SLOT(tulosta_Tilitapahtumat(QStringList,QString,QString,QString)), Qt::DirectConnection);

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

QString KorttiWindow::alustaSivut(QStringList lista, int aloitus, int lopetus)
{
   QString string;

   if (lista.length()>aloitus && lista.length()>lopetus) //tarkistetaan että tapahtumia on tarpeeksi jotta voidaan muodostaa uusi 10 tapahtuman stringi
       for (int i=aloitus; i<lopetus; i++){              //muuten tulee error
         string+=lista[i];
     }
   else {
       string="Ei aikaisempia tilitapahtumia";
   }
  return string;
}
