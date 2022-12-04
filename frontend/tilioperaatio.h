#ifndef TILIOPERAATIO_H
#define TILIOPERAATIO_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class tilioperaatio : public QObject
{
        Q_OBJECT
    public:
    explicit tilioperaatio(QString aTili,QObject *parent = nullptr);
    signals:
    void vie_asiakas_info(QString,QString);
    protected slots:
    //void tilitapahtumatSlot (QNetworkReply *reply);
    //void tilitapahtumat_clicked(QByteArray webToken, QString);
    void nostoSlot (QNetworkReply *reply);
    void siirtoSlot (QNetworkReply *reply);
    void tilioperaatio_info(QByteArray webToken, QString);
    void tilioperaatio_info_done(QNetworkReply *reply);

    protected:
    QString kortti;
    QByteArray wb;

    private:
    QNetworkAccessManager *operationManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString tilinOmistaja, saldo, tilinumero;
    QStringList tapahtumat;
    };

    #endif // TILIOPERAATIO_H
