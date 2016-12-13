#include "browser.h"
#include "browserwindow.h"
#include <QDebug>
Browser::~Browser(){
    qDeleteAll(m_windows);
    m_windows.clear();
}

Browser &Browser::instance(){
    static Browser browser;
    return browser;
}

QVector<BrowserWindow*> Browser::windows(){
    return m_windows;
}


void Browser::addWindow(BrowserWindow *window){
    if(m_windows.contains(window)) return; //Do not add another window to array
    m_windows.push_back(window);
    QObject::connect(window, &QObject::destroyed, [this, window](){
        m_windows.removeOne(window);
        qDebug() << "Removed";
    });
    window->show();
}
