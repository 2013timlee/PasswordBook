#include "logindialog.h"
#include <QApplication>

#include <QTextCodec>
#include <QDir>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strLibPath(QDir::toNativeSeparators
                       (QApplication::applicationDirPath())+QDir::separator()+"plugins");

    a.addLibraryPath(strLibPath);

    QTranslator translator;
    translator.load(QString("qt_zh_CN"));
    a.installTranslator(&translator);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QFont font = QFont("ËÎÌו", 9);
    a.setFont(font);

    LoginDialog loginDlg;
    loginDlg.show();

    return a.exec();
}
