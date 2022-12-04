#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "tilitapahtumat.h"
#include <saldo.h>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class KorttiWindow;
}

class KorttiWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KorttiWindow(QString id_kortti,QWidget *parent = nullptr);
    ~KorttiWindow();

    const QByteArray &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);

signals:
    void timeout(); //yhdistety uloskirjautumisen slottiin
    void tilitapahtumat(QByteArray,QString);
    void saldo_signal(QByteArray,QString);

public slots:
    void tulosta_Tilitapahtumat(QStringList);
    void tulosta_saldo(QStringList);

private slots:
    void tilitSlot(QNetworkReply *reply);
    void on_comboTili_activated(int index);
    void getOmistajaSlot (QNetworkReply *reply);
    void tiliOperaatio (QNetworkReply *reply);
    void nostoMaaraPaivitys(QString);
    void on_btn_uudemmat_clicked();
    void on_btn_vanhemmat_clicked();
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnNostaRahaa_clicked();
    void on_btnSiirraRahaa_clicked();
    void on_btnReturn_clicked();
    void on_btnLogout_clicked();
    void on_btn20e_clicked();
    void on_btn40e_clicked();
    void on_btn60e_clicked();
    void on_btn100e_clicked();
    void on_btn200e_clicked();
    void on_btn500e_clicked();
    void on_btnXe_clicked();
    void on_btnNosta_clicked();
    void on_btnTyhjenna_clicked();

private:
    Ui::KorttiWindow *ui;
    QByteArray webToken;
    QString kortti;
    QNetworkReply *reply;
    QByteArray response_data;
    Tilitapahtumat *objectTilitapahtumat;
    Saldo *objectSaldo;
    QStringList tilinumero, saldo, luotto, uusi_lista,tilin_omistaja_tiedot;
    QString aTili, tilin_omistaja, saldo_string,omistaja_tiedot,luotto_string;
    int max, i;
    QNetworkAccessManager *korttiManager;
};

#endif // KORTTIWINDOW_H
