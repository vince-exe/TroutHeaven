#include "stats_dialog.h"
#include "ui_stats_dialog.h"

#include "application_utilities.h"
#include "home_page_dialog.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QJsonArray>

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));

    this->getPlayerStats();

    ui->acciugaLabel->setText(QString::number(ApplicationUtilities::statsMap["acciuga"]));
    ui->calamaroLabel->setText(QString::number(ApplicationUtilities::statsMap["calamaro"]));
    ui->totanoLabel->setText(QString::number(ApplicationUtilities::statsMap["totano"]));
    ui->trotaLabel->setText(QString::number(ApplicationUtilities::statsMap["trota"]));
    ui->tonnettoLabel->setText(QString::number(ApplicationUtilities::statsMap["tonnetto"]));
    ui->anguillaLabel->setText(QString::number(ApplicationUtilities::statsMap["anguilla"]));
}

StatsDialog::~StatsDialog() { delete ui; }

void StatsDialog::getPlayerStats() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getPlayerStatsFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getPlayerStats);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = HomePageDialog::email;

    QJsonDocument doc(obj);
    manager->post(request, doc.toJson());
}

void StatsDialog::getPlayerStatsFinished(QNetworkReply *rep) {
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString repStr = (QString) rep->readAll();

        if(repStr == LoginErrors::UnprocessableEntity || repStr == LoginErrors::Unauthorized) {
            QMessageBox::critical(0, "Fatal Error", "The application failed to comunicate with the server");
            return;
        }
        QMessageBox::critical(0, "Fatal Error", "Internal application error...");
        return;
    }

    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonObject object = jDoc.object()["user"].toObject();

    ui->moneyLabel->setText(QString::number(object["money"].toDouble()));
    ui->scoreLabel->setText(QString::number(object["score"].toDouble()));
}
