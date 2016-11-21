#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QPoint m_mousePos;
private slots:
    void updateTime();
    void updateColor();
    void colorDialog();
    void showContextMenu(const QPoint &pos);
protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
