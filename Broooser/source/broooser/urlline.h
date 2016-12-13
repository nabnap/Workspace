#ifndef URLLINE_H
#define URLLINE_H
#include <QLineEdit>

class UrlLine : public QLineEdit
{
        Q_OBJECT
public:
    UrlLine(QWidget *parent = nullptr);
    void setSiteIcon(const QIcon &icon);
    void setUrl(const QUrl &url);
    QUrl url() const;
private:
    QToolButton *m_favButton;
};

#endif // URLLINE_H
