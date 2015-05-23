#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "defines.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

    bool connectDb();
    void createDbTable();

private slots:
    void login();
    void exit();
};

#endif // LOGINDIALOG_H
