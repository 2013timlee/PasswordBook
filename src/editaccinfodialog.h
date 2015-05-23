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
    explicit EditAccInfoDialog(QWidget *parent = 0, bool *updateAccInfoViewFlag = false, QString infoId = "0");
    ~EditAccInfoDialog();

private:
    Ui::EditAccInfoDialog *ui;

    bool *updateAccInfoViewFlag;
    QString infoId;
    void initDialog(QString infoId);

private slots:
    void saveAccInfo();
    void exit();
};

#endif // EDITACCINFODIALOG_H
