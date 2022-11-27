#include "stats_dialog.h"
#include "ui_stats_dialog.h"

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));
}

StatsDialog::~StatsDialog() { delete ui; }
