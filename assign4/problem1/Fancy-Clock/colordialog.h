#ifndef COLORDIALOG_H
#define COLORDIALOG_H
#include "ui_color.h"

class ColorDialog : public QDialog, public Ui::ColorPick
{
    Q_OBJECT
public:
    ColorDialog(QWidget * parent = 0);
private slots:
    void colorSelect();
    void saveColor();
private:
    QColor color;
};

#endif // COLORDIALOG_H
