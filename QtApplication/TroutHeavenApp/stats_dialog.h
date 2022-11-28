#ifndef STATS_DIALOG_H
#define STATS_DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = nullptr);

    ~StatsDialog();

    void getPlayerStats();

private slots:
    void getPlayerStatsFinished(QNetworkReply *rep);

private:
    Ui::StatsDialog *ui;
};

#endif // STATS_DIALOG_H
