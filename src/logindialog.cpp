#include "logindialog.h"
#include "ui_logindialog.h"

#include "mainwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(APP_LOGIN_NAME);

    if(!connectFakeDb2())
    {
        QString error_msg = "数据库连接失败。\n请联系软件作者 Tim ：872758512@qq.com";
        QMessageBox::warning(this,APP_NAME,error_msg);
    }
    if(!connectFakeDb())
    {
        QString error_msg = "数据库连接失败。\n请联系软件作者 Tim ：872758512@qq.com";
        QMessageBox::warning(this,APP_NAME,error_msg);
    }
    if(!connectDb())
    {
        QString error_msg = "数据库连接失败。\n请联系软件作者 Tim ：872758512@qq.com";
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
    db.setDatabaseName(DB_NAME);
    //db.setDatabaseName(":memory:");

    if (!db.open())
    {
        qDebug()<<"connect failed.";
        return false;
    }
    qDebug()<<"connect success.";
    return true;
}

bool LoginDialog::connectFakeDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connect_fake");
    db.setDatabaseName("./data/pwdbook.dat");
    //db.setDatabaseName(":memory:");
    if (!db.open())
    {
        qDebug()<<"connect failed.";
        return false;
    }

    QSqlQuery query(db);
    query.exec("create table password (pwd text PRIMARY KEY NOT NULL)");

    query.exec("select count(pwd) from password");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        query.exec("insert into password values('admin')");
    }

    query.exec("create table account_info ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
             "appname text NOT NULL,"
             "username text NOT NULL,"
             "pwd text NOT NULL,"
              "comment text  NOT NULL,"
             "updatetime text NOT NULL)"
               );
    /*
    query.exec("select count(id) from account_info");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret2 = query.exec("insert into account_info(appname,username,pwd,comment,updatetime) values('QQ','1106360','123456','小号，用于网站注册等','2015-05-20_09:05:27')");
    }
    */

    query.exec("create table login_log ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
               "time text NOT NULL,"
               "state text NOT NULL)"
               );
    /*
    query.exec("select count(id) from login_log");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret3 = query.exec("insert into login_log(time,state) values('2015-05-20_09:05:27','成功')");
    }

    qDebug() << ret1 << ret2 << ret3;
    */

    qDebug()<<"connect success.";
    db.close();
    return true;
}

bool LoginDialog::connectFakeDb2()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connect_fake2");
    db.setDatabaseName("./data/decrypt.exe");
    //db.setDatabaseName(":memory:");
    if (!db.open())
    {
        qDebug()<<"connect failed.";
        return false;
    }

    QSqlQuery query(db);
    query.exec("create table password (pwd text PRIMARY KEY NOT NULL)");

    query.exec("select count(pwd) from password");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        query.exec("insert into password values('admin')");
    }

    query.exec("create table account_info ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
             "appname text NOT NULL,"
             "username text NOT NULL,"
             "pwd text NOT NULL,"
              "comment text  NOT NULL,"
             "updatetime text NOT NULL)"
               );
    /*
    query.exec("select count(id) from account_info");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret2 = query.exec("insert into account_info(appname,username,pwd,comment,updatetime) values('QQ','1106360','123456','小号，用于网站注册等','2015-05-20_09:05:27')");
    }
    */

    query.exec("create table login_log ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
               "time text NOT NULL,"
               "state text NOT NULL)"
               );
    /*
    query.exec("select count(id) from login_log");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret3 = query.exec("insert into login_log(time,state) values('2015-05-20_09:05:27','成功')");
    }

    qDebug() << ret1 << ret2 << ret3;
    */

    qDebug()<<"connect success.";
    db.close();
    return true;
}

void LoginDialog::createDbTable()
{
    //bool ret1 = false,ret2 = false,ret3 =false;

    QSqlQuery query;
    query.exec("create table password (pwd text PRIMARY KEY NOT NULL)");

    query.exec("select count(pwd) from password");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        query.exec("insert into password values('admin')");

        ui->pwdEdit->setEchoMode(QLineEdit::Normal);
        QPalette palette=ui->pwdEdit->palette();
        //设置行编辑器不可用时的背景颜色为蓝色
        palette.setColor(QPalette::Text,Qt::gray);
        ui->pwdEdit->setPalette(palette);
        ui->pwdEdit->setText("初始密码为admin");
    }

    query.exec("create table account_info ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
             "appname text NOT NULL,"
             "username text NOT NULL,"
             "pwd text NOT NULL,"
              "comment text  NOT NULL,"
             "updatetime text NOT NULL)"
               );
    /*
    query.exec("select count(id) from account_info");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret2 = query.exec("insert into account_info(appname,username,pwd,comment,updatetime) values('QQ','1106360','123456','小号，用于网站注册等','2015-05-20_09:05:27')");
    }
    */

    query.exec("create table login_log ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
               "time text NOT NULL,"
               "state text NOT NULL)"
               );
    /*
    query.exec("select count(id) from login_log");
    query.next();
    qDebug() << query.value(0).toUInt();
    if(query.value(0).toUInt() == 0)
    {
        ret3 = query.exec("insert into login_log(time,state) values('2015-05-20_09:05:27','成功')");
    }

    qDebug() << ret1 << ret2 << ret3;
    */

}

void LoginDialog::mousePressEvent(QMouseEvent *)
{
    QPalette palette= ui->pwdEdit->palette();
    palette.setColor(QPalette::Text,Qt::black);
    ui->pwdEdit->setPalette(palette);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->pwdEdit->setText("");
}

void LoginDialog::login()
{
    QString time = QDateTime::currentDateTime().toString("yyyy:MM:dd hh:mm:ss");
    QString sql;
    QSqlQuery query;
    query.exec("select pwd from password limit 1");
    query.next();
    QString pwd = query.value(0).toString();
    if(ui->pwdEdit->text() == pwd)
    {
        MainWindow *mainWin = new MainWindow(0);
        mainWin->show();
        sql = QString("insert into login_log(time,state) values('%1','成功')").arg(time);
        query.exec(sql);
        this->close();
    }
    else
    {
        sql = QString("insert into login_log(time,state) values('%1','失败')").arg(time);
        query.exec(sql);
        QString error_msg = "密码错误，请重新输入密码\n初始密码为admin\n如果忘记密码，请联系软件作者 Tim ：872758512@qq.com";
        QMessageBox::warning(this,APP_NAME,error_msg);
    }
}

void LoginDialog::exit()
{
    this->close();
}
