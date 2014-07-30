#include "LogManager.h"
#include "Log.h"

using std::map;
using std::string;

map<string, CLog*> LogManager::m_logMap;

// <Summary>����־</Summary>
// <DateTime>2014/4/22</DateTime>
// <Parameter name="pFilePath" type="IN">��־�ļ�·��</Parameter>
// <Parameter name="nLogLevel" type="IN">��־��¼����</Parameter>
// <Returns>�ɹ�������־����ָ�� ���򷵻�NULL</Returns>
CLog* LogManager::OpenLog(const char *pFilePath, int nLogLevel)
{
    if (NULL == pFilePath)
    {
        return NULL;
    }
    CLog *pLog = NULL;

    map<string, CLog*>::iterator iter = m_logMap.find(pFilePath);
    if (m_logMap.find(pFilePath) == m_logMap.end())   // ֮ǰû�д򿪹����ļ� ��ʵ����һ����־����
    {
        pLog = new CLog(pFilePath);
        if (!pLog->GetOpenStatus())  // �򿪸���־�ļ����ɹ�
        {
            return NULL;
        }

        m_logMap[pFilePath] = pLog;
    }
    else
    {
        pLog = iter->second;
    }

    if (pLog)   // ��־�Ѿ����� ��������־����
    {
        pLog->SetLogLevel((CLog::LOG_LEVEL)nLogLevel);
    }
    return pLog;
}

// <Summary>��ղ��ͷ�������־������ռ�õ��ڴ�</Summary>
// <DateTime>2014/4/28</DateTime>
void LogManager::Clear()
{
    map<std::string, CLog*>::const_iterator iter = m_logMap.begin();
    for (; iter != m_logMap.end(); ++iter)
    {
        delete iter->second;   // �ͷ�ָ����ռ�õ��ڴ�ռ�
    }
    m_logMap.clear();
}

// <Summary>ɾ�����ͷ��ض���־����ռ�õ��ڴ�ռ�</Summary>
// <DateTime>2014/4/28</DateTime>
// <Parameter name="strLogFilePath" type="IN">��־�ļ�������·��</Parameter>
// <Returns></Returns>
// <Exception cref=""></Exception>
void LogManager::RemoveLog(const std::string &strLogFilePath)
{
    map<std::string, CLog*>::const_iterator iter = m_logMap.find(strLogFilePath);
    if (iter != m_logMap.end())  // �ҵ�ָ������־����
    {
        delete iter->second;     // �ͷ���ռ�õ��ڴ�ռ�
        m_logMap.erase(iter);    // ��map��ɾ������־����ָ��
    }
}
