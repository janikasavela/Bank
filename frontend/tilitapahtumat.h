#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "myurl.h"

class Tilitapahtumat : public QObject
{
    Q_OBJECT
public:
    explicit Tilitapahtumat(QString id_kortti,QObject *parent = nullptr);

signals:
    void tilitapahtumat_nayta(QString);
    //laita kommentteihin jos paska

protected slots:
void tilitapahtumatSlot (QNetworkReply *reply);
void tilitapahtumat_clicked(QByteArray webToken);

protected:
QString kortti;
QByteArray wb;

private:
QNetworkAccessManager *tilitapahtumaManager;
QNetworkReply *reply;
QByteArray response_data;

};

#endif // TILITAPAHTUMAT_H
