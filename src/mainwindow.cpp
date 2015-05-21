#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APP_NAME);
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
