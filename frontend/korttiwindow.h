#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>
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
    void timeout();
    void tilitapahtumat(QByteArray);

public slots:
    //laita kommentiksi jos paska
    void tulosta(QString);

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
};

#endif // KORTTIWINDOW_H
