#include "configopt.h"

ConfigOpt* ConfigOpt::instance = 0;//��̬��Ա������ʼ��

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

void ConfigOpt::setUpateFlag(QString updateFlag)
{
    settings->setValue(UPDATE_FLAG,updateFlag);
}

//================================================================//
//���ܣ���ȡ"��ס��¼��Ϣ"����
//================================================================//
QString ConfigOpt::getUpateFlag()
{
    return settings->value(UPDATE_FLAG).toString();
}
