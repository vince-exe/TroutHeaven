#include "store_dialog.h"
#include "ui_store_dialog.h"

#include "application_utilities.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#include "home_page_dialog.h"

StoreDialog::StoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));

    ui->acciugaSpin->setMaximum(ApplicationUtilities::storeMap["acciuga"]);
    ui->acciugaSpin->setMinimum(0);
    ui->acciugaSpin->setValue(ApplicationUtilities::storeMap["acciuga"]);

    ui->anguillaSpin->setMaximum(ApplicationUtilities::storeMap["anguilla"]);
    ui->anguillaSpin->setMinimum(0);
    ui->anguillaSpin->setValue(ApplicationUtilities::storeMap["anguilla"]);

    ui->calamaroSpin->setMaximum(ApplicationUtilities::storeMap["calamaro"]);
    ui->calamaroSpin->setMinimum(0);
    ui->calamaroSpin->setValue(ApplicationUtilities::storeMap["calamaro"]);

    ui->totanoSpin->setMaximum(ApplicationUtilities::storeMap["totano"]);
    ui->totanoSpin->setMinimum(0);
    ui->totanoSpin->setValue(ApplicationUtilities::storeMap["totano"]);

    ui->tonnettoSpin->setMaximum(ApplicationUtilities::storeMap["tonnetto"]);
    ui->tonnettoSpin->setMinimum(0);
    ui->tonnettoSpin->setValue(ApplicationUtilities::storeMap["tonnetto"]);

    ui->trotaSpin->setMaximum(ApplicationUtilities::storeMap["trota"]);
    ui->trotaSpin->setMinimum(0);
    ui->trotaSpin->setValue(ApplicationUtilities::storeMap["trota"]);

    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "acciuga", ui->acciugaSpin);
    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "anguilla", ui->anguillaSpin);
    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "calamaro", ui->calamaroSpin);
    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "totano", ui->totanoSpin);
    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "tonnetto", ui->tonnettoSpin);
    this->checkSpinBoxes(&ApplicationUtilities::storeMap, "trota", ui->trotaSpin);
}

StoreDialog::~StoreDialog() {
    delete ui;
}

void StoreDialog::checkSpinBoxes(QMap<QString, int> *map, QString key, QSpinBox *spinBox) {
    if(!map->value(key)) {
        spinBox->setMaximum(0);
        spinBox->setMinimum(0);
    }
}

void StoreDialog::updatePlayerMoneyFinished(QNetworkReply *rep) {
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString repStr = (QString) rep->readAll();

        if(repStr == ApiErrors::InsufficientCredit) {
            QMessageBox::warning(0, "Warning", "Insufficient Credit :/");
            return;
        }
        QMessageBox::critical(0, "Fatal Error", "Internal application error...");
        return;
    }

    this->updatePlayerScore();
}

void StoreDialog::updatePlayerScoreFinished(QNetworkReply *rep) {
    if(!(rep->error() == QNetworkReply::NoError)) {
        QMessageBox::critical(0, "Fatal Error", "Internal application error...");
        return;
    }
    QMessageBox::information(0, "Success", "All fish were successfully sold");

    this->clearStoreMap();
    this->close();
}

void StoreDialog::updatePlayerMoney() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(updatePlayerMoneyFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::updtPlayerMoney);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = HomePageDialog::email;
    obj["cAcciuga"] = ui->acciugaSpin->value();
    obj["cAnguilla"] = ui->anguillaSpin->value();
    obj["cCalamaro"] = ui->calamaroSpin->value();
    obj["cTotano"] = ui->totanoSpin->value();
    obj["cTonnetto"] = ui->tonnettoSpin->value();
    obj["cTrota"] = ui->trotaSpin->value();

    QJsonDocument doc(obj);
    manager->post(request, doc.toJson());
}

void StoreDialog::updatePlayerScore() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(updatePlayerScoreFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::updtPlayerScore);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = HomePageDialog::email;
    obj["cAcciuga"] = ui->acciugaSpin->value();
    obj["cAnguilla"] = ui->anguillaSpin->value();
    obj["cCalamaro"] = ui->calamaroSpin->value();
    obj["cTotano"] = ui->totanoSpin->value();
    obj["cTonnetto"] = ui->tonnettoSpin->value();
    obj["cTrota"] = ui->trotaSpin->value();

    QJsonDocument doc(obj);
    manager->post(request, doc.toJson());
}

bool StoreDialog::doneBtnCheck() {
    if(ui->anguillaSpin->value()) { return true; }
    if(ui->acciugaSpin->value()) { return true; }
    if(ui->calamaroSpin->value()) { return true; }
    if(ui->totanoSpin->value()) { return true; }
    if(ui->tonnettoSpin->value()) { return true; }
    if(ui->trotaSpin->value()) { return true; }

    return false;
}

void StoreDialog::clearStoreMap() {
    ApplicationUtilities::storeMap["acciuga"] = 0;
    ApplicationUtilities::storeMap["anguilla"] = 0;
    ApplicationUtilities::storeMap["calamaro"] = 0;
    ApplicationUtilities::storeMap["totano"] = 0;
    ApplicationUtilities::storeMap["trota"] = 0;
    ApplicationUtilities::storeMap["tonnetto"] = 0;
}

void StoreDialog::on_doneBtn_clicked() {
    /* nothing to sell */
    if(!this->doneBtnCheck()) { this->close(); return; }

    this->updatePlayerMoney();
}
