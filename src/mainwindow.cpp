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

    initAccInofView();

    updateAccInfoViewFlag = false;

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateAccInofView()));
    timer->start(500);

    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(showAddAccInfoDialog()));
    connect(ui->editBtn,SIGNAL(clicked()),this,SLOT(showEditAccInfoDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, APP_NAME,
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

void MainWindow::initAccInofView()
{
    QSqlQuery query;
    query.exec("select count(id) from account_info");
    query.next();
    int RowCount = query.value(0).toInt();
    if (RowCount == 0)
    {
        return;
    }

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
    if (RowCount == 0)
    {
        return;
    }

    QString sql = "select id,appname,username,pwd,comment,updatetime from account_info order by appname asc";
    query.exec(sql);

    qDebug() << "RowCount:" << RowCount;


    ui->accountInfoView->clear();
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
    QString infoIdStr = ui->accountInfoView->item(row,0)->text();
    int infoId = infoIdStr.toInt();
    qDebug() << infoId;
    EditAccInfoDialog *dlg = new EditAccInfoDialog(this, &updateAccInfoViewFlag, infoId);
    dlg->show();
}
