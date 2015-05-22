#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>

#include "defines.h"
#include "addaccinfodialog.h"
#include "editaccinfodialog.h"

#define ACC_INFO_FIELD_COUNT 6

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APP_NAME);

    configOpt = ConfigOpt::GetInstance();

    QString test = "test";
    configOpt->setUpateFlag(test);

    initLoinLog();
    initAccInofView();

    updateAccInfoViewFlag = false;

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateAccInofView()));
    timer->start(500);

    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(showAddAccInfoDialog()));
    connect(ui->editBtn,SIGNAL(clicked()),this,SLOT(showEditAccInfoDialog()));
    connect(ui->deleteBtn,SIGNAL(clicked()),this,SLOT(deleteAccInfo()));
    connect(ui->deleteAllBtn,SIGNAL(clicked()),this,SLOT(deleteAllAccInfo()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::warning(this, APP_NAME,
                                   QString(tr("�Ƿ��˳�����?")),
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No)
    {
        event->ignore();  //�����˳��źţ������������
    }
    else if (button == QMessageBox::Yes)
    {
        event->accept();  //�����˳��źţ������˳�
    }
}

void MainWindow::initLoinLog()
{
    QSqlQuery query;
    QString sql = "select time from login_log where state='�ɹ�' order by time desc limit 1";
    query.exec(sql);
    query.next();
    QString lastLoginSuc_time = query.value(0).toString();
    ui->loginSuc_time->setText(lastLoginSuc_time);

    sql = "select count(id) from login_log where state='�ɹ�'";
    query.exec(sql);
    query.next();
    QString Suc_num = query.value(0).toString();
    ui->loginSuc_num->setText(Suc_num);

    sql = "select time from login_log where state='ʧ��' order by time desc limit 1";
    query.exec(sql);
    query.next();
    QString lastLoginFail_time = query.value(0).toString();
    ui->loginFail_time->setText(lastLoginFail_time);

    sql = "select count(id) from login_log where state='ʧ��'";
    query.exec(sql);
    query.next();
    QString Fail_num = query.value(0).toString();
    ui->loginFail_num->setText(Fail_num);
}

void MainWindow::initAccInofView()
{
    QSqlQuery query;
    query.exec("select count(id) from account_info");
    query.next();
    int RowCount = query.value(0).toInt();

    QString sql = "select id,appname,username,pwd,comment,updatetime from account_info order by appname asc";
    query.exec(sql);

    qDebug() << "RowCount:" << RowCount;

    ui->accountInfoView->setRowCount(RowCount);
    ui->accountInfoView->setColumnCount(ACC_INFO_FIELD_COUNT);
    ui->accountInfoView->hideColumn(0);
    ui->accountInfoView->setFocusPolicy(Qt::NoFocus);
    ui->accountInfoView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->accountInfoView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->accountInfoView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->accountInfoView->selectRow(0);
    ui->accountInfoView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui->accountInfoView->setStyleSheet("selection-background-color: #96CDCD");

    QStringList header;
    header << "ID" << "Ӧ������" << "�û���" << "����" << "��ע" << "����ʱ��";
    ui->accountInfoView->setHorizontalHeaderLabels(header);

    int i = 0;
    while (query.next())
    {
        for(int j=0; j<ACC_INFO_FIELD_COUNT; j++)
            ui->accountInfoView->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        i++;
    }

    ui->accountInfoView->sortByColumn(1,Qt::AscendingOrder);
    ui->accountInfoView->setSortingEnabled(true);

}

void MainWindow::updateView()
{
    QSqlQuery query;
    query.exec("select count(id) from account_info");
    query.next();
    int RowCount = query.value(0).toInt();

    QString sql = "select id,appname,username,pwd,comment,updatetime from account_info order by appname asc";
    query.exec(sql);

    qDebug() << "RowCount:" << RowCount;


    ui->accountInfoView->clearContents();
    ui->accountInfoView->setRowCount(RowCount);
    ui->accountInfoView->setColumnCount(ACC_INFO_FIELD_COUNT);

    int i = 0;
    while (query.next())
    {
        for(int j=0; j<ACC_INFO_FIELD_COUNT; j++)
            ui->accountInfoView->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        i++;
    }
    ui->accountInfoView->hideColumn(0);

}

void MainWindow::updateAccInofView()
{
    if(updateAccInfoViewFlag)
    {
        updateAccInfoViewFlag = false;
        updateView();
        qDebug() << "initAccInofView()";
    }
}

void MainWindow::showAddAccInfoDialog()
{
    AddAccInfoDialog *dlg = new AddAccInfoDialog(this, &updateAccInfoViewFlag);
    dlg->show();
}

void MainWindow::showEditAccInfoDialog()
{
    int row = ui->accountInfoView->currentIndex().row();
    if(row < 0)
    {
        QMessageBox::warning(this,APP_NAME,"��ѡ����Ҫ�޸ĵ��˻���Ϣ");
        return;
    }
    int infoId = ui->accountInfoView->item(row,0)->text().toInt();
    qDebug() << infoId;
    EditAccInfoDialog *dlg = new EditAccInfoDialog(this, &updateAccInfoViewFlag, infoId);
    dlg->show();
}

void MainWindow::deleteAccInfo()
{
    int row = ui->accountInfoView->currentIndex().row();
    if(row < 0)
    {
        QMessageBox::warning(this,APP_NAME,"��ѡ����Ҫ�޸ĵ��˻���Ϣ");
        return;
    }
    int infoId = ui->accountInfoView->item(row,0)->text().toInt();
    qDebug() << infoId;
    int ok = QMessageBox::warning(this,APP_NAME,"�Ƿ�ɾ����ǰѡ�е��˻���Ϣ��",QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        return;
    QSqlQuery query;
    QString sql = QString("delete from account_info where id = %1").arg(infoId);
    query.exec(sql);
    updateAccInfoViewFlag = true;
    QMessageBox::information(this,APP_NAME,"ɾ���ɹ�");
}

void MainWindow::deleteAllAccInfo()
{
    int ok = QMessageBox::warning(this,APP_NAME,"�Ƿ�ɾ�����е��˻���Ϣ��",QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        return;
    QSqlQuery query;
    QString sql = "delete from account_info";
    query.exec(sql);
    updateAccInfoViewFlag = true;
    QMessageBox::information(this,APP_NAME,"ɾ���ɹ�");
}

void MainWindow::exit()
{
    this->close();
}
