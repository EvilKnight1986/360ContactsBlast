#include "C360ContactsBlast.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char g_szSrcFileName[MAX_PATH] = {0} ;
char g_szDstPath[MAX_PATH]         = {0} ;
char g_szKeyFileName[MAX_PATH] = {0} ;

int ParseArgv(int argc, char ** argv)
{
        return 0 ;
}

int main(int argc, char** argv)
{
        system("title 360������ϵ�����ݰ�����") ;
        string str = "D:\\Projects\\test\\passwd.txt" ;
        char szBuffer[260] = {0} ;

        C360ContactsBlast ContactsBlast ;

        // �����ֵ�·��
        do 
        {
                printf("�������ֵ��ļ�·��: ") ;
                scanf("%s", szBuffer) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetDictionaryPath(str));
        
        // ���ý��ܳɹ��ļ��洢·��
        // ��ʵֻ�Ǵ�һ���ɹ�������
        //do 
        //{
        //        printf("��������ܳɹ�������Ŀ¼: ") ;
        //        scanf("%s", szBuffer) ;
        //        str = szBuffer ;
        //} while (! ContactsBlast.SetDstPath(str));


        // ���ý��ܳɹ��ļ��洢·��
        // ��ʵֻ�Ǵ�һ���ɹ�������
        do 
        {
                printf("����360 contacts���ݰ��ļ���·��: ") ;
                scanf("%s", szBuffer) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetSrcFileName(str));

        ContactsBlast.Blast() ;

        system("pause") ;
        return 0 ;
}