#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_color.h"
#include "colordialog.h"
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QColorDialog>

#include <QSettings>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    ui->setupUi(this);

    updateColor(); //Set the color to the last color used

    //Connect right click to showContectMenu method
    connect(this, &MainWindow::customContextMenuRequested, this, &MainWindow::showContextMenu);

    //Create the timer, do a singleshot to set time immediately. Then, start the timer and tick every second
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->singleShot(0, this, SLOT(updateTime()));
    timer->start(1000);

}

void MainWindow::updateTime(){
    QTime t = QTime::currentTime();
    if(t.hour() > 12) t = t.addSecs(3600 * 12);
    ui->lcdNumber->display(t.toString("hh:mm"));

}
void MainWindow::updateColor(){

    QSettings settings("Group2Dev","FancyClock");
    settings.beginGroup("ClockColor");
    if(settings.contains("lcd/color")){
        QColor c;
        c.setRgba(settings.value("lcd/color").toUInt());
        QPalette p = ui->lcdNumber->palette();
        p.setColor(QPalette::Foreground, c);
        ui->lcdNumber->setPalette(p);

    }
    settings.endGroup();

}

void MainWindow::colorDialog(){
    ColorDialog *cd = new ColorDialog(this);
    connect(cd, SIGNAL(accepted()), this, SLOT(updateColor()));
    cd->exec();
}

void MainWindow::showContextMenu(const QPoint &pos){
    QMenu contextMenu;
    contextMenu.addAction(QString("Options"), this, SLOT(colorDialog()));
    contextMenu.addAction(QString("Exit"), this, SLOT(close()));
    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        emit customContextMenuRequested(e->pos());
    }else{
        QMainWindow::mouseReleaseEvent(e);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    m_mousePos = e->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *e){
    this->move(e->globalPos() - m_mousePos);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
}
