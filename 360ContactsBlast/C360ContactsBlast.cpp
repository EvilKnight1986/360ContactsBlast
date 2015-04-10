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
*  函 数 名 :  SetSrcFileName
*  功能描述 : 设置360 contacts数据包的路径
*  参数列表 : strSrcFilename          -- 360 Contacts数据包路径
*  说    明 :    函数会判断源数据是否存在 
*  返回结果 : 成功返回true,失败返回false
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
*  函 数 名 :  GetSrcFileName
*  功能描述 : 返回360 contacts 文件路径
*  参数列表 : 无
*  说    明 :    
*  返回结果 : 360 contacts路径
*
*******************************************************************************/
const string & C360ContactsBlast::GetSrcFileName(void)
{
        return m_strSrcFileName ;
}

/*******************************************************************************
*
*  函 数 名 :  SetDstPath
*  功能描述 : 设置解密成功文件存储路径
*  参数列表 : strDstPath -- 存储路径
*  说    明 :    会判断目录是否存在，如果不存的话，将尝试创建
*  返回结果 : 成功返回true,失败返回false
*
*******************************************************************************/
bool C360ContactsBlast::SetDstPath(const string & strDstPath)
{
        // 判断目录是否存在
        if (! PathFileExists(strDstPath.c_str()))
        {
                // 如果目录不存在,创建
                if ( CreateDirectory(strDstPath.c_str(), NULL))
                {
                        m_strDstPath = strDstPath ;
                        return true ;
                }
                DWORD dwError = GetLastError() ;
                return false ;
        }

        // 存在，直接赋值
        m_strDstPath = strDstPath ;
        return true ;
}

/*******************************************************************************
*
*  函 数 名 :  GetDstPath
*  功能描述 : 取得解密成功文件存储路径
*  参数列表 : 无
*  说    明 :    
*  返回结果 : 返回解密成功文件存储路径
*
*******************************************************************************/
string & C360ContactsBlast::GetDstPath(void)
{
        //TODO: insert return statement here
        return m_strDstPath ;
}

// 设置字典路径
/*******************************************************************************
*
*  函 数 名 :  SetDictionaryPath
*  功能描述 : 设置字典路径
*  参数列表 : strDictionaryPath -- 字典路径
*  说    明 :    会判断字典文件是否存在
*  返回结果 : 成功返回true,失败返回false
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
*  函 数 名 :  GetDictionaryPath
*  功能描述 : 取得字典文件路径
*  参数列表 : 无
*  说    明 :    
*  返回结果 : 返回字典文件路径
*
*******************************************************************************/
string & C360ContactsBlast::GetDictionaryPath(void)
{
        //TODO: insert return statement here
        return m_strDictionaryPath ;
}

/*******************************************************************************
*
*  函 数 名 :  MappingFile
*  功能描述 : 将文件映射到内存
*  参数列表 : 无
*  说    明 :    将360 contacts文件映射到内存中去，提高效率
*  返回结果 : 返回字典文件路径
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
*  函 数 名 :  Destroy
*  功能描述 : 释放资源
*  参数列表 : 无
*  说    明 :    
*  返回结果 : 无
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

// 开始爆破
/*******************************************************************************
*
*  函 数 名 :  Blast
*  功能描述 : 开始爆破
*  参数列表 : 无
*  说    明 :    
*  返回结果 : 
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


        // 这里可以断点


        // 开始了
        while (! inFile.eof())
        {
                inFile.getline(szPass, 8) ;

                // 先解密数据
                myDes.InitializeKey(szPass,0 );
                int nSrcFileOffset(0) ;
                while(nSrcFileOffset < m_nSrcFileSize)
                {
                        myDes.DecryptData((char *)m_pSrcBuf + nSrcFileOffset,0);
                        memcpy(pBuf + nSrcFileOffset, myDes.GetPlaintext(), 8) ;
                        nSrcFileOffset += 8 ;
                }

                // 成功了，再gzip解压
                
        }


        return false;
}
