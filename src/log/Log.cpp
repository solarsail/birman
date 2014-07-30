#include <ctime>
#include <string>
#include <cstdarg>

#include "Log.h"

using std::fstream;
using std::string;
using std::ios;
using std::streampos;

// ���캯��  filepath��ʾ��־�ļ�����·��
CLog::CLog(const char *filePath, LOG_LEVEL level):m_showLogFlag(true), m_LogLevel(level),
	m_maxLogFileSize(10 * 1024 * 1024), m_logFilePath(filePath)
{
	m_fileOut.open(filePath, ios::out | ios::app);
	m_openSuccess = m_fileOut.is_open();
}

CLog::CLog(const wchar_t *filePath, LOG_LEVEL level):m_showLogFlag(true), m_LogLevel(level),
	m_maxLogFileSize(10 * 1024 * 1024)
{
	m_fileOut.open(filePath, ios::out | ios::app);
	m_openSuccess = m_fileOut.is_open();
	m_logFilePath = W2A(filePath);
}

void CLog::OpenLogFile(const char *pFilePath, LOG_LEVEL level)
{
	if (pFilePath)
	{
		if (m_openSuccess)  // ����Ѿ����ļ� �ر�ԭ�ļ�
		{
			CloseLogFile();
		}
		m_fileOut.open(pFilePath, ios::out | ios::app);
	}
	m_openSuccess = m_fileOut.is_open();
	m_LogLevel = level;
	m_logFilePath = pFilePath;
}

void CLog::OpenLogFile(const wchar_t *pFilePath, LOG_LEVEL level)
{
	if (pFilePath)
	{
		if (m_openSuccess)  // ����Ѿ����ļ� �ر�ԭ�ļ�
		{
			CloseLogFile();
		}
		m_fileOut.open(pFilePath, ios::out | ios::app);
	}
	m_openSuccess = m_fileOut.is_open();
	m_LogLevel = level;
	m_logFilePath = W2A(pFilePath);
}

// <Summary>���ֽ��ַ�ת���ֽ��ַ�</Summary>
// <DateTime>2013/9/9</DateTime>
// <Parameter name="pWcsStr" type="IN">���ֽ��ַ���</Parameter>
// <Returns>���ֽ��ַ���</Returns>
string CLog::W2A(const wchar_t *pWcsStr)
{
    size_t wcsStrLen = wcsnlen(pWcsStr, _TRUNCATE) + 1;   // ���ַ���pWcsStr �ַ����� ����null�ַ�
	char *pDestString = (char *)malloc(wcsStrLen);        // ����ת������ַ����ڴ�ռ�
	if (NULL == pDestString)
	{
		return string("");
	}
	size_t numberOfCharConverted = 0;                      // ʵ��ת�����ַ����� ����null�ַ�
    //wcstombs(pDestString, pWcsStr, _TRUNCATE);   // ���ֽ��ַ�ת���ֽ��ַ�
	 wcstombs_s(&numberOfCharConverted, pDestString, wcsStrLen, pWcsStr, _TRUNCATE);
	string mbsStr(pDestString);
	free(pDestString);
	return mbsStr;
}

// <Summary>�õ���־�ļ���С</Summary>
// <DateTime>2013/9/9</DateTime>
// <Returns>��־�ļ���С</Returns>
size_t CLog::GetLogFileSize()
{
	if (!m_openSuccess)
	{
		return 0;
	}
	streampos curPos = m_fileOut.tellg();  // ��ǰ�ļ�ָ��λ��

	m_fileOut.seekg(0, ios::end);  // ���ļ�ָ��ָ���ļ�ĩβ 
	streampos pos = m_fileOut.tellg(); // ��ȡ�ļ�ָ���λ�� ��ֵ��Ϊ�ļ���С
	m_fileOut.seekg(curPos);   // �ָ��ļ�ָ��λ��
	return static_cast<size_t>(pos);
}

