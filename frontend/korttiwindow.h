#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "tilitapahtumat.h"

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
    void tilitapahtumat(QByteArray);

public slots:
    void tulosta_Tilitapahtumat(QString,QString,QString,QString);

private slots:
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnNostaRahaa_clicked();
    void on_btnSiirraRahaa_clicked();
    void on_btnReturn_clicked();
    void on_btnLogout_clicked();
    void tilitSlot(QNetworkReply *reply);

    void on_comboTili_activated(int index);

private:
    Ui::KorttiWindow *ui;
    QByteArray webToken;
    QString kortti;
    QNetworkReply *reply;
    QByteArray response_data;
    Tilitapahtumat *objectTilitapahtumat;
    QStringList tilinumero, saldo, luotto;
    QString aTili;
};

#endif // KORTTIWINDOW_H
