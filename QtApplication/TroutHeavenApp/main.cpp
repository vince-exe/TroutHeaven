#include "login_window.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();
    w.exec();

    return a.exec();
}
