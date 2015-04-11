#pragma once
#include "DES2.h"
#include <windows.h>
#include <string>
using namespace std ;

#ifdef __cplusplus
extern "C"
{
#include "zlib/gzip.h"
}
#endif

class C360ContactsBlast
{
public:
        C360ContactsBlast(void);
        ~C360ContactsBlast(void);
private:
        //源数据包路径
        string m_strSrcFileName;
        // 目标目录
        string m_strDstPath;
        // 字典路径
        string m_strDictionaryPath;
        // 源文件文件句柄
        HANDLE m_hSrcFile;
        // 源文件File mapping句柄
        HANDLE m_hSrcFileMap;
        // 指向映射到内存中的360 contacts文件内容
        LPVOID m_pSrcBuf;
        // 360 contacts 文件大小
        int m_nSrcFileSize;
        // 用于解压gzip数据的缓冲区大小
        int m_nGzipBufSize ;
        // 用于des解压缓存
        Byte *m_pUndesBuf;
        // 用于gzip解压缓存
        Byte *m_pUngzipBuf;

        DES2 m_myDes;
public:
        // 设置360 contacts数据包的路径
        bool SetSrcFileName(const string & strSrcFileName);
        //  返回360 contacts 文件路径
        const string & GetSrcFileName(void);
        // 设置解密成功文件存储路径
        bool SetDstPath(const string & strDstPath);
        // 取得解密成功文件存储路径
        string & GetDstPath(void);
        // 设置字典路径
        bool SetDictionaryPath(string & strDictionaryPath);
        // 取得字典文件路径
        string & GetDictionaryPath(void);
        // 将文件映射到内存
        bool MappingFile(void);
        // 开始爆破
        bool Blast(void);
private:
        // 释放资源
        void Destroy(void);
};
