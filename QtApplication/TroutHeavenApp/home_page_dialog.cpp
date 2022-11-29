#include "home_page_dialog.h"
#include "ui_home_page_dialog.h"

bool HomePageDialog::isFishing = false;

bool HomePageDialog::canFish = false;

QString HomePageDialog::email;

QString HomePageDialog::password;

TrackActivity HomePageDialog::trackActivity;

#include "application_utilities.h"
#include "fish.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>
#include <QRandomGenerator>

#include <chrono>

/* forms */
#include "score_board_dialog.h"
#include "stats_dialog.h"
#include "store_dialog.h"

HomePageDialog::HomePageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomePageDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));
    ui->startButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->stopButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->scoreBoardButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->statsButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->myNickLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 14, 40));

    this->isFishing = false;
    this->canFish = false;

    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");

    this->getNicknameFromServer();
    this->getFishFromServer();
}

HomePageDialog::~HomePageDialog() {
    delete ui;
}

void HomePageDialog::getNicknameReqFinished(QNetworkReply *rep) {
    /* check the error */
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString strRep = (QString) rep->readAll();

        if(strRep == ApiErrors::UnprocessableEntity) {
            QMessageBox::critical(0, "Fatal Error", "The application failed to load the resources\n[ ERROR MESSAGE ]: " + strRep);
            return; this->close();
        }
        qDebug() << strRep;
        QMessageBox::critical(0, "Fatal Error", "The application failed the request of the nickname");
        return; this->close();
    }

    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonObject jObj = jDoc.object();

    /* set the nickname */
    ui->myNickLabel->setText("You: " + jObj["nickname"].toString());
}

void HomePageDialog::getFishFromServerFinished(QNetworkReply *rep) {
    /* check the error */
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString strRep = (QString) rep->readAll();
        QMessageBox::critical(0, "Fatal Error", "The application failed the request to the server");
        return; this->close();
    }

    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonArray arr = jDoc.object()["fishList"].toArray();

    /* save each fish in the fish map ( key = fish name ) */
    for(auto i : arr) {
        QJsonObject j = i.toObject();
        ApplicationUtilities::statsMap.insert(j["name"].toString(), 0);
        ApplicationUtilities::storeMap.insert(j["name"].toString(), 0);
    }
    this->canFish = true;
}

void HomePageDialog::getNicknameFromServer() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getNicknameReqFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getNicknameApiUrl);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = HomePageDialog::email;

    QJsonDocument doc(obj);
    manager->post(request, doc.toJson());
}

void HomePageDialog::getFishFromServer() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getFishFromServerFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getFishApiUrl);
    QNetworkRequest request(url);

    manager->get(request);
}

void HomePageDialog::updatePlayerStatsFinished(QNetworkReply *rep) {
    /* check the error */
    if(!(rep->error() == QNetworkReply::NoError)) {
        QMessageBox::critical(0, "Fatal Error", "The application failed to update the user stats");
        return; this->close();
    }
    this->isFishing = false;
}

void HomePageDialog::updatePlayerStats() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(updatePlayerStatsFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::updtPlayerStatsAPIUrl);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = this->email;
    obj["cAcciuga"] = this->trackActivity.countAcciuga;
    obj["cAnguilla"] = this->trackActivity.countAnguilla;
    obj["cCalamaro"] = this->trackActivity.countCalamro;
    obj["cTotano"] = this->trackActivity.countTotano;
    obj["cTonnetto"] = this->trackActivity.countTonnetto;
    obj["cTrota"] = this->trackActivity.countTrota;

    QJsonDocument doc(obj);
    manager->post(request, doc.toJson());
}

void HomePageDialog::printHistoryText(const QString &string) {
    /* display the content to the QPlainTextEdit */
    QTextCursor textCursor = QTextCursor(ui->historyTextEdit->document());
    textCursor.movePosition(QTextCursor::End);
    textCursor.insertText(string);
}

