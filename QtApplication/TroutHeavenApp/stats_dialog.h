#ifndef STATS_DIALOG_H
#define STATS_DIALOG_H

#include <QDialog>

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = nullptr);
    ~StatsDialog();

private:
    Ui::StatsDialog *ui;
};

#endif // STATS_DIALOG_H
