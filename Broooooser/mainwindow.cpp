#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TabWidget *tabs = new TabWidget(ui->centralWidget);

    tabs->AddTab();

}

MainWindow::~MainWindow()
{
    delete tabs;
    delete ui;
}
