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

    if(cstr == "Red") color = Qt::red;
    if(cstr == "Green") color = Qt::green;
    if(cstr == "Blue") color = Qt::blue;
    if(cstr == "Black") color = Qt::black;
    if(cstr == "Yellow") color = Qt::yellow;
}

void ColorDialog::saveColor(){
    QSettings settings("Group2Dev","FancyClock");
    settings.beginGroup("ClockColor");
    settings.setValue("lcd/color", color.rgba());
    settings.endGroup();
}
