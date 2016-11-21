#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "phonebook.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    book = new Book;
    addd = new AddDialog(this);

    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(openAdd()));
    connect(addd, SIGNAL(accepted()), this, SLOT(addEntry()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(selectList()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteFromList()));
    ui->deleteButton->setEnabled(false);

    selectList();
}

void MainWindow::addEntry(){
    book->add(addd->lineEdit->text(), addd->lineEdit_2->text());
    displayList();
}

void MainWindow::openAdd(){
    addd->lineEdit->setFocus();
    addd->lineEdit->clear();
    addd->lineEdit_2->clear();
    addd->exec();
}

void MainWindow::selectList(){
    int index = ui->listWidget->currentRow();
    if(index >= 0){
         ui->deleteButton->setEnabled(true);
    }
}
void MainWindow::deleteFromList(){

    int index = ui->listWidget->currentRow();
    if(index >= 0){
        ui->deleteButton->setEnabled(false);
        book->deleteAtIndex(index);
        displayList();
    }
}

void MainWindow::displayList(){
    ui->listWidget->clear();
    for(Entry e : book->getAll()){
        ui->listWidget->addItem(e.getName() + " --- " + e.getNumber());
    }
}

MainWindow::~MainWindow()
{
    delete addd;
    delete ui;
}
