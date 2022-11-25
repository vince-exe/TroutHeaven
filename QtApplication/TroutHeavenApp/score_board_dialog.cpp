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
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QJsonArray>

#include "application_utilities.h"

/* create the models */
QStandardItemModel* modelCart = new QStandardItemModel();

/* define the StringList */
QStringList horizontalHeaderCart;
QStringList verticalHeaderCart;

/* return an item pointer with the text aligned */
QStandardItem* getItem(QString string) {
    QStandardItem* item = new QStandardItem;
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(string);

    return item;
}

void printTable(QStandardItemModel* model, QTableView* table, QJsonArray array) {
    int i = 0;
    for(auto it : array) {
        model->setItem(i, 0, getItem(it.toObject()["nickname"].toString()));
        model->setItem(i, 1, getItem(QString::number(it.toObject()["score"].toDouble())));
        model->setItem(i, 2, getItem(QString::number(it.toObject()["money"].toDouble())));
        i++;
    }

    /* set the model to the table */
    table->setModel(model);

}

ScoreBoardDialog::ScoreBoardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreBoardDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    this->getPlayersList();
    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 29, 40));

    /* create the columns */
    horizontalHeaderCart.append("Nick");
    horizontalHeaderCart.append("Score");
    horizontalHeaderCart.append("Money");
    /* set the model */
    modelCart->setHorizontalHeaderLabels(horizontalHeaderCart);
    modelCart->setVerticalHeaderLabels(verticalHeaderCart);
    /* table settings */
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->verticalHeader()->setDefaultSectionSize(40);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ScoreBoardDialog::~ScoreBoardDialog() {
    horizontalHeaderCart.clear();
    verticalHeaderCart.clear();
    delete ui;
}

void ScoreBoardDialog::getPlayersListFinished(QNetworkReply *rep) {
    if(!(rep->error() == QNetworkReply::NoError)) {
        qDebug() << "\nErrors: " << (QString) rep->readAll();
        return;
    }

    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonObject jObj = jDoc.object();

    printTable(modelCart, ui->tableView, jObj["playersList"].toArray());
}

void ScoreBoardDialog::getPlayersList() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getPlayersListFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getPlayersList);
    QNetworkRequest request(url);

    manager->get(request);
}
