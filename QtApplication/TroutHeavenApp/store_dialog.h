#ifndef STORE_DIALOG_H
#define STORE_DIALOG_H

#include <QDialog>

namespace Ui {
class StoreDialog;
}

class StoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StoreDialog(QWidget *parent = nullptr);
    ~StoreDialog();

private:
    Ui::StoreDialog *ui;
};

#endif // STORE_DIALOG_H
