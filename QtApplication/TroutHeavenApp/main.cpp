#include "login_window.h"

#include <QApplication>

/* temporary */
#include "home_page_dialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //LoginWindow w;
    //w.show();

    HomePageDialog w;
    w.show();
    w.exec();
    return a.exec();
}
