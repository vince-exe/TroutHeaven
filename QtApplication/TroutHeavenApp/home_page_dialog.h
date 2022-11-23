#ifndef HOME_PAGE_DIALOG_H
#define HOME_PAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class HomePageDialog;
}

class HomePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HomePageDialog(QWidget *parent = nullptr);

    static bool isFishing;

    ~HomePageDialog();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::HomePageDialog *ui;
};

#endif // HOME_PAGE_DIALOG_H
