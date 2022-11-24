#ifndef SCORE_BOARD_DIALOG_H
#define SCORE_BOARD_DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class ScoreBoardDialog;
}

class ScoreBoardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoardDialog(QWidget *parent = nullptr);

    ~ScoreBoardDialog();

    void getPlayersList();

private slots:
    void getPlayersListFinished(QNetworkReply *rep);

private:
    Ui::ScoreBoardDialog *ui;
};

#endif // SCORE_BOARD_DIALOG_H
