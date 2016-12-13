#ifndef WEBVIEW_H
#define WEBVIEW_H
#include <QWebEngineView>
#include "jsonmanager.h"
class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = nullptr);
    bool isWebActionEnabled(QWebEnginePage::WebAction webAction) const;
signals:
    void webActionEnabledChanged(QWebEnginePage::WebAction webAction, bool enabled);
private:
    void createWebActionTrigger(QWebEnginePage *page, QWebEnginePage::WebAction);
    JsonManager *m_json;
};

#endif // WEBVIEW_H
