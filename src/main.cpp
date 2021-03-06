#include "logindialog.h"
#include <QApplication>

#include <QTextCodec>
#include <QDir>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //判断data文件夹是否存在，若不存在则新建
    QDir *dir = new QDir;
    bool exist = dir->exists("data");
    if(!exist)
         dir->mkdir("data");

    QString strLibPath(QDir::toNativeSeparators
                       (QApplication::applicationDirPath())+QDir::separator()+"plugins");

    a.addLibraryPath(strLibPath);

    QTranslator translator;
    translator.load(QString("qt_zh_CN"));
    a.installTranslator(&translator);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QFont font = QFont("宋体", 9);
    a.setFont(font);

    LoginDialog loginDlg;
    loginDlg.show();

    return a.exec();
}
