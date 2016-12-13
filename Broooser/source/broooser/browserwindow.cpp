#include "browser.h"
#include "browserwindow.h"
#include "jsonmanager.h"
#include <QVBoxLayout>
#include <QUrl>
#include <QCloseEvent>
#include <QToolButton>
#include <QSize>
#include <QStyle>
#include <QAction>
#include <QMenu>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

BrowserWindow::BrowserWindow(QWidget *parent, QString *session)
    : QMainWindow(parent)
{
    this->setWindowTitle(QString("Broooser"));
    //Setup the tabs
    m_json = new JsonManager(QString("temp.json"));
    m_tabWidget = new TabWidget(this);
    m_session = session;

    //Create the central widget
    QWidget *centralWidget = new QWidget(this);

    //Create the layout for the central widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    //Create the navigation layout
    QHBoxLayout *layout2 = this->setupTopBar();

    //Add the navigation layout and the tab widget
    layout->addLayout(layout2);
    layout->addWidget(m_tabWidget);

    //Set the layout of the central widget and set the central widget
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    //Create a beginning tab
    if(m_session){
        for(QUrl *u : m_json->getSessionUrls(m_session)){
            m_tabWidget->createTab(true, u);
        }
    }else{
        m_tabWidget->createTab(true, m_json->getHomepage());
    }



    //connections
    connect(m_tabWidget, &TabWidget::iconChanged, this, [this](const QIcon &icon){
        m_urlLine->setSiteIcon(icon);
    });
    connect(m_tabWidget, &TabWidget::urlChanged, this, [this](const QUrl &url){
        saveSession();
        m_urlLine->setUrl(url);
    });
    connect(m_tabWidget, &TabWidget::tabClosed, [this](){
        saveSession();
    });
    connect(m_tabWidget, &TabWidget::webActionEnabledChanged, this, [this](QWebEnginePage::WebAction action, bool enabled){
        switch (action) {
        case QWebEnginePage::Back:
            m_back->setEnabled(enabled);
            break;
        case QWebEnginePage::Forward:
            m_forward->setEnabled(enabled);
            break;
        case QWebEnginePage::Reload:
            m_refresh->setEnabled(enabled);
            if(enabled){
                m_refresh->show();
                m_stop->hide();
            }
            break;
        case QWebEnginePage::Stop:
            m_stop->setEnabled(enabled);
            if(enabled){
                m_refresh->hide();
                m_stop->show();
            }
            break;
        default:
            qWarning("Unhandled webActionChanged singal");
        }
    });


}

QHBoxLayout *BrowserWindow::setupTopBar(){
    QHBoxLayout *layout = new QHBoxLayout;

    m_urlLine = new UrlLine(this);

    m_back      = new QToolButton(this);
    m_forward   = new QToolButton(this);
    m_refresh   = new QToolButton(this);
    m_stop      = new QToolButton(this);
    m_fork      = new QToolButton(this);
    m_menu      = new QToolButton(this);
    m_sLabel    = new QLabel(this);

    m_sLabel->setText(tr("Python Learning"));

    m_fork->setToolTip(QString("Create a new session"));

    this->setStyleSheet("QToolButton{ border:none; padding:2px;}");

    m_back->setIcon(QIcon(QStringLiteral(":myIcons/back.png")));
    m_forward->setIcon(QIcon(QStringLiteral(":myIcons/next.png")));
    m_refresh->setIcon(QIcon(QStringLiteral(":myIcons/refresh.png")));
    m_stop->setIcon(QIcon(QStringLiteral(":myIcons/srefresh.png")));
    m_fork->setIcon(QIcon(QStringLiteral(":myIcons/createSession.png")));
    m_menu->setIcon(QIcon(QStringLiteral(":myIcons/menu.png")));

    int size = m_urlLine->sizeHint().height();
    QSize tsize(size,size);
    m_back->setIconSize(tsize);
    m_forward->setIconSize(tsize);
    m_refresh->setIconSize(tsize);
    m_stop->setIconSize(tsize);
    m_fork->setIconSize(tsize);
    m_menu->setIconSize(tsize);

    if(m_session){
        m_sLabel->setText(*m_session);
        m_sLabel->show();
        m_fork->hide();
    }else{
        m_sLabel->hide();
        m_fork->show();
    }

    m_back->setEnabled(false);
    m_forward->setEnabled(false);
    m_refresh->setEnabled(false);
    m_stop->setEnabled(false);

    layout->setSpacing(4);
    layout->setMargin(4);

    layout->addWidget(m_back);
    layout->addWidget(m_forward);
    layout->addWidget(m_refresh);
    layout->addWidget(m_stop);
    layout->addWidget(m_urlLine);
    layout->addWidget(m_sLabel);
    layout->addWidget(m_fork);
    layout->addWidget(m_menu);


    //Setup the shortcuts
    m_refresh->setShortcut(QKeySequence::Refresh);
    m_back->setShortcut(QKeySequence::Back);
    m_forward->setShortcut(QKeySequence::Forward);
    m_stop->setShortcut(QKeySequence::Cancel);

    //Connections
    connect(m_urlLine, &QLineEdit::returnPressed, this, [this]() {
        m_urlLine->setSiteIcon(QIcon(QStringLiteral(":defaulticon.png")));
        if (m_urlLine->url().isValid()) {
            m_tabWidget->setUrl(m_urlLine->url());
            m_urlLine->setUrl(m_urlLine->url());
        }
    });
    connect(m_menu, &QToolButton::clicked, [this]() {
        QMenu *menu = createBrowserMenu();
        QPoint point = mapToGlobal(m_menu->pos());
        point.setY(point.y() + m_menu->height());
        point.setX(point.x() - (menu->sizeHint().width() - m_menu->sizeHint().width()));

        menu->exec(point);

    });
    connect(m_fork, &QToolButton::clicked, [this]() {
        QInputDialog dialog(this);
        QString val = dialog.getText(this, tr("Session Name"), tr("Enter a name for your new session:"));
        if(!val.isEmpty()){
            m_session = new QString(val);
            m_fork->hide();
            m_sLabel->setText(val);
            m_sLabel->show();
            saveSession();
        }

    });

    connect(m_refresh, &QToolButton::clicked, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Reload);
    });
    connect(m_stop, &QToolButton::clicked, [this](){
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Stop);
    });
    connect(m_back, &QToolButton::clicked, [this](){
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Back);
    });
    connect(m_forward, &QToolButton::clicked, [this](){
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Forward);
    });

    return layout;
}

