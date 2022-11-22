#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow();

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_linkButton_clicked();

    void on_loginButton_clicked();

    void loginFinished(QNetworkReply *rep);

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
