#ifndef EDITACCINFODIALOG_H
#define EDITACCINFODIALOG_H

#include <QDialog>

namespace Ui {
class EditAccInfoDialog;
}

class EditAccInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccInfoDialog(QWidget *parent = 0, bool *updateAccInfoViewFlag = false, int infoId = 0);
    ~EditAccInfoDialog();

private:
    Ui::EditAccInfoDialog *ui;

    bool *updateAccInfoViewFlag;
    int infoId;

    void initDialog();

private slots:
    void saveAccInfo();
    void exit();
};

#endif // EDITACCINFODIALOG_H
