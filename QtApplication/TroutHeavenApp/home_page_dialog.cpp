#include "home_page_dialog.h"
#include "ui_home_page_dialog.h"

bool HomePageDialog::isFishing = false;

bool HomePageDialog::canFish = false;

QString HomePageDialog::email;

QString HomePageDialog::password;

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
#include <chrono>

/* forms */
#include "score_board_dialog.h"

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
    ui->optionsButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
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

        if(strRep == LoginErrors::UnprocessableEntity) {
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
        ApplicationUtilities::fishMap.insert(j["name"].toString(), Fish(j["name"].toString(), j["value"].toDouble(), j["score"].toDouble()));
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

void HomePageDialog::printHistoryText(const QString &string) {
    /* display the content to the QPlainTextEdit */
    QTextCursor textCursor = QTextCursor(ui->historyTextEdit->document());
    textCursor.movePosition(QTextCursor::End);
    textCursor.insertText(string);
}

void fishFunc(HomePageDialog* this_) {
    using namespace std::chrono_literals;

    while(this_->isFishing) {
        qDebug() << "pescando..\n";
        std::this_thread::sleep_for(2s);
    }
}

void HomePageDialog::on_startButton_clicked() {
    if(this->isFishing || !this->canFish) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(0, 100, 0);");
    this->isFishing = true;

    this->printHistoryText("[ BOT ]: Ready to catch some fish\n");

    /* start the thread */
    this->fishThread = new std::thread(fishFunc, this);
}

void HomePageDialog::on_stopButton_clicked() {
    if(!this->isFishing) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");
    this->isFishing = false;

    this->printHistoryText("[ BOT ]: Nice catch bye!\n");

    if(this->fishThread->joinable()) {
        this->fishThread->join();
    }
}

void HomePageDialog::on_scoreBoardButton_clicked() {
    ScoreBoardDialog scoreBoardDialog;

    scoreBoardDialog.setModal(true);
    scoreBoardDialog.show();
    scoreBoardDialog.exec();
}

