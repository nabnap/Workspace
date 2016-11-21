#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adddialog.h"
#include "phonebook.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openAdd();
    void addEntry();

    void selectList();
    void displayList();
    void deleteFromList();
private:
    Ui::MainWindow *ui;
    AddDialog *addd;
    Book *book;
};

#endif // MAINWINDOW_H
