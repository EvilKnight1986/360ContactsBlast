#include "C360ContactsBlast.h"
#include <Shlwapi.h>
#include <fstream>
#include <iostream>
using namespace std ;

#pragma comment(lib, "shlwapi.lib")

C360ContactsBlast::C360ContactsBlast(void)
: m_strSrcFileName("")
, m_strDstPath("")
, m_strDictionaryPath("")
,m_hSrcFile(INVALID_HANDLE_VALUE)
,m_hSrcFileMap(NULL)
,m_pSrcBuf(NULL)
, m_nSrcFileSize(0)
{
}

C360ContactsBlast::~C360ContactsBlast(void)
{
        Destroy() ;
}

/*******************************************************************************
*
*  �� �� �� :  SetSrcFileName
*  �������� : ����360 contacts���ݰ���·��
*  �����б� : strSrcFilename          -- 360 Contacts���ݰ�·��
*  ˵    �� :    �������ж�Դ�����Ƿ���� 
*  ���ؽ�� : �ɹ�����true,ʧ�ܷ���false
*
*******************************************************************************/
bool C360ContactsBlast::SetSrcFileName(const string & strSrcFileName)
{
        if (PathFileExists(strSrcFileName.c_str()))
        {
                m_strSrcFileName = strSrcFileName ;
                return true ;
        }
        return false;
}

/*******************************************************************************
*
*  �� �� �� :  GetSrcFileName
*  �������� : ����360 contacts �ļ�·��
*  �����б� : ��
*  ˵    �� :    
*  ���ؽ�� : 360 contacts·��
*
*******************************************************************************/
const string & C360ContactsBlast::GetSrcFileName(void)
{
        return m_strSrcFileName ;
}

/*******************************************************************************
*
*  �� �� �� :  SetDstPath
*  �������� : ���ý��ܳɹ��ļ��洢·��
*  �����б� : strDstPath -- �洢·��
*  ˵    �� :    ���ж�Ŀ¼�Ƿ���ڣ��������Ļ��������Դ���
*  ���ؽ�� : �ɹ�����true,ʧ�ܷ���false
*
*******************************************************************************/
bool C360ContactsBlast::SetDstPath(const string & strDstPath)
{
        // �ж�Ŀ¼�Ƿ����
        if (! PathFileExists(strDstPath.c_str()))
        {
                // ���Ŀ¼������,����
                if ( CreateDirectory(strDstPath.c_str(), NULL))
                {
                        m_strDstPath = strDstPath ;
                        return true ;
                }
                DWORD dwError = GetLastError() ;
                return false ;
        }

        // ���ڣ�ֱ�Ӹ�ֵ
        m_strDstPath = strDstPath ;
        return true ;
}

/*******************************************************************************
*
*  �� �� �� :  GetDstPath
*  �������� : ȡ�ý��ܳɹ��ļ��洢·��
*  �����б� : ��
*  ˵    �� :    
*  ���ؽ�� : ���ؽ��ܳɹ��ļ��洢·��
*
*******************************************************************************/
string & C360ContactsBlast::GetDstPath(void)
{
        //TODO: insert return statement here
        return m_strDstPath ;
}

// �����ֵ�·��
/*******************************************************************************
*
*  �� �� �� :  SetDictionaryPath
*  �������� : �����ֵ�·��
*  �����б� : strDictionaryPath -- �ֵ�·��
*  ˵    �� :    ���ж��ֵ��ļ��Ƿ����
*  ���ؽ�� : �ɹ�����true,ʧ�ܷ���false
*
*******************************************************************************/
bool C360ContactsBlast::SetDictionaryPath(string & strDictionaryPath)
{
        if (PathFileExists(strDictionaryPath.c_str()))
        {
                m_strDictionaryPath = strDictionaryPath ;
                return true ;
        }
        return false;
}

/*******************************************************************************
*
*  �� �� �� :  GetDictionaryPath
*  �������� : ȡ���ֵ��ļ�·��
*  �����б� : ��
*  ˵    �� :    
*  ���ؽ�� : �����ֵ��ļ�·��
*
*******************************************************************************/
string & C360ContactsBlast::GetDictionaryPath(void)
{
        //TODO: insert return statement here
        return m_strDictionaryPath ;
}

