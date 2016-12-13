#include "urlline.h"
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QStyle>
#include <QUrl>
UrlLine::UrlLine(QWidget *parent) : QLineEdit(parent)
{
    m_favButton = new QToolButton(this);
    m_favButton->setIcon(QIcon(QStringLiteral(":defaulticon.png")));

    m_favButton->setStyleSheet(QString("QToolButton{ border:none; padding:2px;}"));
    setStyleSheet(QStringLiteral("QLineEdit { padding-left:%1px;}").arg(m_favButton->sizeHint().width()));
    setMinimumSize(minimumSizeHint().width() + m_favButton->sizeHint().width(), qMax(minimumSizeHint().height(), m_favButton->sizeHint().height()));
}

QUrl UrlLine::url() const{
    return QUrl::fromUserInput(text());
}
void UrlLine::setUrl(const QUrl &url){
    setText(url.toString());
    setCursorPosition(0);
}

void UrlLine::setSiteIcon(const QIcon &icon){
    QPixmap pixmap = icon.pixmap(16,16);
    m_favButton->setIcon(pixmap);
}
