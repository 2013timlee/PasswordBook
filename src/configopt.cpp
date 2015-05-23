#include "configopt.h"

ConfigOpt* ConfigOpt::instance = 0;//静态成员变量初始化

ConfigOpt::ConfigOpt()
{
    settings = new QSettings(CONFIG_FILE, QSettings::IniFormat);
}

ConfigOpt* ConfigOpt::GetInstance()
{
    if(instance == 0)
    {
        instance = new ConfigOpt();
    }
    return instance;
}

void ConfigOpt::setShowFlag(QString updateFlag)
{
    settings->setValue(SHOW_FLAG,updateFlag);
}

//================================================================//
//功能：获取"记住登录信息"配置
//================================================================//
QString ConfigOpt::getShowFlag()
{
    return settings->value(SHOW_FLAG).toString();
}
