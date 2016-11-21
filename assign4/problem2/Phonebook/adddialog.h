#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QDialog>
#include "ui_add_dialog.h"
class AddDialog : public QDialog, public Ui::AddDialog{
    Q_OBJECT
public:
    AddDialog(QWidget *parent = 0);
private slots:
    void validInfo();
};

#endif // ADDDIALOG_H

