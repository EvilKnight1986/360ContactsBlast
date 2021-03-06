#include "C360ContactsBlast.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char g_szSrcFileName[MAX_PATH] = {0} ;
char g_szDstPath[MAX_PATH]         = {0} ;
char g_szKeyFileName[MAX_PATH] = {0} ;

void PrintUsage(char **argv)
{
        printf("%s <m 字典路径> <r 解密文件路径>\r\n") ;
        printf("Example: \r\n") ;
        printf("%s m d:\\test\\passwd.txt r d:\\test\\test.txt \r\n") ;
        return  ;
}

/*******************************************************************************
*
*  函 数 名 :  ParseArgv
*  功能描述 : 处理命令行参数
*  参数列表 : argc             --           参数个数
*                   argv             --           命令行参数
*  说    明 :    为了方便自己测试，不用不停的输入参数
*  返回结果 : 参数错误的话返回false,否则返回Blast的结果
*
*******************************************************************************/
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

                // 跳过无用的参数前缀,比如-之类的
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

                // 处理参数
                int nCurrentArgv = i + 1 ;
                if (nCurrentArgv >= argc)
                {
                        break ;
                }
                switch(cArgvToken)
                {
                case 0:
                        break ;

                // 处理字典路径
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
                // 处理待解密文件路径
                case 'R':
                case 'r':
                        {
                                if (nCurrentArgv > argc)
                                {
                                        break ;
                                }
                                // 函数会去检查文件是否存在，所以这里不检查了
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
                PrintUsage(argv) ;
                return  false;
        }
        return ContactsBlast.Blast() ;
}
/*******************************************************************************
*
*  函 数 名 :  main
*  功能描述 : main函数
*  参数列表 : argc             --           参数个数
*                   argv             --           命令行参数
*  说    明 :    
*  返回结果 : 参数错误的话返回false,否则返回Blast的结果
*
*******************************************************************************/
int main(int argc, char** argv)
{
        system("title 360备份联系人数据包爆破") ;
        string str = "D:\\test\\passwd.txt" ;
        char szBuffer[260] = {0} ;

        if (argc > 1 && ParseArgv(argc, argv))
        {
                // 如果这个成立，说明在上面执行完了，不用再往下走了
                return 0 ;
        }

        C360ContactsBlast ContactsBlast ;
        
        ContactsBlast.SetDictionaryPath(str);

        // 输入字典路径
        do 
        {
                printf("请输入字典文件路径: ") ;
                scanf_s("%s", szBuffer, MAX_PATH) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetDictionaryPath(str));

        // 设置解密成功文件存储路径
        // 其实只是存一个成功的密码
        do 
        {
                printf("设置360 contacts数据包文件的路径: ") ;
                scanf_s("%s", szBuffer, MAX_PATH) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetSrcFileName(str));

        ContactsBlast.Blast() ;

        system("pause") ;
        return 0 ;
}