#include "changepwddialog.h"
#include "ui_changepwddialog.h"

ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);
}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}
