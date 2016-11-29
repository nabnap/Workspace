#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setStyleSheet("QTabWidget::pane { border:none;"
                    "background-color:white; }"
                    "QTabBar::tab{ border-right:1px solid black; padding:5px 10px;}"
                    "QTabBar::tab:!selected {background-color:gray;}"
                    "QTabBar::tab:selected { background-color:white; border-right:none;}"
                    );

    return a.exec();
}
