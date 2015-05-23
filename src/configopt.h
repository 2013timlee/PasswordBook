#ifndef CONFIGOPT_H
#define CONFIGOPT_H

#include <QSettings>

#define CONFIG_FILE "config.ini"

#define SHOW_FLAG "show/flag"

class ConfigOpt
{    
protected:
    ConfigOpt();

//µ¥ÀýÄ£Ê½
public:
    static ConfigOpt* GetInstance();

private:
    QSettings *settings;
    static ConfigOpt *instance;


public:
    void setShowFlag(QString showFlag);
    QString getShowFlag();

};

#endif // CONFIGOPT_H
