#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connectDb();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::connectDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setUserName("root");   //�û� mydb �� ���ݿ� mydb �������ȴ�����
    db.setPassword("123");
    db.setDatabaseName("pwdbook.db");

    if (!db.open())
    {
        qDebug()<<"connect failed.";
        return false;
    }
    qDebug()<<"connect success.";
    return true;
}
