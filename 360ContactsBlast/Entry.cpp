#include "C360ContactsBlast.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char g_szSrcFileName[MAX_PATH] = {0} ;
char g_szDstPath[MAX_PATH]         = {0} ;
char g_szKeyFileName[MAX_PATH] = {0} ;

bool ParseArgv(int argc, char ** argv)
{
        char szBuffer[MAX_PATH] = {0} ;
        char cArgvToken(0) ;
        int nArgvLen(0) ;
        C360ContactsBlast ContactsBlast ;
        string str ;

        for (int i(1); i < argc; ++i)
        {
                nArgvLen = strlen(argv[i]) ;
                cArgvToken = 0 ;

                // �������õĲ���ǰ׺,����-֮���
                for(int j(0); j < nArgvLen && j < MAX_PATH; ++j)
                {
                        if (0 == isalpha(argv[i][j]))
                        {
                                continue ;
                        }
                        else
                        {
                                cArgvToken = argv[i][j] ;
                                break ;
                        }
                }

                // �������
                int nCurrentArgv = i + 1 ;
                switch(cArgvToken)
                {
                case 0:
                        break ;

                case 'M':
                case 'm':
                        {
                                if (nCurrentArgv > argc)
                                {
                                        break ;
                                }
                                str = argv[nCurrentArgv] ;
                                ContactsBlast.SetDictionaryPath( str ) ;
                                ++i ;
                        }
                        break ;
                case 'R':
                case 'r':
                        {
                                if (nCurrentArgv > argc)
                                {
                                        break ;
                                }
                                // ������ȥ����ļ��Ƿ���ڣ��������ﲻ�����
                                str = argv[nCurrentArgv] ;
                                ContactsBlast.SetSrcFileName( str ) ;
                                ++i ; 
                        }
                        break ;
                default:
                        break ;
                }
        }

        if ( ContactsBlast.GetSrcFileName().length() < 1
              || ContactsBlast.GetDictionaryPath().length() < 1)
        {
                return  false;
        }
        return ContactsBlast.Blast() ;
}

int main(int argc, char** argv)
{
        system("title 360������ϵ�����ݰ�����") ;
        string str = "D:\\test\\passwd.txt" ;
        char szBuffer[260] = {0} ;

        if (argc > 1 && 0 != ParseArgv(argc, argv))
        {
                // ������������˵��������ִ�����ˣ���������������
                return 0 ;
        }

        C360ContactsBlast ContactsBlast ;
        
        ContactsBlast.SetDictionaryPath(str);

        // �����ֵ�·��
        //do 
        //{
        //        printf("�������ֵ��ļ�·��: ") ;
        //        scanf_s("%s", szBuffer, MAX_PATH) ;
        //        str = szBuffer ;
        //} while (! ContactsBlast.SetDictionaryPath(str));

        // ���ý��ܳɹ��ļ��洢·��
        // ��ʵֻ�Ǵ�һ���ɹ�������
        do 
        {
                printf("����360 contacts���ݰ��ļ���·��: ") ;
                scanf_s("%s", szBuffer, MAX_PATH) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetSrcFileName(str));

        ContactsBlast.Blast() ;

        system("pause") ;
        return 0 ;
}