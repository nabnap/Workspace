#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Deletes the second tab
    //ui->tabWidget->removeTab(1);
    ui->tabWidget->clear();
   //ui->tabWidget->setStyleSheet("border-radius:0px;");
    //QWidget *newTab = new QWidget(ui->tabWidget);

    QWebEngineView *view = new QWebEngineView(ui->tabWidget);
    view->setUrl(QUrl(QStringLiteral("http://www.qt.io")));
    //view.resize(1024, 750);
    view->show();


    QWebEnginePage *webPage = view->page();

    connect(view, &QWebEngineView::titleChanged, [this, view](const QString &title) {
        int index = ui->tabWidget->indexOf(view);
        if (index != -1){
            QString t = title;
            if(t.length() > 25 ){
                t.chop(t.length()-25);
                t.append("...");
            }



            ui->tabWidget->setTabText(index, t);
        }
            //setTabText(index, title);
        //if (currentIndex() == index)
        //    emit titleChanged(title);
    });

    ui->tabWidget->addTab(view, tr("New Tab"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
