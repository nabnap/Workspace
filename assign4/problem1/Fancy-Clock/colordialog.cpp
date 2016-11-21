#include "colordialog.h"
#include <QSettings>

ColorDialog::ColorDialog(QWidget * parent) : QDialog(parent)
{
    setupUi(this);
    color = Qt::red;
    connect(this->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(colorSelect()));
    connect(this, SIGNAL(accepted()), this, SLOT(saveColor()));
}

void ColorDialog::colorSelect(){
    QString cstr = this->comboBox->currentText();

    if(cstr == "red") color = Qt::red;
    if(cstr == "green") color = Qt::green;
    if(cstr == "blue") color = Qt::blue;
    if(cstr == "black") color = Qt::black;
    if(cstr == "yellow") color = Qt::yellow;
}

void ColorDialog::saveColor(){
    QSettings settings("Group2Dev","FancyClock");
    settings.beginGroup("ClockColor");
    settings.setValue("lcd/color", color.rgba());
    settings.endGroup();
}
