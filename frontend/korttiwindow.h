#ifndef KORTTIWINDOW_H
#define KORTTIWINDOW_H

#include <QDialog>

namespace Ui {
class KorttiWindow;
}

class KorttiWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KorttiWindow(QString id_kortti,QWidget *parent = nullptr);
    ~KorttiWindow();

    const QString &getWebToken() const;
    void setWebToken(const QString &newWebToken);

signals:
    void timeout();

private slots:
    void on_btnTilitapahtumat_clicked();

    void on_btnSaldo_clicked();

    void on_btnNostaRahaa_clicked();

    void on_btnSiirraRahaa_clicked();

    void on_btnReturn_clicked();

    void on_btnLogout_clicked();

private:
    Ui::KorttiWindow *ui;
    QString webToken;
    QString kortti;
};

#endif // KORTTIWINDOW_H
