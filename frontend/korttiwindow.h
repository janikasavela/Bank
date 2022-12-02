#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>
#include "tilitapahtumat.h"
#include <QStringList>

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
    void tulosta_Tilitapahtumat(QStringList,QString,QString,QString);

private slots:
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnNostaRahaa_clicked();
    void on_btnSiirraRahaa_clicked();
    void on_btnReturn_clicked();
    void on_btnLogout_clicked();

private:
    Ui::KorttiWindow *ui;
    QByteArray webToken;
    QString kortti;
    Tilitapahtumat *objectTilitapahtumat;
    QString alustaSivut(QStringList, int, int);
};

#endif // KORTTIWINDOW_H
