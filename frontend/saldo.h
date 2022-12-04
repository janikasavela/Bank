#ifndef SALDO_H
#define SALDO_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


class Saldo : public QObject
{
    Q_OBJECT
public:
    explicit Saldo(QString id_kortti, QObject *parent = nullptr);

signals:
    void saldo_nayta(QStringList);

protected slots:
void saldoSlot (QNetworkReply *reply);
void saldo_clicked(QByteArray webToken, QString);

protected:
QString kortti;
QByteArray wb;

private:
QNetworkAccessManager *saldoManager;
QNetworkReply *reply;
QByteArray response_data;
QString tilinumero;
QStringList tapahtumat;
};

#endif // SALDO_H
