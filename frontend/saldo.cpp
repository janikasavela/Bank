
#include "saldo.h"
#include "myurl.h"
#include <QStringList>

Saldo::Saldo(QString id_kortti, QObject *parent)
    : QObject{parent}
{
kortti=id_kortti; //alustetaan käytettävä kortti heti samalla kun luodaan koosteyhteys
}

void Saldo::saldoSlot(QNetworkReply *reply)
{
    //response_data=reply->readAll();
    //qDebug()<<response_data;

     QByteArray response_data=reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();

        QStringList tapahtumat = {""};
        tapahtumat.clear();

    //siirretään haetut tiedot muuttujiin
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            tapahtumat+="Tapahtuma: "+json_obj["tapahtuma"].toString()+" "+"Paiva: "+json_obj["paiva"].toString()+" "+"Aika: "+json_obj["aika"].toString()+" "+"Summa: "+QString::number(json_obj["summa"].toInt())+"\r";
        }

        qDebug()<<"\n"<<tapahtumat;

        qDebug()<<"lahetan nayta signal";
        qDebug()<<"TAPAHTUMAT TULOSTEETTUUUUUUU  \n";
        emit saldo_nayta(tapahtumat); //lähetetään haetut tiedot tilitapahtumien tulostus slottiin korttiwindowille.

        reply->deleteLater();
        saldoManager->deleteLater();



}

void Saldo::saldo_clicked(QByteArray webToken, QString tili)
{

    qDebug()<<"vastaanotettiin saldo signaali";
    wb=webToken; //alustetaan webtoken
    qDebug()<<wb;

    tilinumero=tili;
    QString site_url=MyUrl::getBaseUrl()+"/hae_saldo/"+tilinumero;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken=wb;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    saldoManager = new QNetworkAccessManager(this);

    connect(saldoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));

    reply = saldoManager->get(request);
}