// ��logTextд����־�ļ�
// level: ������־��Ϣ����  logText����־����
void CLog::WriteLog(string logText, LOG_LEVEL level)
{
    if (m_openSuccess && level <= m_LogLevel)
    {
        string flag;
        if (level <= LL_ERROR)
        {
            flag = "[ERROR] ";
        }
        else if (level >= LL_INFORMATION)
        {
            flag = "[INFORMATION] ";
        }
        else 
        {
            flag = "[WARN] ";
        }
        if (m_showLogFlag)
        {
        	logText = flag + logText;
        }
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // ��־��Ϣ���������־��С ���������־
		{
			ClearLogFile();
		}
		// д��־��Ϣ
		m_fileOut.write(logText.c_str(), logText.size()); 
		// ����־�����ʱ����Ϣ
		time_t nowTime = time(NULL);
        struct tm *pLocalTime = localtime(&nowTime);
		char timeString[100] = {0};
		sprintf_s(timeString, " [%04d-%02d-%02d %02d:%02d:%02d]\n", pLocalTime->tm_year + 1900, pLocalTime->tm_mon + 1, 
			pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
		m_fileOut.write(timeString, strnlen(timeString, sizeof(timeString)));
        m_fileOut.flush();
    }
    return;
}

void CLog::WriteLog(LOG_LEVEL level, const char *pLogText, ...)
{
    va_list args;
    char logText[LOG_LINE_MAX] = {0};
    va_start(args, pLogText);
    vsnprintf_s(logText, LOG_LINE_MAX - 1, pLogText, args);
    WriteLog(logText, level);
}

// <Summary>��ʽ���ַ���</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="srcString" type="IN">��Ҫ���и�ʽ�����ַ���</Parameter>
// <Parameter name="pFormatString" type="IN">��ʽ�ַ���</Parameter>
// <Returns>��ʽ������ַ���</Returns>
const string& CLog::StringFormat(std::string &srcString, const char *pFormatString, ...)
{
    va_list args;
    char tempString[2048] = {0};  // ��ʽ���ַ������֧��2048���ֽ�
    va_start(args, pFormatString);
    vsnprintf_s(tempString, sizeof(tempString), pFormatString, args);
    srcString = tempString;
    return srcString;
}

// <Summary>����־�ַ���ת��Ϊ��������־��Ϣ</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="pLogText" type="IN">��־�ַ���</Parameter>
// <Parameter name="level" type="IN">��־����</Parameter>
// <Returns>��������־��Ϣ</Returns>
string CLog::ConvertToRealLogText(const char *pLogText, LOG_LEVEL level)
{
    if (NULL == pLogText)
    {
        return string("");
    }

    // �õ���ǰϵͳʱ��
    time_t nowTime = time(NULL);
    struct tm *pLocalTime = localtime(&nowTime);

    string strLogText(pLogText);
    string::size_type pos = strLogText.find("$(");
    while (pos != string::npos)
    {
        string::size_type tempPos = strLogText.find(")", pos);
        if (tempPos != string::npos)
        {
            string strSubString = strLogText.substr(pos, tempPos - pos + 1);
            if (strSubString == string("$(DATE)"))
            {
                StringFormat(strSubString, "%04d-%02d-%02d", pLocalTime->tm_year + 1900, pLocalTime->tm_mon + 1, pLocalTime->tm_mday);
            }
            else if (strSubString == string("$(TIME)"))
            {
                StringFormat(strSubString, "%02d:%02d:%02d", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
            }
            else if (strSubString == string("$(DATETIME)"))
            {
                StringFormat(strSubString, "%04d-%02d-%02d %02d:%02d:%02d", pLocalTime->tm_year + 1900, 
                    pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, 
                    pLocalTime->tm_sec);
            }
            else if (strSubString == string("$(LEVELFLAG)"))
            {
                if (LL_ERROR == level)
                {
                    strSubString = "ERROR";
                }
                else if (LL_WARN == level)
                {
                    strSubString = "WARN";
                }
                else if (LL_INFORMATION == level)
                {
                    strSubString = "INFORMATION";
                }
            }
            strLogText.replace(pos, tempPos - pos + 1, strSubString);
            pos = strLogText.find("$(", tempPos + 1);
        }
        else 
        {
            break;
        }
    }

    return strLogText;
}

// <Summary>
// �������� ���ڽ���־��Ҫ��ĸ�ʽ���
// ��logText��ʵ�����ݺ͸�ʽ��¼��־��Ϊ�˱�����־��¼������һЩԤ���峣�������ڴ���ĳЩ�������Ϣ
// ���������ø�ʽ������makefile�ļ��еı�������$(��������),��������Ϊ��д��Ŀ���Ѿ����õĳ����У�
//   1.$(DATE):��ʾ��ǰ���� ��ʽΪYYYY-MM-DD
//   2.$(TIME):��ʾ��ǰʱ�� ��ʽΪHH:MM:SS
//   3.$(LEVELFLAG):��ʾ����־�ļ����־
//   4.$(DATETIME):��ʾ��ǰ���ں�ʱ�� ��ʽΪYYYY-MM-DD HH:mm:SS
// ���ӣ�WriteLogEx(LL_ERROR, "[$(DATE) $(TIME)] �߳��˳� �߳�id=%d [$(LEVELFLAG)]", 10);
// Ч����[2013-10-31 09:55:30] �߳��˳� �߳�id=10 [ERROR]
// </Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="logText" type="IN">��־����</Parameter>
// <Parameter name="level" type="IN">��־����</Parameter>
void CLog::WriteLogEx(LOG_LEVEL level, const char *pLogText, ...)
{
    if (m_openSuccess && level <= m_LogLevel)
    {
        va_list args;
        char szLogText[LOG_LINE_MAX] = {0};
        va_start(args, pLogText);
        vsnprintf_s(szLogText, LOG_LINE_MAX - 1, pLogText, args);
        string strRealLogText = ConvertToRealLogText(szLogText, level);
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // ��־��Ϣ���������־��С ���������־
        {
            ClearLogFile();
        }
        m_fileOut.write(strRealLogText.c_str(), strRealLogText.length());
    }
}

void CLog::CloseLogFile()
{
    m_fileOut.clear();  // ������״̬
    m_fileOut.close();  // �ر���
    m_openSuccess = false;
}

// ɾ����־�ļ�����
void CLog::ClearLogFile()
{
    if (!m_openSuccess || m_logFilePath == string(""))  // ��δ�ɹ���
    {
        return;
    }

    CloseLogFile(); // �ر���
    m_fileOut.open(m_logFilePath, ios::out | ios::trunc); // �ԽضϷ�ʽ���ļ�
    m_openSuccess = m_fileOut.is_open();
}