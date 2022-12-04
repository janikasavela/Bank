#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "tilitapahtumat.h"
#include "tilioperaatio.h"

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
    void hae_tiliInfo(QByteArray,QString);

public slots:
    void tulosta_Tilitapahtumat(QStringList,QString,QString,QString);
    void tuo_asiakas_info(QString,QString);

private slots:
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnNostaRahaa_clicked();
    void on_btnSiirraRahaa_clicked();
    void on_btnReturn_clicked();
    void on_btnLogout_clicked();
    void tilitSlot(QNetworkReply *reply);
    void on_comboTili_activated(int index);
    void on_btn_uudemmat_clicked();
    void on_btn_vanhemmat_clicked();


    void on_btn20e_clicked();

    void on_btn40e_clicked();

    void on_btn60e_clicked();

    void on_btnNosta_clicked();

private:
    Ui::KorttiWindow *ui;
    QByteArray webToken;
    QString kortti;
    QNetworkReply *reply;
    QByteArray response_data;
    Tilitapahtumat *objectTilitapahtumat;
    tilioperaatio *objectTilioperaatio;
    QStringList tilinumero, saldo, luotto, uusi_lista;
    QString aTili;
    int max, i;
};

#endif // KORTTIWINDOW_H
