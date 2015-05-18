#include "camerafeed.h"
#include <QApplication>
#include <QWidget>
#include "login.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login window;
    window.showFullScreen();
    window.setWindowTitle("Login");
    window.show();

    return a.exec();


}
