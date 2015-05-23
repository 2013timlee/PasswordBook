#include "changepwddialog.h"
#include "ui_changepwddialog.h"

#include <QSqlQuery>
#include <QMessageBox>

#include "defines.h"

ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("修改密码");
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(saveNewPwd()));
}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}

void ChangePwdDialog::exit()
{
    this->close();
}

void ChangePwdDialog::saveNewPwd()
{
    QSqlQuery query;
    query.exec("select pwd from password limit 1");
    query.next();
    QString oldPwd = query.value(0).toString();
    if(ui->oldPwdEdit->text() != oldPwd)
    {
        QMessageBox::warning(this,APP_NAME,"原密码输入错误，请重新输入");
        return;
    }
    QString newPwd = ui->newPwdEdit->text();
    QString newPwd2 = ui->newPwdEdit2->text();
    if(newPwd != newPwd2)
    {
        QMessageBox::warning(this,APP_NAME,"两次输入的新密码不一致");
        return;
    }
    QString sql = QString("update password set pwd = '%1' where pwd = '%2'").arg(newPwd).arg(oldPwd);
    if(!query.exec(sql))
    {
        QMessageBox::warning(this,APP_NAME,"修改密码失败");
        return;
    }
    QMessageBox::information(this,APP_NAME,"修改密码成功");
}
