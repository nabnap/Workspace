#include "webview.h"
#include "jsonmanager.h"
#include <QWebEngineView>
#include <QAction>
#include <QMessageBox>
#include <QTimer>

WebView::WebView(QWidget *parent) : QWebEngineView(parent)
{
    m_json = new JsonManager(QString("temp.json"));
    createWebActionTrigger(page(), QWebEnginePage::Reload);
    createWebActionTrigger(page(), QWebEnginePage::Stop);
    createWebActionTrigger(page(), QWebEnginePage::Back);
    createWebActionTrigger(page(), QWebEnginePage::Forward);

    connect(this, &QWebEngineView::renderProcessTerminated,
            [this](QWebEnginePage::RenderProcessTerminationStatus termStatus, int statusCode) {
        QString status;
        switch (termStatus) {
        case QWebEnginePage::NormalTerminationStatus:
            status = tr("Render process normal exit");
            break;
        case QWebEnginePage::AbnormalTerminationStatus:
            status = tr("Render process abnormal exit");
            break;
        case QWebEnginePage::CrashedTerminationStatus:
            status = tr("Render process crashed");
            break;
        case QWebEnginePage::KilledTerminationStatus:
            status = tr("Render process killed");
            break;
        }
        QMessageBox::StandardButton btn = QMessageBox::question(window(), status,
                                                   tr("Render process exited with code: %1\n"
                                                      "Do you want to reload the page ?").arg(statusCode));
        if (btn == QMessageBox::Yes)
            QTimer::singleShot(0, [this] { reload(); });
    });

    connect(this, &QWebEngineView::loadProgress, [this](){
        if(m_json->isBlocked(page()->url()))
            this->stop();
    });
}

bool WebView::isWebActionEnabled(QWebEnginePage::WebAction webAction) const{
    return page()->action(webAction)->isEnabled();
}

void WebView::createWebActionTrigger(QWebEnginePage *page, QWebEnginePage::WebAction webAction){
    QAction *action = page->action(webAction);
    connect(action, &QAction::changed, [this, action, webAction]{
        emit webActionEnabledChanged(webAction, action->isEnabled());
    });
}