QString checkNumber(double n, TrackActivity* trackActivity) {
    double j;

    if(n >= 0 && n <= 50) {
        j = QRandomGenerator::global()->bounded(0, 5);

        if(j == 0 || j == 1) {
            trackActivity->countAcciuga++;
            ApplicationUtilities::statsMap["acciuga"] += 1;
            ApplicationUtilities::storeMap["acciuga"] += 1;
            return "acciuga";
        }
        else if(j == 2) {
            trackActivity->countAnguilla++;
            ApplicationUtilities::statsMap["anguilla"] += 1;
            ApplicationUtilities::storeMap["anguilla"] += 1;
            return "anguilla";
        }
        else {
            trackActivity->countCalamro++;
            ApplicationUtilities::statsMap["calamaro"] += 1;
            ApplicationUtilities::storeMap["calamaro"] += 1;
            return  "calamaro";
        }
    }
    if(n <= 90) {
        j = QRandomGenerator::global()->bounded(0, 4);

        if(j == 0 || j == 1) {
            trackActivity->countTotano++;
            ApplicationUtilities::statsMap["totano"] += 1;
            ApplicationUtilities::storeMap["totano"] += 1;
            return "totano";
        }
        else {
            trackActivity->countTonnetto++;
            ApplicationUtilities::statsMap["tonnetto"] += 1;
            ApplicationUtilities::storeMap["tonnetto"] += 1;
            return "tonnetto";
        }
    }
    trackActivity->countTrota++;
    ApplicationUtilities::statsMap["trota"] += 1;
    ApplicationUtilities::storeMap["trota"] += 1;
    return "trota";
}

void fishFunc(HomePageDialog* this_) {
    HomePageDialog::trackActivity = {0, 0, 0, 0, 0, 0};

    while(this_->isFishing) {
        std::this_thread::sleep_for(UserStats::fishTime);

        if(this_->isFishing) {
            QString keyFish = checkNumber(QRandomGenerator::global()->bounded(0, 100), &HomePageDialog::trackActivity);
            this_->printHistoryText("[ BOT ]: Catch +1 of " + keyFish + "\n");
        }
    }
}

void HomePageDialog::on_startButton_clicked() {
    if(this->isFishing || !this->canFish) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(0, 100, 0);");
    this->isFishing = true;

    this->ui->historyTextEdit->clear();
    this->printHistoryText("[ BOT ]: Ready to catch some fish\n\n");

    /* start the thread */
    this->fishThread = new std::thread(fishFunc, this);
}

void HomePageDialog::on_stopButton_clicked() {
    if(!this->isFishing) { return; }
    this->isFishing = false;

    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");

    this->printHistoryText("\n[ BOT ]: Nice catch bye!\n");

    if(this->fishThread->joinable()) {
        this->fishThread->join();
    }
    /* send the fish to the server */
    this->updatePlayerStats();
}

void HomePageDialog::on_scoreBoardButton_clicked() {
    if(this->isFishing) {
        QMessageBox::information(0, "Info Application", "You have to stop your fishing session");
        return;
    }

    ScoreBoardDialog scoreBoardDialog;

    scoreBoardDialog.setModal(true);
    scoreBoardDialog.show();
    scoreBoardDialog.exec();
}

void HomePageDialog::on_storeBtn_clicked() {
    if(this->isFishing) {
        QMessageBox::information(0, "Info Application", "You have to stop your fishing session");
        return;
    }
    StoreDialog storeDialog;

    storeDialog.setModal(true);
    storeDialog.show();
    storeDialog.exec();
}

void HomePageDialog::on_statsButton_clicked() {
    StatsDialog statsDialog;

    statsDialog.setModal(true);
    statsDialog.show();
    statsDialog.exec();
}

void HomePageDialog::on_inventaryBtn_clicked() {
    if(this->isFishing) {
        QMessageBox::information(0, "Info Application", "You have to stop your fishing session");
        return;
    }
}

