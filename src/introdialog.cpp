#include "introdialog.h"
#include "ui_introdialog.h"

IntroDialog::IntroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("�������벾");

    ui->label->setText("���벾Ϊ������\n\n������ߣ�Tim Lee\n\n��ϵ��ʽ��872758512@qq.com");
}

IntroDialog::~IntroDialog()
{
    delete ui;
}
