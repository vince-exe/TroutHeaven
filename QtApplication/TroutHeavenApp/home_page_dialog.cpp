#include "home_page_dialog.h"
#include "ui_home_page_dialog.h"

bool HomePageDialog::isFishing = false;

HomePageDialog::HomePageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomePageDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));
    ui->statusLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 20, 40));
    ui->startButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->stopButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->scoreBoardButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->optionsButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));

    this->isFishing = false;
    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");
}

HomePageDialog::~HomePageDialog() {
    delete ui;
}

void HomePageDialog::on_startButton_clicked() {
    if(this->isFishing) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(0, 100, 0);");
    this->isFishing = true;
}

void HomePageDialog::on_stopButton_clicked() {
    if(!this->isFishing) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");
    this->isFishing = false;
}

