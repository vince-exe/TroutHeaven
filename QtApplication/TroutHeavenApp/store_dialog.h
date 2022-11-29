#ifndef STORE_DIALOG_H
#define STORE_DIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QMap>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class StoreDialog;
}

class StoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StoreDialog(QWidget *parent = nullptr);

    ~StoreDialog();

    void checkSpinBoxes(QMap<QString, int>* map,  QString key, QSpinBox* spinBox);

    void updatePlayerMoney();

    void updatePlayerScore();

    bool doneBtnCheck();

    void clearStoreMap();

private slots:
    void on_doneBtn_clicked();

    void updatePlayerMoneyFinished(QNetworkReply* rep);

    void updatePlayerScoreFinished(QNetworkReply* rep);

private:
    Ui::StoreDialog *ui;
};

#endif // STORE_DIALOG_H
