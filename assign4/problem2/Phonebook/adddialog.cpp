#include "adddialog.h"
#include <QPushButton>
AddDialog::AddDialog(QWidget * parent) : QDialog(parent){
    setupUi(this);

    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(validInfo()));
    connect(lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(validInfo()));

    validInfo();
}

void AddDialog::validInfo(){
    //addd->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    if(lineEdit->text().size() > 0 && lineEdit_2->text().size() > 0){
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }else{
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

