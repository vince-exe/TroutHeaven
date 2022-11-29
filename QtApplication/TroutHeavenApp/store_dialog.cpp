#include "store_dialog.h"
#include "ui_store_dialog.h"

StoreDialog::StoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));
    ui->acciugaSpin->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->anguillaSpin->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->totanoSpin->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->trotaSpin->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->calamaroSpin->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
}

StoreDialog::~StoreDialog() {
    delete ui;
}
