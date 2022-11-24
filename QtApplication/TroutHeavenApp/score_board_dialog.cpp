#include "score_board_dialog.h"
#include "ui_score_board_dialog.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#include "application_utilities.h"

ScoreBoardDialog::ScoreBoardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoardDialog) {
    ui->setupUi(this);

    this->getPlayersList();
}

ScoreBoardDialog::~ScoreBoardDialog() {
    delete ui;
}

void ScoreBoardDialog::getPlayersListFinished(QNetworkReply *rep) {
    if(!(rep->error() == QNetworkReply::NoError)) {
        qDebug() << "\nErrors: " << (QString) rep->readAll();
        return;
    }

    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonObject jObj = jDoc.object();

    qDebug() << jObj;
}

void ScoreBoardDialog::getPlayersList() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getPlayersListFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getPlayersList);
    QNetworkRequest request(url);

    manager->get(request);
}
