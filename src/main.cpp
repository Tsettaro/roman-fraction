#include "../include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Paksurion Group");
    a.setOrganizationDomain("paksurion.ru");
    a.setApplicationName("ROMFRAC");
    a.setApplicationVersion("1.1");
    MainWindow w;
    w.show();
    return a.exec();
}
