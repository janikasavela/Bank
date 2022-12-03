#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class Tilitapahtumat : public QObject
{
    Q_OBJECT
public:
explicit Tilitapahtumat(QString id_kortti,QObject *parent = nullptr);

signals:
void tilitapahtumat_nayta(QStringList,QString,QString,QString);

protected slots:
void tilitapahtumatSlot (QNetworkReply *reply);
void tilitapahtumat_clicked(QByteArray webToken, QString);

protected:
QString kortti;
QByteArray wb;

private:
QNetworkAccessManager *tilitapahtumaManager;
QNetworkReply *reply;
QByteArray response_data;
QString tilinOmistaja, saldo, tilinumero;
QStringList tapahtumat;
};

#endif // TILITAPAHTUMAT_H
