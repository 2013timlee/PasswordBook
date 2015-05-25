#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>

#include "defines.h"
#include "addaccinfodialog.h"
#include "editaccinfodialog.h"
#include "changepwddialog.h"
#include "introdialog.h"

#define ACC_INFO_FIELD_COUNT 6

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APP_NAME);

    configOpt = ConfigOpt::GetInstance();

    showFlag = false;
    ui->showClearText->setChecked(false);
    QString showFlagStr = configOpt->getShowFlag();
    if(!showFlagStr.isEmpty())
    {
        showFlag = (bool)showFlagStr.toInt();
        if(showFlag)
            ui->showClearText->setChecked(true);
    }

    initLoinLog();
    initAccInfoView();

    updateAccInfoViewFlag = false;

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateAccInfoView()));
    timer->start(500);

    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(showAddAccInfoDialog()));
    connect(ui->editBtn,SIGNAL(clicked()),this,SLOT(showEditAccInfoDialog()));
    connect(ui->deleteBtn,SIGNAL(clicked()),this,SLOT(deleteAccInfo()));
    connect(ui->deleteAllBtn,SIGNAL(clicked()),this,SLOT(deleteAllAccInfo()));
    connect(ui->exportBtn,SIGNAL(clicked()),this,SLOT(exportAccInfo()));
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(exit()));
    connect(ui->showClearText,SIGNAL(stateChanged(int)),this,SLOT(updateAccinfoView_pwd()));
    connect(ui->changePwdAction,SIGNAL(triggered()),this,SLOT(showChangePwdDialog()));
    connect(ui->showIntroAction,SIGNAL(triggered()),this,SLOT(showIntroDialog()));
    connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(exit()));
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
    QString sql = "select count(id) from login_log where state='�ɹ�'";
    query.exec(sql);
    query.next();
    QString Suc_num = query.value(0).toString();
    ui->loginSuc_num->setText(Suc_num);

    if(Suc_num.toInt() != 0)
    {
        sql = "select time from login_log where state='�ɹ�' order by time desc limit 1";
        query.exec(sql);
        query.next();
        QString lastLoginSuc_time = query.value(0).toString();
        ui->loginSuc_time->setText(lastLoginSuc_time);
    }

    sql = "select count(id) from login_log where state='ʧ��'";
    query.exec(sql);
    query.next();
    QString Fail_num = query.value(0).toString();
    ui->loginFail_num->setText(Fail_num);

    if(Fail_num.toInt())
    {
        sql = "select time from login_log where state='ʧ��' order by time desc limit 1";
        query.exec(sql);
        query.next();
        QString lastLoginFail_time = query.value(0).toString();
        ui->loginFail_time->setText(lastLoginFail_time);
    }
}

