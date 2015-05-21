#include "logindialog.h"
#include "ui_logindialog.h"

#include "mainwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(APP_NAME);
    if(!connectDb())
    {
        QString error_msg = "数据库连接失败，请联系软件作者。";
        QMessageBox::warning(this,APP_NAME,error_msg);
    }
    createDbTable();

    connect(ui->loginBtn,SIGNAL(clicked()),this,SLOT(login()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::connectDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pwdbook.db");
    //db.setDatabaseName(":memory:");

    if (!db.open())
    {
        qDebug()<<"connect failed.";
        return false;
    }
    qDebug()<<"connect success.";
    return true;
}

void LoginDialog::createDbTable()
{
    bool ret1 = false,ret2 = false,ret3 =false;

    QSqlQuery query;
    query.exec("create table password (pwd text PRIMARY KEY NOT NULL)");
    query.exec("select count(pwd) from password");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret1 = query.exec("insert into password values('admin')");
    }

    query.exec("create table account_info ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
             "appname text NOT NULL,"
             "username text NOT NULL,"
             "pwd text NOT NULL,"
              "comment text  NOT NULL,"
             "updatetime text NOT NULL)"
               );
    query.exec("select count(id) from account_info");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret2 = query.exec("insert into account_info(appname,username,pwd,comment,updatetime) values('QQ','1106360','123456','小号，用于网站注册等','2015-05-20_09:05:27')");
    }

    query.exec("create table login_log ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
               "time text NOT NULL,"
               "state text NOT NULL)"
               );
    query.exec("select count(id) from login_log");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret3 = query.exec("insert into login_log(time,state) values('2015-05-20_09:05:27','成功')");
    }

    qDebug() << ret1 << ret2 << ret3;

}

void LoginDialog::login()
{
    QSqlQuery query;
    query.exec("select pwd from password limit 1");
    query.next();
    QString pwd = query.value(0).toString();
    if(ui->pwdEdit->text() == pwd)
    {
        MainWindow *mainWin = new MainWindow(this);
        this->hide();
        mainWin->show();
    }
    else
    {
        QString error_msg = "密码错误，请重新输入密码。";
        QMessageBox::warning(this,APP_NAME,error_msg);
    }
}

void LoginDialog::exit()
{
    this->close();
}
