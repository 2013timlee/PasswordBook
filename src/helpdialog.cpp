#include "helpdialog.h"
#include "ui_helpdialog.h"

#include "defines.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(APP_LOGIN_NAME);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