void MainWindow::initAccInfoView()
{
    QSqlQuery query;
    query.exec("select count(id) from account_info");
    query.next();
    int RowCount = query.value(0).toInt();

    QString sql = "select id,appname,username,pwd,comment,updatetime from account_info order by appname asc";
    query.exec(sql);

    qDebug() << "RowCount:" << RowCount;

    ui->accountInfoView->setSortingEnabled(false);
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
        {
            if(!ui->showClearText->isChecked() && j == 3)
            {
                ui->accountInfoView->setItem(i, j, new QTableWidgetItem("******"));
            }
            else
            {
                ui->accountInfoView->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
        }
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

    ui->accountInfoView->setSortingEnabled(false);
    ui->accountInfoView->clearContents();
    ui->accountInfoView->setRowCount(RowCount);
    ui->accountInfoView->setColumnCount(ACC_INFO_FIELD_COUNT);

    int i = 0;
    while (query.next())
    {
        for(int j=0; j<ACC_INFO_FIELD_COUNT; j++)
        {
            if(!ui->showClearText->isChecked() && j == 3)
            {
                ui->accountInfoView->setItem(i, j, new QTableWidgetItem("******"));
            }
            else
            {
                ui->accountInfoView->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
        }
        i++;
    }
    ui->accountInfoView->hideColumn(0);
    ui->accountInfoView->sortByColumn(1,Qt::AscendingOrder);
    ui->accountInfoView->setSortingEnabled(true);
}

void MainWindow::updateAccInfoView()
{
    if(updateAccInfoViewFlag)
    {
        updateAccInfoViewFlag = false;
        updateView();
        qDebug() << "initAccInofView()";
    }
}

void MainWindow::updateAccinfoView_pwd()
{
    if(ui->showClearText->isChecked())
        configOpt->setShowFlag("1");
    else
        configOpt->setShowFlag("0");
    updateAccInfoViewFlag = true;
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
    QString infoId = ui->accountInfoView->item(row,0)->text();
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

/*
void LockDormantUserDialog::exportLockedUser()
{
    QString dir = QFileDialog::getSaveFileName(this,
                                                tr("����ǩ����¼"),
                                                "",
                                                tr("*.csv")) ;

    if (!dir.isEmpty())
    {
        QString path = dir;
        if(exportLockedUserData(path))
        {
            QMessageBox::information(0,tr("�����ɹ�"),tr("�����ɹ���\n�����ļ�����Ϊ:\n") + path);
        }
        else
        {
            QMessageBox::information(0,tr("����ʧ��"),tr("����ʧ�ܣ�"));
        }
    }
    else return;
}

bool LockDormantUserDialog::exportLockedUserData(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream in(&file);

      //�������������û���Ϣ
    in<<tr("����")<<","<<tr("����")<<","<<tr("����")<<","<<tr("����")<<","<<tr("ְλ")<<","<<tr("��ƺ�")<<","<<tr("������")<<","<<tr("�ֻ�����")<<","<<tr("WiFi�绰����")<<endl;
    QSqlQuery query;
    QString sql = QString("select user_id,card_id,name,department,position,lamp_id,car_id,cellphone,wifiphone from user_locked order by user_id asc");
    query.exec(sql);
    qDebug()<<sql<<query.lastError().text()<<query.size();
    while(query.next())
    {
        in <<  query.value(0).toString()<< ","
           <<  query.value(1).toString()<< ","
           <<  query.value(2).toString()<< ","
           <<  query.value(3).toString()<< ","
           <<  query.value(4).toString()<< ","
           <<  query.value(5).toString()<< ","
           <<  query.value(6).toString()<< ","
           <<  query.value(7).toString()<< ","
           <<  query.value(8).toString()<< ","
           <<  "\r\n";
    }

    file.close();
    return true;
}
 */

void MainWindow::exportAccInfo()
{
    QString dir = QFileDialog::getSaveFileName(this,
                                                tr("����ǩ����¼"),
                                                "���벾�˻���Ϣ",
                                                tr("*.csv")) ;

    if (!dir.isEmpty())
    {
        QString path = dir;
        if(exportAccInfoData(path))
        {
            QMessageBox::information(this,APP_NAME,tr("�����ɹ���\n�����ļ�����Ϊ:\n") + path);
        }
        else
        {
            QMessageBox::information(this,APP_NAME,tr("����ʧ�ܣ�"));
        }
    }
    else return;
}

bool MainWindow::exportAccInfoData(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream in(&file);

      //�����˻���Ϣ
    in<<tr("Ӧ������")<<","<<tr("�û���")<<","<<tr("����")<<","<<tr("��ע")<<endl;
    QSqlQuery query;
    QString sql = QString("select appname,username,pwd,comment from account_info order by appname asc");
    query.exec(sql);
    //qDebug()<<sql<<query.lastError().text()<<query.size();
    while(query.next())
    {
        in <<  query.value(0).toString()<< ","
           <<  query.value(1).toString()<< ","
           <<  query.value(2).toString()<< ","
           <<  query.value(3).toString()<< ","
           <<  "\r\n";
    }
    file.close();
    return true;
}

void MainWindow::exit()
{
    this->close();
}

void MainWindow::showChangePwdDialog()
{
    ChangePwdDialog *dlg = new ChangePwdDialog(this);
    dlg->show();
}

void MainWindow::showIntroDialog()
{
    IntroDialog *dlg = new IntroDialog(this);
    dlg->show();
}
