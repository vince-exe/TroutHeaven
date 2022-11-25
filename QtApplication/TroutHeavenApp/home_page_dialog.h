#ifndef HOME_PAGE_DIALOG_H
#define HOME_PAGE_DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

#include <thread>

namespace Ui {
class HomePageDialog;
}

class HomePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HomePageDialog(QWidget *parent = nullptr);

    static bool isFishing;

    static bool canFish;

    static QString email;

    static QString password;

    ~HomePageDialog();

    void getNicknameFromServer();

    void getFishFromServer();

    void printHistoryText(const QString& string);

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void getNicknameReqFinished(QNetworkReply *rep);

    void getFishFromServerFinished(QNetworkReply *rep);

    void on_scoreBoardButton_clicked();

private:
    Ui::HomePageDialog *ui;

    std::thread* fishThread;
};

void fishFunc(HomePageDialog*);

#endif // HOME_PAGE_DIALOG_H
