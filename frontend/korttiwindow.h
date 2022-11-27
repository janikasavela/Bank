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

private slots:
    void on_btnTilitapahtumat_clicked();

private:
    Ui::KorttiWindow *ui;
    QString webToken;
};

#endif // KORTTIWINDOW_H
