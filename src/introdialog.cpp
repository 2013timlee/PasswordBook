#include "introdialog.h"
#include "ui_introdialog.h"

IntroDialog::IntroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("关于密码簿");

    ui->label->setText("密码簿为免费软件\n\n软件作者：Tim Lee\n\n联系方式：872758512@qq.com");
}

IntroDialog::~IntroDialog()
{
    delete ui;
}
