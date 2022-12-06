#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "korttiwindow.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogin_clicked();
    void loginSlot (QNetworkReply *reply);
    void timeoutSlot(); //uloskirjautuminen
    void deleted (QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    KorttiWindow *objectKorttiWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString id_kortti;
    int kierros;
};
#endif // MAINWINDOW_H
