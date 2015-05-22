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

    bool updateAccInfoViewFlag;

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
    ConfigOpt *configOpt;

    void closeEvent(QCloseEvent *event);
    void initAccInofView();
    void updateView();

private slots:
    void updateAccInofView();
    void showAddAccInfoDialog();
    void showEditAccInfoDialog();
};

#endif // MAINWINDOW_H
