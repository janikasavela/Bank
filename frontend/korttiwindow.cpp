#include "korttiwindow.h"
#include "qdebug.h"
#include "ui_korttiwindow.h"

KorttiWindow::KorttiWindow(QString id_kortti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KorttiWindow)
{
    ui->setupUi(this);
    kortti=id_kortti;
    ui->labelidkortti->setText(kortti+" (Valikko)");
    ui->stackedWidget->setCurrentIndex(0);      //KorttiWindowin menuWindow
    ui->btnReturn->hide();
}

KorttiWindow::~KorttiWindow()
{
    delete ui;
}

const QString &KorttiWindow::getWebToken() const
{
    return webToken;
}

void KorttiWindow::setWebToken(const QString &newWebToken)
{
    webToken = newWebToken;
}

void KorttiWindow::on_btnTilitapahtumat_clicked()
{
    ui->labelidkortti->setText(kortti+" (Tilitapahtumat)");
    ui->stackedWidget->setCurrentIndex(2);
    ui->btnReturn->show();
    QString wb=this->getWebToken();
    qDebug()<<wb;
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
