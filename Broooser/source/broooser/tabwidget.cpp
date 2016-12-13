#include "tabwidget.h"
#include "webview.h"
#include <QTabBar>
#include <QWebEngineView>
#include <QUrl>
#include <QAction>
#include <QThread>
TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->tabBar()->setTabsClosable(true);
    this->tabBar()->setMovable(true);

    connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);
    connect(this->tabBar(), &QTabBar::tabCloseRequested, this, [this](int index){
        closeTab(index);
        emit tabClosed();
    });
}


void TabWidget::handleCurrentChanged(int index){
    if(index != -1){
        WebView *view = webViewAt(index);
        if(!view->url().isEmpty())
            view->setFocus();
        emit urlChanged(view->url());
        QIcon icon = view->page()->icon();
        if(!icon.isNull())
            emit iconChanged(icon);
        else
            emit iconChanged(QIcon(QStringLiteral(":defaulticon.png")));
        emit webActionEnabledChanged(QWebEnginePage::Back, view->isWebActionEnabled(QWebEnginePage::Back));
        emit webActionEnabledChanged(QWebEnginePage::Forward, view->isWebActionEnabled(QWebEnginePage::Forward));
        emit webActionEnabledChanged(QWebEnginePage::Stop, view->isWebActionEnabled(QWebEnginePage::Stop));
        emit webActionEnabledChanged(QWebEnginePage::Reload,view->isWebActionEnabled(QWebEnginePage::Reload));
    }
}

void TabWidget::triggerWebPageAction(QWebEnginePage::WebAction action){
    qDebug() << "Action triggered!";
    if(WebView *view = currentWebView()){
        view->triggerPageAction(action);
        view->setFocus();
    }
}

WebView *TabWidget::createTab(bool mcur, QUrl *url){
    if(url == nullptr)
        url = new QUrl(QString("https://google.com"));
    WebView *view = new WebView();
    setupView(view);
    view->setUrl(*url);
    this->addTab(view, tr("New Tab"));
    if (mcur) this->setCurrentWidget(view);

    return view;
}

void TabWidget::setUrl(const QUrl url){
    WebView *view = this->currentWebView();
    if(view){
        view->setUrl(url);
    }
}
void TabWidget::setupView(WebView *view){
    connect(view, &QWebEngineView::titleChanged, [this,view](const QString &title){
        int index = indexOf(view);
        QString t(title);
        t.truncate(36);
        t.append(tr("..."));
        if(index != -1)
            setTabText(index, t);
    });
    connect(view, &QWebEngineView::iconChanged, [this, view](const QIcon &icon){
        int index = indexOf(view);
        QIcon ico = icon.isNull() ? QIcon(QStringLiteral(":defaulticon.png")) : icon;
        if (currentIndex() == index)
            emit iconChanged(ico);
    });
    connect(view, &QWebEngineView::urlChanged, [this, view](const QUrl &url){
        int index = indexOf(view);
        if(currentIndex() == index)
            emit urlChanged(url);
    });

    connect(view, &WebView::webActionEnabledChanged, [this, view](QWebEnginePage::WebAction webAction, bool enabled){
        if(currentIndex() == indexOf(view))
            emit webActionEnabledChanged(webAction, enabled);
    });
}

WebView *TabWidget::currentWebView() const{
    return this->webViewAt(this->currentIndex());
}
WebView *TabWidget::webViewAt(int i) const{
    return qobject_cast<WebView*>(this->widget(i));
}

void TabWidget::closeAllTabs(){
    for(int i = 0; i < count(); i++){
        closeTab(i);
    }
}

void TabWidget::closeTab(int index){

    if (WebView *view = webViewAt(index)) {
        //bool hasFocus = view->hasFocus();
        removeTab(index);
        //if (hasFocus && count() > 0)
        //    currentWebView()->setFocus();
        //if (count() == 0)
        //    createTab();
        view->deleteLater();
    }
}