QMenu* BrowserWindow::createBrowserMenu(){
    QMenu *menu = new QMenu(this);
    WebView *v = m_tabWidget->currentWebView();
    //QAction *newtab = new QAction(QIcon(tr(":addtab.png")), tr("Add Tab"), this);
    QAction *exit       = new QAction("Exit", this);
    QAction *newtab     = new QAction(tr("New Tab"), this);
    QAction *newwindow  = new QAction(tr("New Window"), this);
    QAction *sethome    = new QAction(tr("Set as Homepage"), this);
    QAction *delhome    = new QAction(tr("Delete Homepage"), this);
    QAction *delsession    = new QAction(tr("Disband Session"), this);
    QAction *blocksite    = new QAction(tr("Block Site"), this);
    QAction *unblocksite    = new QAction(tr("Unblock Site"), this);
    QAction *booksite    = new QAction(tr("Bookmark Site"), this);
    QAction *unbooksite    = new QAction(tr("Unbookmark Site"), this);

    newtab->setData(0);
    newwindow->setData(2);
    sethome->setData(3);
    delhome->setData(4);
    delsession->setData(5);

    blocksite->setData(6);
    booksite->setData(7);

    unblocksite->setData(8);
    unbooksite->setData(9);
    exit->setData(11);

    menu->addAction(newtab);
    menu->addAction(newwindow);
    menu->addSeparator();
    if(v){
        if(!m_json->isBooked(v->page()->url()))
            menu->addAction(booksite);
        else
            menu->addAction(unbooksite);

        if(!m_json->isBlocked(v->page()->url()))
            menu->addAction(blocksite);
        else
            menu->addAction(unblocksite);
        menu->addSeparator();
    }
    QVector<QString*> sessions = m_json->getSessions();
    if(sessions.size() > 0){
        QMenu *sessionMenu = menu->addMenu(tr("Sessions"));
        for(QString *key : sessions){
            if(key->compare(m_session) != 0){
                QAction *a = new QAction(*key, this);
                a->setData(QVariant(1));
                sessionMenu->addAction(a);
            }
        }
    }
    if(v){
        QVector<QString*> bookmarks = m_json->getBookmarks();
        if(bookmarks.size() > 0){
            QMenu *bookmarkMenu = menu->addMenu(tr("Bookmarks"));
            for(QString *key : bookmarks){
                QAction *a = new QAction(*key, this);
                a->setData(10);
                bookmarkMenu->addAction(a);
            }
        }

        menu->addAction(sethome);
    }
    menu->addSeparator();
    if(m_session) menu->addAction(delsession);
    if(m_json->getHomepage()) menu->addAction(delhome);
    menu->addSeparator();
    menu->addAction(exit);

    connect(menu, &QMenu::triggered, this, [this, v](QAction *action){
        switch(action->data().toInt()){
            case 0:
                m_tabWidget->createTab(true, m_json->getHomepage());
                break;
            case 1:
                this->handleNewWindowTriggered(new QString(action->text()));
                break;
            case 2:
                this->handleNewWindowTriggered(nullptr);
                break;
            case 3:
                //Set the current pages url as home
                if(v){
                    m_json->saveHomepage(v->page()->url());
                }

                break;
            case 4:
                m_json->deleteHomepage();
                break;
            case 5:
                m_json->deleteSession(m_session);
                m_session = nullptr;
                m_fork->show();
                m_sLabel->hide();
                break;
            case 6:
                //Block site
                if(v){
                    m_json->saveBlockSite(v->page()->url());
                    v->stop();
                    v->reload();
                }
                break;
            case 7:
                if(v){
                    m_json->saveBookSite(v->page()->url());
                }
                break;
            case 8:
                if(v){
                    m_json->deleteBlockSite(v->page()->url());
                    v->stop();
                    v->reload();
                }
                break;
            case 9:
                if(v){
                    m_json->deleteBookSite(v->page()->url());
                }
                break;
            case 10:
                qDebug() << action->text();
                m_tabWidget->setUrl(QUrl::fromUserInput(action->text()));
                break;
            case 11:
                this->close();
                break;
        }
    });
    return menu;
}



bool BrowserWindow::saveSession(){
    QVector<QUrl> urls;
    for(int i = 0; i < m_tabWidget->count(); i++){
        WebView *v = m_tabWidget->webViewAt(i);
        QUrl url = v->page()->url();
        urls.append(url);
    }
    return m_json->saveSession(m_session, urls);
}

//This is incharge of properly closing all QObjects
//Note: this fixed the QWebEngineView crash
void BrowserWindow::closeEvent(QCloseEvent *event){
   event->accept();
   deleteLater();
}

void BrowserWindow::handleNewWindowTriggered(QString *session)
{
    BrowserWindow *window = new BrowserWindow(nullptr, session);
    Browser::instance().addWindow(window);
}

BrowserWindow::~BrowserWindow()
{

}
