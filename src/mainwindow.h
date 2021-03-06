#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QSqlTableModel>

#include "configopt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
    ConfigOpt *configOpt;
    bool updateAccInfoViewFlag;
    bool showFlag;

    void closeEvent(QCloseEvent *event);
    void initLoinLog();
    void initAccInfoView();
    void updateView();
    bool exportAccInfoData(QString filePath);

private slots:
    void updateAccInfoView();
    void updateAccinfoView_pwd();
    void showAddAccInfoDialog();
    void showEditAccInfoDialog();
    void deleteAccInfo();
    void deleteAllAccInfo();
    void exportAccInfo();
    void exit();
    void showChangePwdDialog();
    void showIntroDialog();
};

#endif // MAINWINDOW_H
