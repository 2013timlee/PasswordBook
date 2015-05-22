#ifndef ADDACCINFODIALOG_H
#define ADDACCINFODIALOG_H

#include <QDialog>


namespace Ui {
class AddAccInfoDialog;
}

class AddAccInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAccInfoDialog(QWidget *parent = 0, bool *updateAccInfoViewFlag = false);
    ~AddAccInfoDialog();

private:
    Ui::AddAccInfoDialog *ui;

    bool *updateAccInfoViewFlag;

private slots:
    void saveAccInfo();
    void exit();
};

#endif // ADDACCINFODIALOG_H
