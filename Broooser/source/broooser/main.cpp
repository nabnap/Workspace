#include "browser.h"
#include "browserwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QStyle>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon(QIcon(QLatin1String(":simplebrowser.svg")));

    QDir dir;
    qDebug() << dir.absolutePath();
    QFile file("stylesheet.qss");
    if(file.open(QFile::ReadOnly)){
        QString stylesheet = QLatin1String(file.readAll());
        a.setStyleSheet(stylesheet);
        qDebug() << "Read stylesheet";
        file.close();
    }else{
        qDebug() << "Failed Read stylesheet";
    }
    BrowserWindow *win = new BrowserWindow(nullptr, nullptr);
    Browser::instance().addWindow(win);

    return a.exec();

}
