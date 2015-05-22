#include "addaccinfodialog.h"
#include "ui_addaccinfodialog.h"

#include <QDebug>
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>

#include "defines.h"

AddAccInfoDialog::AddAccInfoDialog(QWidget *parent, bool *updateAccInfoViewFlag) :
    QDialog(parent),
    ui(new Ui::AddAccInfoDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("添加账户信息");
    this->updateAccInfoViewFlag = updateAccInfoViewFlag;

    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(saveAccInfo()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));

}

AddAccInfoDialog::~AddAccInfoDialog()
{
    delete ui;
}

void AddAccInfoDialog::saveAccInfo()
{
    QString appname = ui->appnameEdit->text();
    QString username = ui->usernameEdit->text();
    QString pwd = ui->pwdEdit->text();
    QString comment = ui->commentEdit->text();
    QString updatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query;
    QString sql = QString("insert into account_info(appname,username,pwd,comment,updatetime) values ('%1','%2','%3','%4','%5')")
            .arg(appname).arg(username).arg(pwd).arg(comment).arg(updatetime);
    qDebug()<<sql;
    if(!query.exec(sql))
    {
        QMessageBox::warning(this,APP_NAME,"添加账户信息失败");
        return;
    }
    *updateAccInfoViewFlag = true;
    QMessageBox::information(this,APP_NAME,"添加账户信息成功");
}

void AddAccInfoDialog::exit()
{
    this->close();
}
