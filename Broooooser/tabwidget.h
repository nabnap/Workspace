#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class TabWidget : public QTabWidget
{
     Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);
    void AddTab();
};

#endif // TABWIDGET_H
