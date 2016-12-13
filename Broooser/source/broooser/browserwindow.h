#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include "tabwidget.h"
#include "urlline.h"
#include "jsonmanager.h"

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(QWidget *parent = 0, QString *session = 0);
    ~BrowserWindow();
private:
    QHBoxLayout *setupTopBar();
    QMenu* createBrowserMenu();
    void handleNewWindowTriggered(QString *session = 0);


    bool saveSession();


    TabWidget *m_tabWidget;
    UrlLine *m_urlLine;
    QToolButton *m_back, *m_forward, *m_refresh, *m_stop, *m_fork, *m_menu;
    QLabel *m_sLabel;
    QString *m_session;
    //QMenu *m_bmenu;
    JsonManager *m_json;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // BROWSERWINDOW_H
