#pragma once
#include "DES2.h"
#include <windows.h>
#include <string>
using namespace std ;

class C360ContactsBlast
{
public:
        C360ContactsBlast(void);
        ~C360ContactsBlast(void);
private:
        //Դ���ݰ�·��
        string m_strSrcFileName;
        // Ŀ��Ŀ¼
        string m_strDstPath;
        // �ֵ�·��
        string m_strDictionaryPath;
        // Դ�ļ��ļ����
        HANDLE m_hSrcFile;
        // Դ�ļ�File mapping���
        HANDLE m_hSrcFileMap;
        // ָ��ӳ�䵽�ڴ��е�360 contacts�ļ�����
        LPVOID m_pSrcBuf;
        // 360 contacts �ļ���С
        int m_nSrcFileSize;
        DES2 myDes;
public:
        // ����360 contacts���ݰ���·��
        bool SetSrcFileName(const string & strSrcFileName);
        //  ����360 contacts �ļ�·��
        const string & GetSrcFileName(void);
        // ���ý��ܳɹ��ļ��洢·��
        bool SetDstPath(const string & strDstPath);
        // ȡ�ý��ܳɹ��ļ��洢·��
        string & GetDstPath(void);
        // �����ֵ�·��
        bool SetDictionaryPath(string & strDictionaryPath);
        // ȡ���ֵ��ļ�·��
        string & GetDictionaryPath(void);
        // ���ļ�ӳ�䵽�ڴ�
        bool MappingFile(void);
        // ��ʼ����
        bool Blast(void);
private:
        // �ͷ���Դ
        void Destroy(void);
};