/*******************************************************************************
*
*  �� �� �� :  MappingFile
*  �������� : ���ļ�ӳ�䵽�ڴ�
*  �����б� : ��
*  ˵    �� :    ��360 contacts�ļ�ӳ�䵽�ڴ���ȥ�����Ч��
*  ���ؽ�� : �����ֵ��ļ�·��
*
*******************************************************************************/
bool C360ContactsBlast::MappingFile(void)
{
        bool bResult(false) ;

        __try
        {
                m_hSrcFile = CreateFile(m_strSrcFileName.c_str(),
                                                        GENERIC_READ,
                                                        FILE_SHARE_READ,
                                                        NULL,
                                                        OPEN_EXISTING,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL) ;

                if (INVALID_HANDLE_VALUE == m_hSrcFile)
                {
                        fprintf(stderr, "CreateFile failed\r\n") ;
                        __leave ;
                }

                m_hSrcFileMap = CreateFileMapping(m_hSrcFile,
                                                                                NULL,
                                                                                PAGE_READONLY,
                                                                                0,
                                                                                0,
                                                                                NULL) ;
                if (NULL == m_hSrcFileMap)
                {
                        fprintf(stderr, "CreateFileMapping failed\r\n") ;
                        __leave ;
                }

                m_nSrcFileSize = GetFileSize(m_hSrcFile, 0) ;

                m_pSrcBuf = MapViewOfFile(m_hSrcFileMap,
                                                                   FILE_MAP_READ,
                                                                   0,
                                                                   0,
                                                                   0) ;

                if (NULL == m_pSrcBuf)
                {
                        fprintf(stderr, "MapViewOfFile failed\r\n") ;
                        __leave ;
                }

                bResult = true ;

        }

        __finally
        {
                if(! bResult)
                {
                        Destroy() ;
                }
        }
        return bResult;
}

/*******************************************************************************
*
*  �� �� �� :  Destroy
*  �������� : �ͷ���Դ
*  �����б� : ��
*  ˵    �� :    
*  ���ؽ�� : ��
*
*******************************************************************************/
void C360ContactsBlast::Destroy(void)
{
        if (NULL != m_pSrcBuf)
        {
                UnmapViewOfFile(m_pSrcBuf) ;
                m_pSrcBuf = NULL ;
        }

        if (NULL != m_hSrcFileMap)
        {
                CloseHandle(m_hSrcFileMap) ;
                m_hSrcFileMap = NULL ;
        }

        if (INVALID_HANDLE_VALUE != m_hSrcFile)
        {
                CloseHandle( m_hSrcFile) ;
                m_hSrcFile = INVALID_HANDLE_VALUE ;
        }
}

// ��ʼ����
/*******************************************************************************
*
*  �� �� �� :  Blast
*  �������� : ��ʼ����
*  �����б� : ��
*  ˵    �� :    
*  ���ؽ�� : 
*
*******************************************************************************/
bool C360ContactsBlast::Blast(void)
{
        ifstream inFile(m_strDictionaryPath.c_str()) ;
        char szPass[MAX_PATH] = {0} ;
        char *pBuf = NULL ;
        char *pGzipBuf = NULL ;
        int nGzipBufSize = m_nSrcFileSize << 2 ;

        if (! inFile)
        {
                fprintf(stderr, "ifstream open file failed!\r\n") ;
                return false ;
        }

        pBuf = new char [m_nSrcFileSize] ;
        pGzipBuf = new char [nGzipBufSize] ;
        
        if (NULL == pBuf)
        {
                return false ;
        }


        // ������Զϵ�


        // ��ʼ��
        while (! inFile.eof())
        {
                inFile.getline(szPass, 8) ;

                // �Ƚ�������
                myDes.InitializeKey(szPass,0 );
                int nSrcFileOffset(0) ;
                while(nSrcFileOffset < m_nSrcFileSize)
                {
                        myDes.DecryptData((char *)m_pSrcBuf + nSrcFileOffset,0);
                        memcpy(pBuf + nSrcFileOffset, myDes.GetPlaintext(), 8) ;
                        nSrcFileOffset += 8 ;
                }

                // �ɹ��ˣ���gzip��ѹ
                
        }


        return false;
}
