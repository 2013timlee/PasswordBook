#ifndef CONFIGOPT_H
#define CONFIGOPT_H

#include <QSettings>

#define CONFIG_FILE "config.ini"

#define UPDATE_FLAG "update/flag"

class ConfigOpt
{    
protected:
    ConfigOpt();

//����ģʽ
public:
    static ConfigOpt* GetInstance();

private:
    QSettings *settings;
    static ConfigOpt *instance;


public:
    void setUpateFlag(QString updateFlag);
    QString getUpateFlag();

};

#endif // CONFIGOPT_H
