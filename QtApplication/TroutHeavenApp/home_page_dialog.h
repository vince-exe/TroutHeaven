#ifndef HOME_PAGE_DIALOG_H
#define HOME_PAGE_DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class HomePageDialog;
}

class HomePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HomePageDialog(QWidget *parent = nullptr);

    static bool isFishing;

    static QString email;

    static QString password;

    ~HomePageDialog();

    void getNicknameFromServer();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void getNicknameReqFinished(QNetworkReply *rep);

    void on_scoreBoardButton_clicked();

private:
    Ui::HomePageDialog *ui;
};

#endif // HOME_PAGE_DIALOG_H
