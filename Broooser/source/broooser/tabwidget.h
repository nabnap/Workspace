#ifndef TABWIDGET_H
#define TABWIDGET_H
#include "webview.h"
#include <QTabWidget>
#include <QWebEngineView>
#include <QUrl>
class TabWidget : public QTabWidget
{
        Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);
    WebView  *createTab(bool mcur, QUrl *url = nullptr);
    void setUrl(const QUrl url);
    void setupView(WebView *view);
    void closeTab(int index);
    void closeAllTabs();
    WebView *currentWebView() const;
    WebView *webViewAt(int index) const;
signals:
    void iconChanged(const QIcon &icon);
    void urlChanged(const QUrl &url);
    void tabClosed();
    void webActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
public slots:
    void triggerWebPageAction(QWebEnginePage::WebAction action);
private slots:
    void handleCurrentChanged(int index);
};

#endif // TABWIDGET_H
