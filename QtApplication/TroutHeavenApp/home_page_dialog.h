#ifndef HOME_PAGE_DIALOG_H
#define HOME_PAGE_DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

#include <thread>

struct TrackActivity {
    int countAcciuga, countAnguilla, countCalamro, countTotano, countTonnetto, countTrota;
};

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

    static TrackActivity trackActivity;

    ~HomePageDialog();

    void getNicknameFromServer();

    void getFishFromServer();

    void updatePlayerStats();

    void printHistoryText(const QString& string);

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void getNicknameReqFinished(QNetworkReply *rep);

    void getFishFromServerFinished(QNetworkReply *rep);

    void updatePlayerStatsFinished(QNetworkReply *rep);

    void on_scoreBoardButton_clicked();

    void on_storeBtn_clicked();

    void on_storeBtn_2_clicked();

    void on_statsButton_clicked();

private:
    Ui::HomePageDialog *ui;

    std::thread* fishThread;
};

void fishFunc(HomePageDialog*);

QString checkNumber(double n, TrackActivity* trackActivity);

#endif // HOME_PAGE_DIALOG_H
