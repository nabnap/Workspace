#include "tabwidget.h"
#include <QTabBar>
#include <QWidget>
#include <QLayout>
#include <QWebEngineView>
TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    QTabBar *tabBar = this->tabBar();
    tabBar->setTabsClosable(true);
    tabBar->setMovable(true);
    tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    parent->layout()->addWidget(this);
}
void TabWidget::AddTab(){
    QWebEngineView *view = new QWebEngineView(this);
    view->setUrl(QUrl(QStringLiteral("http://www.qt.io")));
    view->show();

    QWebEnginePage *webPage = view->page();

    connect(view, &QWebEngineView::titleChanged, [this, view](const QString &title) {
        int index = this->indexOf(view);
        if (index != -1){
            QString t = title;
            if(t.length() > 25 ){
                t.chop(t.length()-25);
                t.append("...");
            }


            this->setTabText(index, t);
        }
    });

    this->addTab(view, tr("New Tabs"));
}


