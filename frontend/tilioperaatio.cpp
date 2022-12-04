#include "tilioperaatio.h"
#include "myurl.h"

tilioperaatio::tilioperaatio(QString aTili,QObject *parent) : QObject{parent}
{
    tilinumero=aTili; //alustetaan käytettävä tili heti samalla kun luodaan koosteyhteys
}

void tilioperaatio::nostoSlot(QNetworkReply *reply)
{

}

void tilioperaatio::siirtoSlot(QNetworkReply *reply)
{

}void tilioperaatio::tilioperaatio_info_done(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
       QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
       QJsonArray json_array = json_doc.array();

   //siirretään haetut tiedot muuttujiin
       foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           tilinOmistaja=json_obj["nimi"].toString();
           saldo=QString::number(json_obj["saldo"].toInt());
       }

       qDebug()<<"vie asiakas info signal";
       emit vie_asiakas_info(tilinOmistaja,saldo);
       //emit tilitapahtumat_nayta(tapahtumat,tilinOmistaja,saldo,tilinumero); //lähetetään haetut tiedot tilitapahtumien tulostus slottiin korttiwindowille.

}
void tilioperaatio::tilioperaatio_info(QByteArray webToken, QString aTili)
{
   qDebug()<<"vastaanotettiin info signal";
   wb=webToken; //alustetaan webtoken
   //qDebug()<<wb;

   tilinumero=aTili;
   QString site_url=MyUrl::getBaseUrl()+"/tili/info/"+tilinumero;
   QNetworkRequest request((site_url));
   //WEBTOKEN ALKU
   QByteArray myToken=wb;
   request.setRawHeader(QByteArray("Authorization"),(myToken));
   //WEBTOKEN LOPPU
   operationManager = new QNetworkAccessManager(this);

   connect(operationManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tilioperaatio_info_done(QNetworkReply*)));

   reply = operationManager->get(request);

}
