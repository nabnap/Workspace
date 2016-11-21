/********************************************************************************
** Form generated from reading UI file 'color.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOR_H
#define UI_COLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ColorPick
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ColorPick)
    {
        if (ColorPick->objectName().isEmpty())
            ColorPick->setObjectName(QStringLiteral("ColorPick"));
        ColorPick->resize(400, 114);
        verticalLayout = new QVBoxLayout(ColorPick);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(ColorPick);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        buttonBox = new QDialogButtonBox(ColorPick);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ColorPick);
        QObject::connect(buttonBox, SIGNAL(accepted()), ColorPick, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ColorPick, SLOT(reject()));

        QMetaObject::connectSlotsByName(ColorPick);
    } // setupUi

    void retranslateUi(QDialog *ColorPick)
    {
        ColorPick->setWindowTitle(QApplication::translate("ColorPick", "Preference", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ColorPick", "red", 0)
         << QApplication::translate("ColorPick", "green", 0)
         << QApplication::translate("ColorPick", "blue", 0)
         << QApplication::translate("ColorPick", "black", 0)
         << QApplication::translate("ColorPick", "yellow", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class ColorPick: public Ui_ColorPick {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOR_H
