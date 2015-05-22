#include "editaccinfodialog.h"
#include "ui_editaccinfodialog.h"

#include <QDebug>
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>

#include "defines.h"

EditAccInfoDialog::EditAccInfoDialog(QWidget *parent , bool *updateAccInfoViewFlag, int infoId) :
    QDialog(parent),
    ui(new Ui::EditAccInfoDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("修改账户信息");
    this->updateAccInfoViewFlag = updateAccInfoViewFlag;
    this->infoId = infoId;

    initDialog();

    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(saveAccInfo()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));
}

EditAccInfoDialog::~EditAccInfoDialog()
{
    delete ui;
}

void EditAccInfoDialog::initDialog()
{
    QSqlQuery query;
    QString sql = "select appname,username,pwd,comment from account_info";
    query.exec(sql);
    query.next();
    QString appname = query.value(0).toString();
    QString username = query.value(1).toString();
    QString pwd = query.value(2).toString();
    QString comment = query.value(3).toString();
    ui->appnameEdit->setText(appname);
    ui->usernameEdit->setText(username);
    ui->pwdEdit->setText(pwd);
    ui->commentEdit->setText(comment);
}

void EditAccInfoDialog::saveAccInfo()
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
        QMessageBox::warning(this,APP_NAME,"修改账户信息失败");
        return;
    }
    *updateAccInfoViewFlag = true;
    QMessageBox::warning(this,APP_NAME,"修改账户信息成功");
}

void EditAccInfoDialog::exit()
{
    this->close();
}
