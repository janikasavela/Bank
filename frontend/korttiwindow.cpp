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
{   //tätä voi kutsua jos tarvii johonkin uuteen tauluun saada sen webtokenin. vielä ei olla tarvittu tätä mihinkään..
    return webToken;
}

void KorttiWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void KorttiWindow::tulosta_Tilitapahtumat(QString a)
{
    //tähän slottiin lähetetään kaikki tilitapahtumien tulostustiedot.
    qDebug()<<"tulosta signaali vastaanotettu tapahtumista";
    QString tulosta=a;
    ui->textTilitapahtumat->setEnabled(false);
    ui->textTilitapahtumat->setText(tulosta);
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
    connect(objectTilitapahtumat,SIGNAL(tilitapahtumat_nayta(QString)),
            this, SLOT(tulosta_Tilitapahtumat(QString)), Qt::DirectConnection);

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
