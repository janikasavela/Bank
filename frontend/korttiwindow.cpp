#include "korttiwindow.h"
#include "qdebug.h"
#include "ui_korttiwindow.h"

KorttiWindow::KorttiWindow(QString id_kortti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KorttiWindow)
{
    ui->setupUi(this);
    ui->labelidkortti->setText(id_kortti);
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
    QString wb=this->getWebToken();
    qDebug()<<wb;
}

