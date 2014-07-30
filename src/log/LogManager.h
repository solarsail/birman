/************************************************************************/
/* �����ƣ�  LogManager
/* �����ռ䣺��
/* �ļ�����  LogManager.h LogManager.cpp
/* ����ʱ��: 2014-4-22
/* ���ߣ�    
/* ��˵����  ��־��������࣬ͨ���������ʵ������־����ȷ���������������־�������һ����־�ļ�
/************************************************************************/

#ifndef _LOGMANAGER_INCLUDE_H_
#define _LOGMANAGER_INCLUDE_H_

#include <map>
#include <string>

class CLog;

class LogManager
{
public:
    static CLog* OpenLog(const char *pFilePath, int nLogLevel = 1); // ����־
    static void Clear();                                            // ��ղ��ͷ�������־������ռ�õ��ڴ�
    static void RemoveLog(const std::string &strLogFilePath);       // ɾ�����ͷ��ض���־����ռ�õ��ڴ�ռ�

private:  // ˽��Ĭ�Ϲ��캯�������ƹ��캯��
    LogManager(void);
    LogManager(const LogManager &logManager);

private:  // ˽�г�Ա
    static std::map<std::string, CLog*> m_logMap;  // ������־�ļ�·������־������ֵ伯��

};

#endif
