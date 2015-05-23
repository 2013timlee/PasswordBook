#include "introdialog.h"
#include "ui_introdialog.h"

IntroDialog::IntroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroDialog)
{
    ui->setupUi(this);
}

IntroDialog::~IntroDialog()
{
    delete ui;
}
